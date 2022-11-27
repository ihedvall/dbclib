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
  void Source(uint8_t source) {source_ = source;};
  [[nodiscard]] uint8_t Source() const;

  void Comment(const std::string& comment) { comment_ = comment; }
  [[nodiscard]] const std::string& Comment() const { return comment_; }

  [[nodiscard]] const std::vector<Attribute>& Attributes() const {
    return attribute_list_;
  }
  Attribute& CreateAttribute(const Attribute& definition);
  const Attribute* GetAttribute(const std::string& name) const;


 private:
  std::string name_;
  std::string comment_;
  std::vector<Attribute> attribute_list_;
  uint8_t source_ = 254; ///< Source Address (254-255 = not defined)
};

}  // namespace dbc
