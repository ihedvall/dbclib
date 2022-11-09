/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once
#include <string>
#include <vector>
#include "dbc/attribute.h"
namespace dbc {

class Node {
 public:
  void Name(const std::string& name) { name_ = name; }
  [[nodiscard]] const std::string& Name() const {
    return name_;
  }
  void Comment(const std::string& comment) { comment_ = comment; }
  [[nodiscard]] const std::string& Comment() const { return comment_; }

  Attribute& CreateAttribute(const Attribute& definition);

 private:
  std::string name_;
  std::string comment_;
  std::vector<Attribute> attribute_list_;
};

}  // namespace dbc
