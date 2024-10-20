/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */
/** \file node.h
 * \brief Interface against a DBC node (Device(ECU).
 */
#pragma once
#include <string>
#include <vector>
#include "dbc/attribute.h"
namespace dbc {
/** \brief Interface against a DBC node which normally is an ECU.
 *
 */
class Node {
 public:
  /** \brief Sets the name. */
  void Name(const std::string& name) { name_ = name; }
  /** \brief Returns the name. */
  [[nodiscard]] const std::string& Name() const {
    return name_;
  }

  /** \brief Source number is used in J1939 and is included in the CAN ID. */
  void Source(uint8_t source) {source_ = source;};
  /** \brief Source number (J1939). */
  [[nodiscard]] uint8_t Source() const;

  /** \brief Sets the descriptive text. */
  void Comment(const std::string& comment) { comment_ = comment; }
  /** \brief Returns the descriptive text. */
  [[nodiscard]] const std::string& Comment() const { return comment_; }

  /** \brief Returns the attribute list. */
  [[nodiscard]] const std::vector<Attribute>& Attributes() const {
    return attribute_list_;
  }
  /** \brief Creates an attribute. Parser function. */
  [[nodiscard]] Attribute& CreateAttribute(const Attribute& definition);
  /** \brief Returns an attribute by its name. */
  [[nodiscard]] const Attribute* GetAttribute(const std::string& name) const;

 private:
  std::string name_; ///< Node name.
  std::string comment_; ///< Node description.
  std::vector<Attribute> attribute_list_; ///< Attribute list.
  uint8_t source_ = 254; ///< Source Address (254-255 = not defined)
};

}  // namespace dbc
