/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/signal.h"
#include "dbchelper.h"
#include <algorithm>

namespace dbc {
Signal::~Signal() {
  observer_list_.clear();
}

Attribute& Signal::CreateAttribute(const Attribute& definition) {
  Attribute temp(definition);
  attribute_list_.emplace_back(temp);
  return attribute_list_.back();
}

void Signal::EnumList(const std::map<int64_t, std::string>& enum_list) {
  enum_list_ = enum_list;
}

const std::map<int64_t, std::string>& Signal::EnumList() const {
  return enum_list_;
}

void Signal::Receivers(const std::vector<std::string>& receiver_list) {
  receiver_list_ = receiver_list;
}

const std::vector<std::string>& Signal::Receivers() const {
  return receiver_list_;
}

ExtendedMux& Signal::GetExtendedMux() {
  return extended_mux_;
}

bool Signal::IsMultiplexed() const {
  return /*!mux_list_.empty() || */ mux_type_ == MuxType::Multiplexed;
}

void Signal::ParseMessage(const std::vector<uint8_t>& message,
                          uint64_t ns1970, uint32_t can_id, bool j1939) {
  SampleCanId(can_id);
  SampleTime(ns1970);

  channel_value_.valid = true;
  channel_value_.out_of_range = false;
  channel_value_.not_available = false;
  channel_value_.error = false;
  channel_value_.reserved = false;

  switch (data_type_) {
    case SignalDataType::SignedData: {
      const int64_t temp = DbcHelper::RawToSigned(little_endian_, bit_start_,
                                            bit_length_, message.data());
      channel_value_.signed_value = temp;
      break;
    }

    case SignalDataType::UnsignedData: {
      if (IsArrayValue()) {
        std::vector<uint8_t> temp = DbcHelper::RawToByteArray(bit_start_, bit_length_,
                                              message.data());
        channel_value_.array_value = std::move(temp);
      } else {
        const uint64_t temp = DbcHelper::RawToUnsigned(little_endian_,
          bit_start_, bit_length_, message.data());
        channel_value_.unsigned_value = temp;
      }
      break;
    }

    case SignalDataType::FloatData: {
      const float temp = DbcHelper::RawToFloat(little_endian_, bit_start_,
                                                     bit_length_, message.data());
      channel_value_.float_value = temp;
      break;
    }

    case SignalDataType::DoubleData: {
      const double temp = DbcHelper::RawToDouble(little_endian_, bit_start_,
                                               bit_length_, message.data());
      channel_value_.float_value = temp;
      break;
    }

    default:
      channel_value_.Clear();
      break;
  }

  // Check if out of range
  if (max_ > min_) {
    // Check out of range
    if (!enum_list_.empty()) {
      // Enumerate list converts to a string
      double key_value = 0.0;
      ChannelValue(key_value);
      if (key_value < min_ || key_value > max_) {
        channel_value_.out_of_range = true;
      } else if (j1939) {
        // In range but test if the enum string is 'Error' or 'NotAvailable
        const std::string enum_string = GetEnumString(static_cast<int64_t>(key_value));
        if (enum_string == "Error" ) {
          channel_value_.error = true;
        } else if (enum_string == "NotAvailable") {
          channel_value_.not_available = true;
        }

      }
    } else if (!IsArrayValue()) {
      double eng_value = 0.0;
      EngValue(eng_value);
      if (eng_value < min_ || eng_value > max_) {
        channel_value_.out_of_range = true;
      }
    }
  }

  // Check if it is not available and error
  if (j1939 && channel_value_.out_of_range) {
    DbcHelper::ParseJ1939Flags(*this, message);
    channel_value_.not_available = DbcHelper::IsAllBitsSet(LittleEndian(),
      BitStart(), BitLength(), message.data());
  }

  if (channel_value_.out_of_range ||
      channel_value_.not_available ||
      channel_value_.reserved ||
      channel_value_.error ) {
    channel_value_.valid = false;
  }

  FireOnSample();
}

bool ExtendedMux::InRange(size_t value) const {
  return std::any_of(range_list.cbegin(), range_list.cend(),
                     [&] (const RangePair &range) {
    return value >= range.first && value <= range.second;  });
}

std::string Signal::GetEnumString(int64_t index) const {
  const auto itr = enum_list_.find(index);
  return itr != enum_list_.cend() ? itr->second : std::string();
}

template <>
bool Signal::ChannelValue(std::string& value) const {
  bool valid = true;
  value.clear();

  switch (data_type_) {
    case SignalDataType::SignedData: {
      try {
        const auto temp = channel_value_.signed_value;
        value = std::to_string(temp);
      } catch (const std::exception&) {
        valid = false;
      }
      break;
    }

    case SignalDataType::UnsignedData: {
      if (IsArrayValue()) {
        try {
          const auto temp = channel_value_.array_value;
          // Assume that it is an ASCII string
          std::ostringstream out;
          for (const auto input : temp) {
            if (input == 0 || input == 0xFF) {
              break;
            }
            out << static_cast<char>(input);
          }
          value = out.str();
        } catch (const std::exception&) {
          valid = false;
        }
      } else {
        try {
          const auto temp = channel_value_.unsigned_value;
          value = std::to_string(temp);
        } catch (const std::exception&) {
          valid = false;
        }
      }
      break;
    }

    case SignalDataType::DoubleData:
    case SignalDataType::FloatData: {
      try {
        const auto temp = channel_value_.float_value;
        std::ostringstream temp_text;
        temp_text << temp;
        value =temp_text.str();
      } catch (const std::exception&) {
        valid = false;
      }
      break;
    }

    default:
      break;
  }
  if (!valid) {
    value = "*";
  }
  return channel_value_.valid && valid;
}

template <>
bool Signal::ChannelValue(std::vector<uint8_t>& value) const {
  value = channel_value_.array_value;
  return channel_value_.valid;
}

template <>
bool Signal::ChannelValue(SignalValue& value) const {
  value = channel_value_;
  return channel_value_.valid;
}


template <>
bool Signal::EngValue(std::string& value) const {
  bool valid = true;
  value = "*";
  bool need_to_convert = true;
  // If it is an enumerate. We could convert the enum string but that's weird.
  if (!enum_list_.empty()) {
    need_to_convert = false;
  }
  // Avoid truncation
  if (scale_ == 1.0 && offset_ == 0) {
    need_to_convert = false;
  }

  switch (data_type_) {
    case SignalDataType::SignedData: {
      int64_t channel = 0;
      valid = ChannelValue(channel);

      if (need_to_convert) {
        auto temp = static_cast<double>(channel);
        temp *= scale_;
        temp += offset_;
        std::ostringstream conv;
        conv << temp;
        value = std::move(conv.str());
      } else if (!enum_list_.empty()) {
        value = std::move(GetEnumString(channel));
      } else {
        value = std::move(std::to_string(channel));
      }
      break;
    }

    case SignalDataType::UnsignedData: {
      size_t bytes = bit_length_ / 8;
      if ((bit_length_ % 8) != 0) {
        ++bytes;
      }
      if (bytes > 8) {
         valid = ChannelValue(value);
      } else {
        uint64_t channel = 0;
        valid = ChannelValue(channel);
        if (need_to_convert) {
          auto temp = static_cast<double>(channel);
          temp *= scale_;
          temp += offset_;
          std::ostringstream conv;
          conv << temp;
          value = conv.str();
        } else if (!enum_list_.empty()) {
          value = GetEnumString(static_cast<int64_t>(channel));
        } else {
          value = std::to_string(channel);
        }
      }
      break;
    }

    case SignalDataType::FloatData: {
      float channel = 0;
      valid = ChannelValue(channel);
      if (need_to_convert) {
        auto temp = static_cast<double>(channel);
        temp *= scale_;
        temp += offset_;
        std::ostringstream conv;
        conv << temp;
        value = conv.str();
      } else {
        value = std::to_string(channel);
      }
      break;
    }

    case SignalDataType::DoubleData: {
      double channel = 0;
      valid = ChannelValue(channel);
      if (need_to_convert) {
        auto temp = channel;
        temp *= scale_;
        temp += offset_;
        std::ostringstream conv;
        conv << temp;
        value = conv.str();
      } else {
        value = std::to_string(channel);
      }
      break;
    }

    default:
      valid = false;
      break;
  }

  return channel_value_.valid && valid;
}

std::string Signal::DataTypeAsString() const {

  if (!enum_list_.empty()) {
    return "Enumerate";
  }

  switch (data_type_) {
    case SignalDataType::SignedData:
      return "Signed";

    case SignalDataType::UnsignedData:
      // Check if it might be a string
      if ((bit_start_ % 8) == 0 &&
          (bit_length_ % 8) == 0 &&
          (bit_length_ / 8) > 8) {
        return "String";
      }
      return "Unsigned";

    case SignalDataType::FloatData:
      return "Float";

    case SignalDataType::DoubleData:
      return "Double";

    default:
      break;
  }
  return {};
}

std::string Signal::MuxAsString() const {
  std::ostringstream temp;
  switch (mux_type_) {
    case MuxType::Multiplexor:
      temp << "M (Multiplexor)";
      break;

    case MuxType::Multiplexed:
      temp << "m" << MuxValue() << " (Multiplexed)";
      break;

    case MuxType::ExtendedMultiplexor:
      temp << "E (Extended Multiplexor)";
      break;

    case MuxType::NotMultiplexed:
    default:
      break;
  }

  if (!extended_mux_.multiplexor.empty()) {
    if (!temp.str().empty()) {
      temp << " ";
    } else {
      temp << "e (Extended Multiplexed) ";
    }

    temp << extended_mux_.multiplexor << ":";
    for (const auto& itr : extended_mux_.range_list) {
      temp << " " << itr.first << "-" << itr.second;
    }

  }
  return temp.str();
}

void Signal::AttachObserver(std::shared_ptr<ISampleObserver>& observer) const {
  std::shared_ptr<ISampleObserver> temp(observer);
  observer_list_.push_back(std::move(temp));
}

void Signal::ClearObserverList() const {
  observer_list_.clear();
}

void Signal::FireOnSample() const {
  for (auto& observer : observer_list_) {
    if (observer != nullptr) {
      observer->OnSample();
    }
  }
}

bool Signal::IsArrayValue() const {
  size_t bytes = BitLength() / 8;
  if ((BitLength() % 8) != 0) {  // This shouldn't happen
    ++bytes;
  }
  return bytes > 8;
}

}  // namespace dbc