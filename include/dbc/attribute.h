/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <string>
#include <vector>
#include <sstream>
namespace dbc {

enum class AttributeType : int {
  DbcNetwork,
  DbcNode,
  DbcMessage,
  DbcSignal,
  EnvironmentVariable,
  NodeSignalRelation,
  NodeMessageRelation,
};

enum class AttributeValueType : int {
  IntegerValue,
  FloatValue,
  StringValue,
  EnumValue,
  HexValue
};

class Attribute {
 public:
    Attribute( AttributeType type, const std::string& name );

    void Name(const std::string& name) { name_ = name; }
    [[nodiscard]] const std::string& Name() const { return name_; }

    void Type(AttributeType type ) { type_ = type; }
    [[nodiscard]] AttributeType Type() const { return type_; }

    void ValueType(AttributeValueType type ) { value_type_ = type; }
    [[nodiscard]] AttributeValueType ValueType() const { return value_type_; }

    void Min(double min ) { min_ = min; }
    [[nodiscard]] double Min() const { return min_; }

    void Max(double max ) { max_ = max; }
    [[nodiscard]] double Max() const { return max_; }

    void EnumList(const std::vector<std::string>& list);
    [[nodiscard]] const std::vector<std::string>& EnumList() const;

    template <typename T>
    void Value(const T& value);

    template <typename T>
    T Value() const;
  private:
    AttributeType      type_ = AttributeType::DbcNetwork;
    std::string        name_;
    AttributeValueType value_type_ = AttributeValueType::StringValue;
    double             value_float_ = 0.0;
    std::string        value_string_;
    std::vector<std::string> enum_list_;
    double             min_ = 0.0;
    double             max_ = 0.0;
};

template <typename T>
void Attribute::Value(const T& value) {
  value_float_ = static_cast<double>(value);
  value_string_ = std::to_string(value);
}

template<>
void Attribute::Value(const std::string& value);



template <typename T>
T Attribute::Value() const {
  T value = {};
  switch (ValueType()) {
    case AttributeValueType::StringValue: {
      std::istringstream temp(value_string_);
      try {
        temp >> value;
      } catch (const std::exception& ) {
      }
      break;
    }

    default:
      value = static_cast<T>(value_float_);
      break;
  }
  return value;
}

template <>
[[nodiscard]] std::string Attribute::Value() const;


}  // namespace dbc
