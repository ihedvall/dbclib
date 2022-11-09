/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once
#include <cstdint>
#include <vector>
#include <map>
#include <string>

#include "dbc/attribute.h"
#include "dbc/signal.h"

namespace dbc {

class Message {
 public:
   void Ident(uint64_t ident) {
     ident_ = ident;
   }
   [[nodiscard]] uint64_t Ident() const {
     return ident_;
   }

   void Name(const std::string& name) { name_ = name; }
   [[nodiscard]] const std::string& Name() const { return name_; }

   void Comment(const std::string& comment) { comment_ = comment; }
   [[nodiscard]] const std::string& Comment() const { return comment_; }

   void NofBytes(size_t bytes) { nof_bytes_ = bytes; }
   [[nodiscard]] size_t NofBytes() const { return nof_bytes_; }

   void Node(const std::string& node) {
     if (node_.empty()) {
       node_ = node;
     }
     sender_list_.push_back(node);
   }

   [[nodiscard]] std::string Node() const {
     return  node_;
   }

   Signal* GetSignal(const std::string& name);

   Attribute& CreateAttribute(const Attribute& definition);
   Signal& CreateSignal(const std::string& name);

  private:
   uint64_t ident_; ///< Message ID
   std::string name_;
   std::string comment_;
   size_t nof_bytes_ = 8;
   std::string node_;
   std::vector<std::string> sender_list_; ///< Also holds the node name

   std::vector<Attribute> attribute_list_;
   std::map<std::string, Signal> signal_list_;
};

}  // namespace dbc
