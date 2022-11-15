/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <any>
#include "dbc/attribute.h"

namespace dbc {

enum class SignalDataType : int {
  SignedData,
  UnsignedData,
  FloatData,
  DoubleData
};

enum class MuxType : int {
  NotMultiplexed,
  Multiplexor,
  Multiplexed,
  ExtendedMultiplexor
};

struct ExtendedMux {
  std::string multiplexor;
  std::vector<std::pair<size_t, size_t>> range_list;
  [[nodiscard]] bool InRange(size_t value) const;
};

class Signal {
 public:
  void Name(const std::string& name) { name_ = name; }
  [[nodiscard]] const std::string& Name() const { return name_; }

  void Unit(const std::string& unit) { unit_ = unit; }
  [[nodiscard]] const std::string& Unit() const { return unit_; }

  void Comment(const std::string& comment) { comment_ = comment; }
  [[nodiscard]] const std::string& Comment() const { return comment_; }

  void DataType(SignalDataType type) { data_type_ = type; }
  [[nodiscard]] SignalDataType DataType() const { return data_type_; }
  [[nodiscard]] std::string DataTypeAsString() const;

  void Mux(MuxType type) { mux_type_ = type; }
  [[nodiscard]] MuxType Mux() const { return mux_type_; }
  [[nodiscard]] std::string MuxAsString() const;

  void MuxValue(int value) { mux_value_ = value; }
  [[nodiscard]] int MuxValue() const { return mux_value_; }

  void BitStart(size_t start) { bit_start_ = start; }
  [[nodiscard]] size_t BitStart() const { return bit_start_; }

  void BitLength(size_t length) { bit_length_ = length; }
  [[nodiscard]] size_t BitLength() const { return bit_length_; }

  void LittleEndian(bool endian) { little_endian_ = endian; }
  [[nodiscard]] bool LittleEndian() const { return little_endian_; }

  void Scale(double scale) { scale_ = scale; }
  [[nodiscard]] double Scale() const { return scale_; }

  void Offset(double offset) { offset_ = offset; }
  [[nodiscard]] double Offset() const { return offset_; }

  void Min(double min) { min_ = min; }
  [[nodiscard]] double Min() const { return min_; }

  void Max(double max) { max_ = max; }
  [[nodiscard]] double Max() const { return max_; }

  void EnumList(const std::map<int64_t, std::string>& enum_list);
  [[nodiscard]] const std::map<int64_t, std::string>& EnumList() const;

  void Receivers(const std::vector<std::string>& receiver_list);
  [[nodiscard]] const std::vector<std::string>& Receivers() const;

  [[nodiscard]] const std::vector<Attribute>& Attributes() const {
    return attribute_list_;
  }

  void MessageId(uint64_t message_id) { message_id_ = message_id;}
  [[nodiscard]] uint64_t MessageId() const { return message_id_; }

  [[nodiscard]] bool IsMultiplexed() const;

  [[nodiscard]] Attribute& CreateAttribute(const Attribute& definition);
  [[nodiscard]] ExtendedMux& GetExtendedMux();
  [[nodiscard]] std::string GetEnumString(int64_t index) const;

  void ParseMessage(const std::vector<uint8_t>& message);

  template <typename T>
  bool ChannelValue( T& value ) const;

  template <typename T>
  bool EngValue( T& value ) const;
 private:
  std::string name_;
  std::string comment_;
  std::string unit_;

  std::vector<std::string> receiver_list_;

  MuxType mux_type_ = MuxType::NotMultiplexed;
  int mux_value_ = 0;
  size_t bit_start_ = 0;
  size_t bit_length_ = 0;
  bool little_endian_ = true;
  SignalDataType data_type_ = SignalDataType::SignedData;
  double scale_ = 1.0;
  double offset_ = 0.0;
  double min_ = 0.0;
  double max_ = 0.0;
  ExtendedMux extended_mux_;

  std::vector<Attribute> attribute_list_;
  std::map<int64_t, std::string> enum_list_;

  std::any channel_value_; ///< Unscaled value

  uint64_t message_id_ = 0;

};

template <typename T>
bool Signal::ChannelValue(T& value) const {
  bool valid = false;

  value = {};

  switch (data_type_) {
    case SignalDataType::SignedData: {
      int64_t temp = 0;
      try {
        valid = channel_value_.has_value();
        temp = std::any_cast<int64_t>(channel_value_);
        value = static_cast<T>(temp);
      } catch (const std::exception&) {
        valid = false;
      }
      break;
    }

    case SignalDataType::UnsignedData: {
      uint64_t temp = 0;
      try {
        valid = channel_value_.has_value();
        temp = std::any_cast<uint64_t>(channel_value_);
        value = static_cast<T>(temp);
      } catch (const std::exception&) {
        valid = false;
      }
      break;
    }

    case SignalDataType::FloatData: {
      float temp = 0;
      try {
        valid = channel_value_.has_value();
        temp = std::any_cast<float>(channel_value_);
        value = static_cast<T>(temp);
      } catch (const std::exception&) {
        valid = false;
      }
      break;
    }

    case SignalDataType::DoubleData: {
      double temp = 0;
      try {
        valid = channel_value_.has_value();
        temp = std::any_cast<float>(channel_value_);
        value = static_cast<T>(temp);
      } catch (const std::exception&) {
        valid = false;
      }
      break;
    }

    default:
      break;
   }
   return valid;
}

template <typename T>
bool Signal::EngValue(T& value) const {
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
        value = static_cast<T>(temp);
      } else {
        value = static_cast<T>(channel);
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
        value = static_cast<T>(temp);
      } else {
        value = static_cast<T>(channel);
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
        value = static_cast<T>(temp);
      } else {
        value = static_cast<T>(channel);
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
        value = static_cast<T>(temp);
      } else {
        value = static_cast<T>(channel);
      }
      break;
    }

    default:
      break;
  }
  return valid;
}

template <>
bool Signal::EngValue(std::string& value) const;

}  // namespace dbc
