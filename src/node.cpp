/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/node.h"
#include <ranges>
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
#if __cplusplus > 202003L
  const auto itr = std::ranges::find_if(attribute_list_,
                                        [&] (const auto& attr) {
    return attr.Name() == name;
  });
  return itr != attribute_list_.cend() ? &(*itr) : nullptr;
#else
    for (const auto& attr: attribute_list_) {
        if (attr.Name() == name)
            return &attr;
    }
    return nullptr;
#endif
}

}  // namespace dbc