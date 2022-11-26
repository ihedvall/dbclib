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
   [[nodiscard]] bool IsJ1939() const;
   [[nodiscard]] uint32_t CanId() const;
   [[nodiscard]] uint8_t  Priority() const;   ///< J1939 Priority
   [[nodiscard]] uint32_t Pgn() const;        ///< J1939 PGN
   [[nodiscard]] uint8_t  Source() const;     ///< J1939 Source
   [[nodiscard]] bool ExtendedDataPage() const;  ///< J1938 Data Page Flag
   [[nodiscard]] bool DataPage() const;       ///< J1938 Data Page Flag
   [[nodiscard]] uint8_t PduFormat() const;   ///< J1939 PF
   [[nodiscard]] uint8_t PduSpecific() const; ///< J1939 PS
   [[nodiscard]] bool IsPdu1() const;
   [[nodiscard]] bool IsPdu2() const;

   void Name(const std::string& name) { name_ = name; }
   [[nodiscard]] const std::string& Name() const { return name_; }

   void Comment(const std::string& comment) { comment_ = comment; }
   [[nodiscard]] const std::string& Comment() const { return comment_; }

   void NofBytes(size_t bytes);
   [[nodiscard]] size_t NofBytes() const;

   void Node(const std::string& node) {
     if (node_.empty()) {
       node_ = node;
     }
     sender_list_.push_back(node);
   }

   [[nodiscard]] std::string NodeName() const {
     return  node_;
   }

   [[nodiscard]] Signal* GetSignal(const std::string& name);
   [[nodiscard]] const Signal* GetSignal(const std::string& name) const;
   [[nodiscard]] Signal* GetMultiplexor();
   [[nodiscard]] const Attribute* GetAttribute(const std::string& name) const;

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

   [[nodiscard]] const std::vector<uint8_t>& Data() const {return data_;}
   bool UpdateData(const std::vector<uint8_t>& message,
                   size_t offset = 0, size_t data_index = 0);
   void ParseMessage(uint64_t ns1970);
   void ResetSequenceNumber() {sequence_number_ = 0;}
   uint8_t NextSequenceNumber() const {return sequence_number_;}

   void ResetSampleCounter() const;
   void StepSampleCounter() const {++sample_counter_;}
   size_t SampleCounter() const {return sample_counter_;}

   Attribute& CreateAttribute(const Attribute& definition);
   Signal& CreateSignal(const std::string& name);

  private:
   uint64_t ident_; ///< Message ID
   std::string name_;
   std::string comment_;
   std::string node_;
   std::vector<std::string> sender_list_; ///< Also holds the node name

   std::vector<Attribute> attribute_list_;
   std::map<std::string, Signal> signal_list_;

   mutable size_t sample_counter_ = 0;
   std::vector<uint8_t> data_; ///< Store last message and solve >8 byte data
   uint8_t sequence_number_ = 0; ///< Used to verify multibyte package
};

}  // namespace dbc
