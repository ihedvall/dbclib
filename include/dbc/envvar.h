/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

/** \file envvar.h
 * \brief Wrapper wrong environment variables.
 */
#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <map>

namespace dbc {
/** \brief The variable data type. */
enum class EnvType : int {
  IntegerType = 0, ///< Integer variable.
  FloatType = 1,   ///< Floating point variable.
  StringType = 2,  ///< Text variable
  DataType = 3     ///< Data type variable.
};

/** \brief Type of access. */
enum class AccessType : int {
  Unrestricted = 0, ///< Unrestricted access.
  ReadOnly = 1,     ///< Read-only access.
  WriteOnly = 2,    ///< Write-only access.
  ReadWrite = 3     ///< Read and write access.
};

/** \brief Wrapper around an environment DBC variable. */
class EnvVar {
  public:
   /** \brief Sets the name. */
    void Name(const std::string& name) { name_ = name; }
    /** \brief Retuns the name. */
    [[nodiscard]] const std::string& Name() const { return name_; }

    /** \brief Sets the descriptive text. */
    void Comment(const std::string& comment) { comment_ = comment;}
    /** \brief Return the descriptive text. */
    [[nodiscard]] const std::string& Comment() const { return comment_; }

    /** \brief Sets the data type. */
    void Type(EnvType type) { type_ = type; }
    /** \brief Returns the data type. */
    [[nodiscard]] EnvType Type() const { return type_; }
    /** \brief Returns the data type as string. */
    [[nodiscard]] std::string TypeAsString() const;

    void Min(double min) { min_ = min; } ///< Sets the min range
    [[nodiscard]] double Min() const { return min_;} ///< Min range.

    void Max(double max) {max_ = max;} ///< Sets the max range.
    [[nodiscard]] double Max() const { return max_;} ///< Max range.

    void Unit(const std::string& unit) { unit_ = unit; } ///< Sets the unit.
    [[nodiscard]] const std::string& Unit() const { return unit_; } ///< Unit.

    /** \brief Sets the initial value. */
    void InitValue(double value) {init_value_ = value;}
    /** \brief Returns the initial value. */
    [[nodiscard]] double InitValue() const { return init_value_; }

    void Ident(uint64_t ident) {ident_ = ident;} ///< Sets the identity.
    [[nodiscard]] uint64_t Ident() const { return ident_;} ///< Identity.

    void Access(AccessType type) { access_type_ = type; } ///< Sets the access.
    [[nodiscard]] AccessType Access() const { return access_type_; } ///< Access

    /** \brief Sets the node list. */
    void NodeList(const std::vector<std::string>& node_list) {
      node_list_ = node_list;
    }
    /** \brief Returns the node list. */
    [[nodiscard]] const std::vector<std::string>& NodeList() const {
      return node_list_;
    }

    /** \brief Sets the enumerate list. */
    void EnumList(const std::map<int64_t, std::string>& enum_list);
    /** \brief Returns the node list. */
    [[nodiscard]] const std::map<int64_t, std::string>& EnumList() const;

   private:
    std::string name_; ///< Variable name.
    std::string comment_; ///< Variable description.
    EnvType type_ = EnvType::IntegerType; ///< Variable data type.
    double min_ = 0.0; ///< Min range.
    double max_ = 0.0; ///< Max range.
    std::string unit_; ///< Unit of measure.
    double init_value_ = 0.0; ///< Initial value.
    uint64_t ident_ = 0; ///< Identity.
    AccessType access_type_ = AccessType::Unrestricted; ///< Access type.
    std::vector<std::string> node_list_; ///< Node list.
    std::map<int64_t, std::string> enum_list_; ///< Enumerate list.
};

}  // namespace dbc
