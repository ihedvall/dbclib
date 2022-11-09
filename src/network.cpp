//
// Created by ihedv on 2022-11-04.
//

#include "dbc/network.h"

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

Attribute& Network::GetDefinition(const std::string& name) {
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

Message* Network::GetMessage(uint64_t message_id) {
  auto itr = message_list_.find(message_id);
  return itr != message_list_.end() ? &itr->second : nullptr;
}

Signal* Network::GetSignal(uint64_t message_id,
                           const std::string& signal_name) {
  auto* message = GetMessage(message_id);
  return message != nullptr ? message->GetSignal(signal_name) : nullptr;
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

}  // namespace dbc