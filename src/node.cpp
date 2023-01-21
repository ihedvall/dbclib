/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/node.h"
#include <algorithm>
namespace dbc {

Attribute& Node::CreateAttribute(const Attribute& definition) {
  Attribute temp(definition);
  attribute_list_.emplace_back(temp);
  return attribute_list_.back();
}

uint8_t Node::Source() const {
  if (source_ > 253) {
   const auto* attr = GetAttribute("NmStationAddress");
   if (attr != nullptr) {
     return attr->Value<uint8_t>();
   }
  }
  return source_;
}

const Attribute* Node::GetAttribute(const std::string& name) const {
  const auto itr = std::find_if(attribute_list_.cbegin(),attribute_list_.cend(),
                                        [&] (const auto& attr) {
    return attr.Name() == name;
  });
  return itr != attribute_list_.cend() ? &(*itr) : nullptr;
}

}  // namespace dbc