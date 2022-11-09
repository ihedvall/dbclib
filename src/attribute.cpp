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
  value_string_ = value;

  switch (ValueType()) {
    case AttributeValueType::IntegerValue:
    case AttributeValueType::FloatValue:
      try {
        value_float_ = std::stod(value);
      } catch (const std::exception& ) {
      }
      break;

    case AttributeValueType::EnumValue: {
      value_float_ = 0;
      for (size_t index = 0; index < enum_list_.size(); ++index) {
        if (enum_list_[index] == value) {
          value_float_ = static_cast<double>(index);
          break;
        }
      }
      break;
    }

    default:
      break;
  }
  try {
    value_float_ = std::stod(value);
  } catch (const std::exception& ) {
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

}  // namespace dbc