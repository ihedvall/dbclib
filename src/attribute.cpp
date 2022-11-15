/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/attribute.h"

namespace dbc {
Attribute::Attribute(AttributeType type, const std::string& name)
: type_(type),
  name_(name) {

}

template <>
void Attribute::Value(const std::string& value) {
  switch (ValueType()) {


    case AttributeValueType::EnumValue: {
      value_float_ = 0;
      value_string_ = value;
      for (size_t index = 0; index < enum_list_.size(); ++index) {
        if (enum_list_[index] == value) {
          value_float_ = static_cast<double>(index);
          value_string_ = value;
          return;
        }
      }
      try {
        const auto idx = std::stoull(value);
        if (idx < enum_list_.size()) {
          value_float_ = static_cast<double>(idx);
          value_string_ = enum_list_[idx];
          return;
        }
      } catch (const std::exception& ) {

      }
    }

    default: {
      try {
        value_float_ = std::stod(value);
        value_string_ = value;
      } catch (const std::exception&) {

      }
      break;
    }

  }

}

template <>
std::string Attribute::Value() const {
  return value_string_;
}

void Attribute::EnumList(const std::vector<std::string>& list) {
  enum_list_ = list;
}

const std::vector<std::string>& Attribute::EnumList() const {
  return enum_list_;
}

std::string Attribute::ValueTypeAsString() const {
  switch (value_type_) {
    case AttributeValueType::IntegerValue:
      return "Integer";

    case AttributeValueType::FloatValue:
      return "Float";

    case AttributeValueType::StringValue:
      return "String";

    case AttributeValueType::EnumValue:
      return "Enumerate";

    case AttributeValueType::HexValue:
      return "Hexadecimal";

    default:
      break;
  }
  return {};
}

}  // namespace dbc