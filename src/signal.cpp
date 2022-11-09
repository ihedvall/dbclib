/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/signal.h"

namespace dbc {

Attribute& Signal::CreateAttribute(const Attribute& definition) {
  Attribute temp(definition);
  attribute_list_.emplace_back(temp);
  return attribute_list_.back();
}

void Signal::EnumList(const std::map<int64_t, std::string>& enum_list) {
  enum_list_ = enum_list;
}

const std::map<int64_t, std::string>& Signal::EnumList() const {
  return enum_list_;
}

void Signal::Receivers(const std::vector<std::string>& receiver_list) {
  receiver_list_ = receiver_list;
}

const std::vector<std::string>& Signal::Receivers() const {
  return receiver_list_;
}

ExtendedMux& Signal::CreateExtendedMux() {
  ExtendedMux temp;
  mux_list_.emplace_back(temp);
  return mux_list_.back();
}

}  // namespace dbc