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

enum class ProtocolType : int {
  StandardCAN = 0,
  J1939 = 1,
  NMEA2000 = 2,
  OBD2 = 3
};

enum class BusType : int {
  CAN = 0
};

class Network {
 public:
  [[nodiscard]] std::string Name() const;

  void Filename(const std::string& filename) { filename_ = filename;}
  [[nodiscard]] std::string Filename() const {return filename_;};

  void Protocol(ProtocolType type);
  [[nodiscard]] ProtocolType Protocol() const;
  [[nodiscard]] std::string ProtocolAsString() const;

  void Bus(BusType type);
  [[nodiscard]] BusType Bus() const;
  [[nodiscard]] std::string BusAsString() const;

  void Version(const std::string& version) { version_ = version; }
  [[nodiscard]] const std::string& Version() const {
    return version_;
  }

  void Comment(const std::string& comment) {
    comment_ = comment;
  }
  [[nodiscard]] const std::string& Comment() const { return comment_; }

  [[nodiscard]] Node* GetNode(const std::string& name);
  [[nodiscard]] const Node* GetNode(const std::string& name) const;
  [[nodiscard]] const Node* GetNodeBySource(uint8_t source) const;

  void J1939(bool j1939) {j1939_ = j1939;}
  [[nodiscard]] bool J1939() const {return j1939_;}

  [[nodiscard]] Message* GetMessage(uint64_t message_id);
  [[nodiscard]] const Message* GetMessage(uint64_t message_id) const;
  [[nodiscard]] Message* GetMessageByCanId(uint64_t can_id);
  [[nodiscard]] const Message* GetMessageByCanId(uint64_t can_id) const;
  [[nodiscard]] const Message* GetMessageByName(const std::string &name) const;
  [[nodiscard]] Message* GetMessageByPgn(uint32_t pgn);
  [[nodiscard]] Message* GetMessageByPgnAndSource(uint32_t pgn, uint8_t source);
  [[nodiscard]] Signal* GetSignal(uint64_t message_id,
                                  const std::string& signal_name);

  [[nodiscard]] const Signal* GetSignal(uint64_t message_id,
                          const std::string& signal_name) const;

  [[nodiscard]] const Signal* GetSignalByCanId(uint64_t can_id,
                                        const std::string& signal_name) const;

  [[nodiscard]] const Signal* GetSignalByName(
      const std::string& signal_name) const;

  [[nodiscard]] const SignalGroup* GetSignalGroup(uint64_t message_id,
                                        const std::string& name) const;

  [[nodiscard]] const SignalGroup* GetSignalGroupByName(
      const std::string& name) const;

  [[nodiscard]] const std::map<std::string, EnvVar>& EnvVars() const {
    return env_var_list_;
  }

  [[nodiscard]] const std::map<uint64_t, Message>& Messages() const {
    return message_list_;
  }

  [[nodiscard]] const std::map<std::string, Node>& Nodes() const {
    return node_list_;
  }

  [[nodiscard]] const std::vector<SignalGroup>& SignalGroups() const {
    return signal_group_list_;
  }

  [[nodiscard]] const std::map<std::string, EnumMap>& Enums() const {
    return value_table_list_;
  }


  [[nodiscard]] const std::vector<Attribute>& Attributes() const {
    return attribute_list_;
  }
  [[nodiscard]] Attribute* GetAttribute(const std::string& name);
  [[nodiscard]] const Attribute* GetAttribute(const std::string& name) const;

  void AddValueTable(const std::string& name, const EnumMap& list);
  void AddSignalGroup(const SignalGroup& group);

  // Parser only functions
  [[nodiscard]] EnvVar& GetEnvVar(const std::string& name);
  [[nodiscard]] Node& CreateNode(const std::string& name);
  [[nodiscard]] Attribute& CreateDefinition(const std::string& name);
  [[nodiscard]] Attribute& CreateAttribute(const Attribute& definition);
  [[nodiscard]] Message& CreateMessage(uint64_t message_id);
  [[nodiscard]] Message*  LastMessage();
 private:
  std::string filename_;
  std::string version_;
  std::string comment_;
  std::map<std::string, EnvVar> env_var_list_;
  uint64_t last_message_id_ = 0;
  bool j1939_ = false; ///< Indicate if this is a J1939 network

  // Only define the name and type of value
  std::map<std::string, Attribute> definition_list_;
  std::vector<Attribute> attribute_list_;
  std::map<std::string, Node> node_list_;
  std::map<uint64_t, Message> message_list_;
  std::map<std::string, EnumMap> value_table_list_;
  std::vector<SignalGroup> signal_group_list_;
};

}  // namespace dbc
