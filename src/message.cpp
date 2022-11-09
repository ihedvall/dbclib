/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/message.h"

namespace dbc {

Attribute& Message::CreateAttribute(const Attribute& definition) {
  Attribute temp(definition);
  attribute_list_.emplace_back(temp);
  return attribute_list_.back();
}

Signal* Message::GetSignal(const std::string& name) {
  auto itr = signal_list_.find(name);
  return itr != signal_list_.end() ? &itr->second : nullptr;
}

Signal& Message::CreateSignal(const std::string& name) {
  auto itr = signal_list_.find(name);
  if (itr == signal_list_.end()) {
    Signal temp;
    temp.Name(name);
    itr = signal_list_.insert({name, temp}).first;
  }
  return itr->second;
}

}  // namespace dbc