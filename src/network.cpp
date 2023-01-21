/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/network.h"
#include "dbchelper.h"
#include <algorithm>
namespace dbc {

EnvVar& Network::GetEnvVar(const std::string& name) {
  auto itr = env_var_list_.find(name);
  if (itr == env_var_list_.end()) {
    EnvVar temp;
    temp.Name(name);
    itr = env_var_list_.insert({name, temp}).first;
  }
  return itr->second;
}

Attribute& Network::CreateDefinition(const std::string& name) {
  auto itr = definition_list_.find(name);
  if (itr == definition_list_.end()) {
    Attribute temp(AttributeType::DbcNetwork, name);
    itr = definition_list_.insert({name, temp}).first;
  }
  return itr->second;
}

Attribute& Network::CreateAttribute(const Attribute& definition) {
  Attribute temp(definition);
  attribute_list_.emplace_back(temp);
  return attribute_list_.back();
}

Node* Network::GetNode(const std::string& name) {
  auto itr = node_list_.find(name);
  return itr != node_list_.end() ? &itr->second : nullptr;
}

const Node* Network::GetNode(const std::string& name) const {
  const auto itr = node_list_.find(name);
  return itr != node_list_.cend() ? &itr->second : nullptr;
}

const Node* Network::GetNodeBySource(uint8_t source) const {
  const auto itr = std::find_if(node_list_.cbegin(), node_list_.cend(),
                                [&] (const NodeList::value_type& itr1) {
    return itr1.second.Source() == source;
  });
  return itr != node_list_.cend() ? &itr->second : nullptr;
}

Message* Network::GetMessage(uint64_t message_id) {
  auto itr = message_list_.find(message_id);
  return itr != message_list_.end() ? &itr->second : nullptr;
}

const Message* Network::GetMessage(uint64_t message_id) const {
  const auto itr = message_list_.find(message_id);
  return itr != message_list_.cend() ? &itr->second : nullptr;
}

Message* Network::GetMessageByCanId(uint64_t can_id) {
  auto itr = std::find_if(message_list_.begin(),
                          message_list_.end(),
                          [&] (const MessageList ::value_type &mess) {
    return mess.second.CanId() == can_id;
  });
  return itr != message_list_.end() ? &itr->second : nullptr;
}

const Message* Network::GetMessageByCanId(uint64_t can_id) const {
  const auto itr = std::find_if(message_list_.cbegin(),
                                message_list_.cend(),
                              [&] (const MessageList ::value_type &mess) {
      return mess.second.CanId() == can_id;
    });
  return itr != message_list_.cend() ? &itr->second : nullptr;
}

const Message* Network::GetMessageByName(const std::string& name) const {
  const auto itr = std::find_if(message_list_.cbegin(), message_list_.cend(),
                                [&] (const MessageList::value_type &mess) {
    return mess.second.Name() == name;
  });
  return itr != message_list_.cend() ? &itr->second : nullptr;
}

Message* Network::GetMessageByPgn(uint32_t pgn) {
  auto itr = std::find_if(message_list_.begin(), message_list_.end(),
                          [&] (const MessageList::value_type &mess) {
    return mess.second.Pgn() == pgn;
  });
  return itr != message_list_.end() ? &itr->second : nullptr;
}

Message* Network::GetMessageByPgnAndSource(uint32_t pgn, uint8_t source) {
  auto itr = std::find_if(message_list_.begin(), message_list_.end(),
                          [&] (const MessageList::value_type& mess) {
    return mess.second.Pgn() == pgn && mess.second.Source() == source;
  });
  return itr != message_list_.end() ? &itr->second : nullptr;
}

Signal* Network::GetSignal(uint64_t message_id,
                           const std::string& signal_name) {
  auto* message = GetMessage(message_id);
  return message != nullptr ? message->GetSignal(signal_name) : nullptr;
}

const Signal* Network::GetSignal(uint64_t message_id,
                                 const std::string& signal_name) const {
  const auto* message = GetMessage(message_id);
  return message != nullptr ? message->GetSignal(signal_name) : nullptr;
}

const Signal* Network::GetSignalByCanId(uint64_t can_id,
                                 const std::string& signal_name) const {
  const auto* message = GetMessageByCanId(can_id);
  return message != nullptr ? message->GetSignal(signal_name) : nullptr;
}

const Signal* Network::GetSignalByName( const std::string& signal_name) const {
  for (const auto& mess : message_list_) {
    const auto& message = mess.second;
    const auto* signal = message.GetSignal(signal_name);
    if (signal != nullptr) {
      return signal;
    }
  }
  return nullptr;
}

const SignalGroup* Network::GetSignalGroup(uint64_t message_id,
                           const std::string& name) const {
  const auto itr = std::find_if(signal_group_list_.cbegin(),
                                signal_group_list_.cend(),
                                        [&] (const SignalGroup& group) {
    return group.MessageId() == message_id &&
           group.Name() == name;
  });
  return itr != signal_group_list_.cend() ? &(*itr) : nullptr;
}

const SignalGroup* Network::GetSignalGroupByName(
    const std::string& name) const {
  const auto itr = std::find_if(signal_group_list_.cbegin(),
                                signal_group_list_.cend(),
                                        [&] (const SignalGroup& group) {
    return group.Name() == name;
  });
  return itr != signal_group_list_.cend() ? &(*itr) : nullptr;
}

Message& Network::CreateMessage(uint64_t message_id) {
  auto itr = message_list_.find(message_id);
  if (itr == message_list_.end()) {
    Message temp;
    temp.Ident(message_id);
    itr = message_list_.insert({message_id, temp}).first;
  }
  last_message_id_ = message_id;
  return itr->second;
}

Message* Network::LastMessage() {
  return GetMessage(last_message_id_);
}

Node& Network::CreateNode(const std::string& name) {
  auto itr = node_list_.find(name);
  if (itr == node_list_.end()) {
    Node temp;
    temp.Name(name);
    itr = node_list_.insert({name, temp}).first;
  }
  return itr->second;
}

void Network::AddValueTable(const std::string& name, const EnumMap& list) {
  auto itr = value_table_list_.find(name);
  if (itr == value_table_list_.end()) {
    itr = value_table_list_.insert({name, list}).first;
  } else {
    itr->second = list;
  }
}

void Network::AddSignalGroup(const SignalGroup& group) {
  signal_group_list_.push_back(group);
}

std::string Network::Name() const {
  // Plan A is to return attribute DBName.
  // Plan B is to return the file name (stem).
  const auto* db_name = GetAttribute("DBName");
  if (db_name != nullptr) {
    return db_name->Value<std::string>();
  }
  return DbcHelper::GetStem(filename_);
}

Attribute* Network::GetAttribute(const std::string& name) {
  auto itr = std::find_if(attribute_list_.begin(), attribute_list_.end(),
                          [&] (const Attribute& attribute) {
    return attribute.Name() == name;
  });
  return itr != attribute_list_.end() ? &(*itr) : nullptr;
}

const Attribute* Network::GetAttribute(const std::string& name) const {
  const auto itr = std::find_if(attribute_list_.cbegin(),
                                attribute_list_.cend(),
                                        [&] (const Attribute& attribute) {
    return attribute.Name() == name;
  });
  return itr != attribute_list_.cend() ? &(*itr) : nullptr;
}

void Network::Protocol(ProtocolType type) {
  auto* protocol = GetAttribute("ProtocolType");
  if (protocol == nullptr) {
    auto& definition = CreateDefinition("ProtocolType");
    definition.Type(AttributeType::DbcNetwork);
    definition.ValueType(AttributeValueType::StringValue);
    auto& temp = CreateAttribute(definition);
    protocol = &temp;
  }
  switch (type) {
    case ProtocolType::J1939:
      protocol->Value(std::string("J1939"));
      break;

    case ProtocolType::NMEA2000:
      protocol->Value(std::string("NMEA2000"));
      break;

    case ProtocolType::OBD2:
      protocol->Value(std::string("OBD2"));
      break;

    default:
      protocol->Value(std::string("StandardCAN"));
      break;
  }
}

ProtocolType Network::Protocol() const {
  const auto* temp = GetAttribute("ProtocolType");
  if (temp != nullptr && temp->Value<std::string>() == "J1939") {
    return ProtocolType::J1939;
  } else if (temp != nullptr && temp->Value<std::string>() == "J1939PG") {
      return ProtocolType::J1939;
  } else if (temp != nullptr && temp->Value<std::string>() == "OBD2") {
      return ProtocolType::OBD2;
  } else if (temp != nullptr && temp->Value<std::string>() == "NMEA2000") {
      return ProtocolType::NMEA2000;
  }
  return ProtocolType::StandardCAN;
}

std::string Network::ProtocolAsString() const {
  switch (Protocol()) {
    case ProtocolType::J1939:
      return "J1939";

    case ProtocolType::NMEA2000:
      return "NMEA 2000";

    case ProtocolType::OBD2:
      return "OBD2";

    default:
      break;
  }
  return "Standard CAN";
}

void Network::Bus(BusType type) {
  auto* bus = GetAttribute("BusType");
  if (bus == nullptr) {
    auto& definition = CreateDefinition("BusType");
    definition.Type(AttributeType::DbcNetwork);
    definition.ValueType(AttributeValueType::StringValue);
    auto& temp = CreateAttribute(definition);
    bus = &temp;
  }
  bus->Value(std::string("CAN"));
}

BusType Network::Bus() const {
  return BusType::CAN;
}

std::string Network::BusAsString() const {
  return "CAN";
}

}  // namespace dbc