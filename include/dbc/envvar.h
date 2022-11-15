/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <map>

namespace dbc {

enum class EnvType : int {
  IntegerType = 0,
  FloatType = 1,
  StringType = 2,
  DataType = 3
};

enum class AccessType : int {
  Unrestricted = 0,
  ReadOnly = 1,
  WriteOnly = 2,
  ReadWrite = 3
};

class EnvVar {
  public:
    void Name(const std::string& name) { name_ = name; }
    [[nodiscard]] const std::string& Name() const { return name_; }

    void Comment(const std::string& comment) { comment_ = comment;}
    [[nodiscard]] const std::string& Comment() const { return comment_; }

    void Type(EnvType type) { type_ = type; }
    [[nodiscard]] EnvType Type() const { return type_; }
    [[nodiscard]] std::string TypeAsString() const;

    void Min(double min) { min_ = min; }
    [[nodiscard]] double Min() const { return min_;}

    void Max(double max) {max_ = max;}
    [[nodiscard]] double Max() const { return max_;}

    void Unit(const std::string& unit) { unit_ = unit; }
    [[nodiscard]] const std::string& Unit() const { return unit_; }

    void InitValue(double value) {init_value_ = value;}
    [[nodiscard]] double InitValue() const { return init_value_; }

    void Ident(uint64_t ident) {ident_ = ident;}
    [[nodiscard]] uint64_t Ident() const { return ident_;}

    void Access(AccessType type) { access_type_ = type; }
    [[nodiscard]] AccessType Access() const { return access_type_; }

    void NodeList(const std::vector<std::string>& node_list) {
      node_list_ = node_list;
    }
    [[nodiscard]] const std::vector<std::string>& NodeList() const {
      return node_list_;
    }

    void EnumList(const std::map<int64_t, std::string>& enum_list);
    [[nodiscard]] const std::map<int64_t, std::string>& EnumList() const;

   private:
    std::string name_;
    std::string comment_;
    EnvType type_ = EnvType::IntegerType;
    double min_ = 0.0;
    double max_ = 0.0;
    std::string unit_;
    double init_value_ = 0.0;
    uint64_t ident_ = 0;
    AccessType access_type_ = AccessType::Unrestricted;
    std::vector<std::string> node_list_;
    std::map<int64_t, std::string> enum_list_;
};

}  // namespace dbc
