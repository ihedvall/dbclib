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

   [[nodiscard]] bool IsExtended() const;

   [[nodiscard]] uint32_t CanId() const;

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

   [[nodiscard]] Signal* GetSignal(const std::string& name);
   [[nodiscard]] const Signal* GetSignal(const std::string& name) const;
   [[nodiscard]] Signal* GetMultiplexor();

   [[nodiscard]] const std::map<std::string, Signal>& Signals() const {
     return signal_list_;
   }
   [[nodiscard]] const std::vector<std::string>& Senders() const {
     return sender_list_;
   }
   [[nodiscard]] const std::vector<Attribute>& Attributes() const {
     return attribute_list_;
   }

   [[nodiscard]] bool IsNodeSender(const std::string& node_name) const;

   void ParseMessage(const std::vector<uint8_t>& message);

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
