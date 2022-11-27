/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/signal.h"
#include "dbchelper.h"
#include <ranges>
#include <algorithm>

namespace dbc {
Signal::~Signal() {
  for (auto* observer : observer_list_) {
    if (observer != nullptr) {
      observer->DetachObserver();
    }
  }
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
                          uint64_t ns1970, uint32_t can_id) {
  SampleCanId(can_id);
  SampleTime(ns1970);
  if (!Valid()) {
    channel_value_.reset();
    FireOnSample();
    return;
  }

  switch (data_type_) {
    case SignalDataType::SignedData: {
      const int64_t temp = DbcHelper::RawToSigned(little_endian_, bit_start_,
                                            bit_length_, message.data());
      channel_value_ = temp;
      break;
    }

    case SignalDataType::UnsignedData: {
      size_t bytes = bit_length_ / 8;
      if ((bit_length_ % 8) != 0) {
        ++bytes;
      }
      if (bytes > 8) {
        auto temp = DbcHelper::RawToByteArray(bit_start_, bit_length_,
                                              message.data());
        channel_value_ = temp;
      } else {
        const uint64_t temp = DbcHelper::RawToUnsigned(
            little_endian_, bit_start_, bit_length_, message.data());
        channel_value_ = temp;
      }
      break;
    }

    case SignalDataType::FloatData: {
      const float temp = DbcHelper::RawToFloat(little_endian_, bit_start_,
                                                     bit_length_, message.data());
      channel_value_ = temp;
      break;
    }

    case SignalDataType::DoubleData: {
      const double temp = DbcHelper::RawToDouble(little_endian_, bit_start_,
                                               bit_length_, message.data());
      channel_value_ = temp;
      break;
    }

    default:
      channel_value_.reset();
      break;
  }
  FireOnSample();
}

bool ExtendedMux::InRange(size_t value) const {
  return std::ranges::any_of(range_list, [&] (const auto& range) {
    return value >= range.first && value <= range.second;  });
}

std::string Signal::GetEnumString(int64_t index) const {
  const auto itr = enum_list_.find(index);
  return itr != enum_list_.cend() ? itr->second : std::string();
}

template <>
bool Signal::ChannelValue(std::string& value) const {
  bool valid = false;
  value.clear();

  switch (data_type_) {
    case SignalDataType::SignedData: {
      try {
        valid = channel_value_.has_value() && Valid();
        const auto temp = std::any_cast<int64_t>(channel_value_);
        value = std::to_string(temp);
      } catch (const std::exception&) {
        valid = false;
      }
      break;
    }

    case SignalDataType::UnsignedData: {
      size_t bytes = bit_length_ / 8;
      if ((bit_length_ % 8) != 0) {
        ++bytes;
      }
      if (bytes > 8) {
        try {
          valid = channel_value_.has_value() && Valid();
          const auto temp = std::any_cast<std::vector<uint8_t>>(channel_value_);
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
          valid = channel_value_.has_value() && Valid();
          const auto temp = std::any_cast<uint64_t>(channel_value_);
          value = std::to_string(temp);
        } catch (const std::exception&) {
          valid = false;
        }
      }
      break;
    }

    case SignalDataType::FloatData: {
      try {
        valid = channel_value_.has_value() && Valid();
        const auto temp = std::any_cast<float>(channel_value_);
        std::ostringstream temp_text;
        temp_text << temp;
        value =temp_text.str();
      } catch (const std::exception&) {
        valid = false;
      }
      break;
    }

    case SignalDataType::DoubleData: {
      try {
        valid = channel_value_.has_value() && Valid();
        const auto temp = std::any_cast<double>(channel_value_);
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
  return valid;
}

template <>
bool Signal::ChannelValue(std::any& value) const {
  bool valid = channel_value_.has_value() && Valid();
  if (valid) {
    value = channel_value_;
  } else {
    value.reset();
  }
  value = channel_value_;
  return valid;
}


template <>
bool Signal::EngValue(std::string& value) const {
  bool valid = false;
  value = {};
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
        value = conv.str();
      } else if (!enum_list_.empty()) {
        value = GetEnumString(channel);
      } else {
        value = std::to_string(channel);
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
      break;
  }
  if (!valid) {
    value = "*";
  }
  return valid;
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

void Signal::AttachObserver(ISampleObserver* observer) const {
  observer_list_.push_back(observer);
}

void Signal::DetachObserver(const ISampleObserver* observer) const  {
  for (auto itr = observer_list_.begin(); itr != observer_list_.end(); ) {
    if ( *itr == observer) {
      itr = observer_list_.erase(itr);
    } else {
      ++itr;
    }
  }
}

void Signal::FireOnSample() {
  for (auto* observer : observer_list_) {
    if (observer != nullptr) {
      observer->OnSample();
    }
  }
}
}  // namespace dbc