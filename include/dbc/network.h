/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
*/

#pragma once
#include <vector>
#include <map>
#include "dbc/envvar.h"
#include "dbc/attribute.h"
#include "dbc/node.h"
#include "dbc/message.h"
#include "dbc/signal.h"
#include "dbc/signalgroup.h"

namespace dbc {

using EnumMap = std::map<int64_t, std::string>;

class Network {
 public:
  void Version(const std::string& version) { version_ = version; }
  [[nodiscard]] const std::string& Version() const {
    return version_;
  }

  void Comment(const std::string& comment) { comment_ = comment; }
  [[nodiscard]] const std::string& Comment() const { return comment_; }

  Node* GetNode(const std::string& name);
  Message* GetMessage(uint64_t message_id);
  Signal* GetSignal(uint64_t message_id, const std::string& signal_name);

  [[nodiscard]] const std::map<std::string, EnvVar>& EnvVars() const {
    return env_var_list_;
  }

  [[nodiscard]] const std::map<uint64_t, Message>& Messages() const {
    return message_list_;
  }

  void AddValueTable(const std::string& name, const EnumMap& list);
  void AddSignalGroup(const SignalGroup& group);

  // Parser only functions
  [[nodiscard]] EnvVar& GetEnvVar(const std::string& name);
  [[nodiscard]] Node& CreateNode(const std::string& name);
  [[nodiscard]] Attribute& GetDefinition(const std::string& name);
  [[nodiscard]] Attribute& CreateAttribute(const Attribute& definition);
  [[nodiscard]] Message& CreateMessage(uint64_t message_id);
  [[nodiscard]] Message*  LastMessage();
 private:


  std::string version_;
  std::string comment_;
  std::map<std::string, EnvVar> env_var_list_;
  uint64_t last_message_id_ = 0;

  // Only define the ame and type of value
  std::map<std::string, Attribute> definition_list_;
  std::vector<Attribute> attribute_list_;
  std::map<std::string, Node> node_list_;
  std::map<uint64_t, Message> message_list_;
  std::map<std::string, EnumMap> value_table_list_;
  std::vector<SignalGroup> signal_group_list_;
};

}  // namespace dbc
