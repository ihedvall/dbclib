/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/signal.h"
#include "dbchelper.h"
#include <algorithm>

namespace dbc {

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

void Signal::ParseMessage(const std::vector<uint8_t>& message) {
    switch (data_type_) {
    case SignalDataType::SignedData: {
      const int64_t temp = DbcHelper::RawToSigned(little_endian_, bit_start_,
                                            bit_length_, message.data());
      channel_value_ = temp;
      break;
    }

    case SignalDataType::UnsignedData: {
      const uint64_t temp = DbcHelper::RawToUnsigned(little_endian_, bit_start_,
                                                  bit_length_, message.data());
      channel_value_ = temp;
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
        value = std::to_string(temp);
      } else if (!enum_list_.empty()) {
        value = GetEnumString(channel);
      } else {
        value = std::to_string(channel);
      }
      break;
    }

    case SignalDataType::UnsignedData: {
      uint64_t channel = 0;
      valid = ChannelValue(channel);
      if (need_to_convert) {
        auto temp = static_cast<double>(channel);
        temp *= scale_;
        temp += offset_;
        value = std::to_string(temp);
      } else if (!enum_list_.empty()) {
        value = GetEnumString(static_cast<int64_t>(channel));
      } else {
        value = std::to_string(channel);
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
        value = std::to_string(temp);
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
        value = std::to_string(temp);
      } else {
        value = std::to_string(channel);
      }
      break;
    }

    default:
      break;
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

}  // namespace dbc