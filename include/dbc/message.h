/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */
/** \file message.h
 * \brief DBC message configuration object.
 */
#pragma once
#include <cstdint>
#include <vector>
#include <map>
#include <string>

#include "dbc/attribute.h"
#include "dbc/signal.h"

namespace dbc {
/** \brief Sorted list of signal objects. */
using SignalList = std::map<std::string, Signal>;

/** \brief DBC message configuration object. */
class Message {
 public:
   void Ident(uint64_t ident) { ///< Sets the message ID (29-bit)
     ident_ = ident;
   }
   [[nodiscard]] uint64_t Ident() const { ///< Returns the message ID.
     return ident_;
   }

   [[nodiscard]] bool IsExtended() const; ///< True if 29-bit ID.
   [[nodiscard]] bool IsJ1939() const; ///< True if it is a J1939 message.
   [[nodiscard]] uint32_t CanId() const; ///< Returns CAN ID.
   [[nodiscard]] uint8_t  Priority() const;   ///< J1939 Priority
   [[nodiscard]] uint32_t Pgn() const;        ///< J1939 PGN
   [[nodiscard]] uint8_t  Source() const;     ///< J1939 Source
   [[nodiscard]] bool ExtendedDataPage() const;  ///< J1938 Data Page Flag
   [[nodiscard]] bool DataPage() const;       ///< J1938 Data Page Flag
   [[nodiscard]] uint8_t PduFormat() const;   ///< J1939 PF
   [[nodiscard]] uint8_t PduSpecific() const; ///< J1939 PS
   [[nodiscard]] bool IsPdu1() const; ///< True if PDU1
   [[nodiscard]] bool IsPdu2() const; ///< True if PDU2

   /** \brief Sets the message name. */
   void Name(const std::string& name) { name_ = name; }
   /** \brief Returns the message name. */
   [[nodiscard]] const std::string& Name() const { return name_; }

   /** \brief Sets the descriptive text. */
   void Comment(const std::string& comment) { comment_ = comment; }
   /** \brief Returns the descriptive text. */
   [[nodiscard]] const std::string& Comment() const { return comment_; }

   void NofBytes(size_t bytes); ///< Sets the number of bytes.
   [[nodiscard]] size_t NofBytes() const; ///< Returns the number of bytes.

   /** \brief Sets a node name. */
   void Node(const std::string& node) {
     if (node_.empty()) {
       node_ = node;
     }
     sender_list_.push_back(node);
   }
   /** \brief Returns the node name. */
   [[nodiscard]] std::string NodeName() const {
     return  node_;
   }

   /** \brief Returns a signal by its name. */
   [[nodiscard]] Signal* GetSignal(const std::string& name);
   /** \brief Returns a signal by its name. */
   [[nodiscard]] const Signal* GetSignal(const std::string& name) const;
   /** \brief Returns the multiplexer signal object. */
   [[nodiscard]] Signal* GetMultiplexor();

   /** \brief Returns an attribute by its name. */
   [[nodiscard]] const Attribute* GetAttribute(const std::string& name) const;

   /** \brief Returns the signal list. */
   [[nodiscard]] const SignalList& Signals() const {
     return signal_list_;
   }

   /** \brief Returns a list of sender names. */
   [[nodiscard]] const std::vector<std::string>& Senders() const {
     return sender_list_;
   }

   /** \brief Returns a list of attributes. */
   [[nodiscard]] const std::vector<Attribute>& Attributes() const {
     return attribute_list_;
   }

   /** \brief Returns true if the node is a sender. */
   [[nodiscard]] bool IsNodeSender(const std::string& node_name) const;

   /** \brief Returns the last message data buffer. */
   [[nodiscard]] const std::vector<uint8_t>& Data() const {return data_;}

   /** \brief Update the internal data buffer.
    *
    * Sets the internal last message data buffer. Note that the input offset
    * and destination offset is used if the message requires more than one
    * CAN data message before it is complete.
    *
    * @param message Message data.
    * @param offset Offset in the message data buffer (input index).
    * @param data_index Offset in the last message data buffer (dest index).
    * @return Returns true if this was the last byte (complete message).
    */
   bool UpdateData(const std::vector<uint8_t>& message,
                   size_t offset = 0, size_t data_index = 0);
   /** \brief Parses the message. Internal usage. */
   void ParseMessage(uint64_t ns1970, uint32_t can_id);
   /** \brief Reset the internal sequence counter. */
   void ResetSequenceNumber() {sequence_number_ = 0;}
   /** \brief Returns the next sequence number. */
   uint8_t NextSequenceNumber() const {return sequence_number_;}

   void ResetSampleCounter() const; ///< Reset the sample counters.
   /** \brief Increments the internal sample counters. */
   void StepSampleCounter() const {++sample_counter_;}
   /** \brief Returns number of samples. */
   size_t SampleCounter() const {return sample_counter_;}

   /** \brief Creates an attributes by using its definition. */
   Attribute& CreateAttribute(const Attribute& definition);

   /** \brief Create a new signal by its name. */
   Signal& CreateSignal(const std::string& name);

  private:
   uint64_t ident_; ///< Message ID
   std::string name_; ///< Message name.
   std::string comment_; ///< Message description.
   std::string node_; ///< Node (ECU) sender name.
   std::vector<std::string> sender_list_; ///< Also holds the node name

   std::vector<Attribute> attribute_list_; ///< Attribute list.

   SignalList signal_list_; ///< Signal list.

   mutable size_t sample_counter_ = 0; ///< Sample counter.
   std::vector<uint8_t> data_; ///< Store last message and solve >8 byte data
   uint8_t sequence_number_ = 0; ///< Used to verify multibyte package
};

}  // namespace dbc
