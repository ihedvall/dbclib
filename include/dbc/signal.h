/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <map>
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
};

struct ExtendedMux {
  std::string multiplexor;
  std::vector<std::pair<size_t, size_t>> range_list;
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

  void Mux(MuxType type) { mux_type_ = type; }
  [[nodiscard]] MuxType Mux() const { return mux_type_; }

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

  [[nodiscard]] Attribute& CreateAttribute(const Attribute& definition);
  [[nodiscard]] ExtendedMux& CreateExtendedMux();

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
  std::vector<ExtendedMux> mux_list_;


  std::vector<Attribute> attribute_list_;
  std::map<int64_t, std::string> enum_list_;
};

}  // namespace dbc
