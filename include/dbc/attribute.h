/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
/** \file attribute.h
 * \brief All DBC network objects may have attributes attached to them.
 */
#pragma once

#include <string>
#include <vector>
#include <sstream>
namespace dbc {
/** \brief Define what type of network object the attribute is valid for.
 *
 */
enum class AttributeType : int {
  DbcNetwork, ///< Network attribute.
  DbcNode,    ///< Node/Device attribute.
  DbcMessage, ///< Message attribute.
  DbcSignal,  ///< Signal attribute.
  EnvironmentVariable, ///< Environment attribute
  NodeSignalRelation, ///< Node signal relation attribute.
  NodeMessageRelation, ///< Node message relation attribute.
};

/** \brief Data type of the attribute.
 *
 */
enum class AttributeValueType : int {
  IntegerValue, ///< Integer value.
  FloatValue,   ///< Floating point value.
  StringValue,  ///< Text value.
  EnumValue,    ///< Enumerate value.
  HexValue      ///< Hexa-decimal value.
};

/** \brief Support class for handling attributes of network objects.
 *
 * The Attribute class is a support class for handling attributes attached
 * to DBC objects.
 *
 * The DBC file first specify a definition of an attribute.
 * This definition defines range and data type i.e. a sort of template.
 *
 * Then the DBC file define the attribute that references a definition and
 * has a value (constant).
 */
class Attribute {
 public:
    /** \brief Constructor for an attribute or definition. */
    Attribute( AttributeType type, const std::string& name );

    /** \brief Sets the name of the attribute. */
    void Name(const std::string& name) { name_ = name; }
    /** \brief Retuns the attribute name. */
    [[nodiscard]] const std::string& Name() const { return name_; }

    /** \brief Sets the type of attribute. */
    void Type(AttributeType type ) { type_ = type; }
    /** \brief Return type of attribute. */
    [[nodiscard]] AttributeType Type() const { return type_; }

    /** \brief Sets the attribute data type. */
    void ValueType(AttributeValueType type ) { value_type_ = type; }
    /** \brief Returns the attribute data type. */
    [[nodiscard]] AttributeValueType ValueType() const { return value_type_; }
    /** \brief Returns the attribute data type as string. */
    [[nodiscard]] std::string ValueTypeAsString() const;

    void Min(double min ) { min_ = min; } ///< Sets the min range
    [[nodiscard]] double Min() const { return min_; } ///< Min range.

    void Max(double max ) { max_ = max; } ///< Sets the max range.
    [[nodiscard]] double Max() const { return max_; } ///< Max range.

    /** \brief Sets an enumerate string list. */
    void EnumList(const std::vector<std::string>& list);
    /** \brief Returns an enumerated string list. */
    [[nodiscard]] const std::vector<std::string>& EnumList() const;

    /** \brief Sets the attribute value. */
    template <typename T>
    void Value(const T& value);

    /** \brief Returns the attribute value. */
    template <typename T>
    [[nodiscard]] T Value() const;
  private:
    AttributeType      type_ = AttributeType::DbcNetwork; ///< Attribute type
    std::string        name_; ///< Name of attribute.
    AttributeValueType value_type_ =
        AttributeValueType::StringValue; ///< Attribute data type.
    double             value_float_ = 0.0; ///< Attribute float value.
    std::string        value_string_; ///< Attribute text value.
    std::vector<std::string> enum_list_; ///< Attribute enumerate list.
    double             min_ = 0.0; ///< Min range.
    double             max_ = 0.0; ///< Max range.
};


template <typename T>
void Attribute::Value(const T& value) {
  try {
    value_float_ = static_cast<double>(value);
    switch (value_type_) {
      case AttributeValueType::IntegerValue:
        value_string_ = std::to_string(static_cast<int64_t>(value));
        break;

      case AttributeValueType::FloatValue:
        value_string_ = std::to_string(static_cast<double>(value));
        break;

      case AttributeValueType::EnumValue: {
        const auto index = static_cast<size_t>(value_float_);
        if ( index < enum_list_.size()) {
          value_string_ = enum_list_[index];
        }
        break;
      }

      default:
        value_string_ = std::to_string(value);
        break;
    }

  } catch (const std::exception&) {
    value_float_ = 0.0;
    value_string_ = "Conversion error";
  }
}

/** \brief Sets an attribute  string value. */
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

/** \brief Returns an attribute string value. */
template <>
[[nodiscard]] std::string Attribute::Value() const;


}  // namespace dbc
