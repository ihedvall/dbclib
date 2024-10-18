/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
*/
/** \file network.h
 * \brief Defines a DBC network configuration object.
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
/** \brief Enumerate list. */
using EnumMap = std::map<int64_t, std::string>;

/** \brief Type of CAN protocol. */
enum class ProtocolType : int {
  StandardCAN = 0, ///< Standard CAN.
  J1939 = 1, ///< J1939 protocol.
  NMEA2000 = 2, ///< NMEA protocol.
  OBD2 = 3 ///< OBD2 protocol.
};

/** \brief Type of bus. */
enum class BusType : int {
  CAN = 0, ///< CAN bus
  CAN_FD   ///< CAN FD bus
};

/** \brief Sorted message of messages. Message ID is the key. */
using MessageList = std::map<uint64_t, Message>;

/** \brief Interface against a DBC network configuration. */
class Network {
 public:
  [[nodiscard]] std::string Name() const; ///< Network name.

  /** \brief Sets the file name. */
  void Filename(const std::string& filename) { filename_ = filename;}
  /** \brief Returns the file name. */
  [[nodiscard]] std::string Filename() const {return filename_;};

  /** \brief Sets the protocol type. Should be included in the file but
   * sometimes is missing.
   * @param type Type of protocol.
   */
  void Protocol(ProtocolType type);
  /** \brief Returns what type of protocol the bus is using. */
  [[nodiscard]] ProtocolType Protocol() const;
  /** \brief Returns the network protocol as text. */
  [[nodiscard]] std::string ProtocolAsString() const;

  /** \brief Sets the type of bus. */
  void Bus(BusType type);
  /** \brief Returns the type of bus. */
  [[nodiscard]] BusType Bus() const;
  /** \brief Returns the type of bus as text. */
  [[nodiscard]] std::string BusAsString() const;

  /** \brief Sets the DBC (file) version. */
  void Version(const std::string& version) { version_ = version; }
  /** \brief Returns the DBC file version. */
  [[nodiscard]] const std::string& Version() const {
    return version_;
  }
  /** \brief Sets the descriptive text for the DBC file. */
  void Comment(const std::string& comment) {
    comment_ = comment;
  }
  /** \brief Returns the descriptive text. */
  [[nodiscard]] const std::string& Comment() const { return comment_; }

  /** \brief Returns the node by its name. */
  [[nodiscard]] Node* GetNode(const std::string& name);
  /** \brief Returns the node by its name. */
  [[nodiscard]] const Node* GetNode(const std::string& name) const;
  /** \brief Returns the node by its source number. */
  [[nodiscard]] const Node* GetNodeBySource(uint8_t source) const;

  /** \brief Set to true if this is a J1939 bus. */
  void J1939(bool j1939) {j1939_ = j1939;}
  /** \brief Returns true if this is a J1939 bus. */
  [[nodiscard]] bool J1939() const {return j1939_;}

  /** \brief Returns a message object by its message ID. */
  [[nodiscard]] Message* GetMessage(uint64_t message_id);
  /** \brief Returns a message object by its message ID. */
  [[nodiscard]] const Message* GetMessage(uint64_t message_id) const;
  /** \brief Returns a message object by its CAN ID. */
  [[nodiscard]] Message* GetMessageByCanId(uint64_t can_id);
  /** \brief Returns a message object by its CAN ID. */
  [[nodiscard]] const Message* GetMessageByCanId(uint64_t can_id) const;
  /** \brief Returns a message object by its name. */
  [[nodiscard]] const Message* GetMessageByName(const std::string &name) const;
  /** \brief Returns a message object by its PGN. */
  [[nodiscard]] Message* GetMessageByPgn(uint32_t pgn);
  /** \brief Returns a message object by its PGN and source number. */
  [[nodiscard]] Message* GetMessageByPgnAndSource(uint32_t pgn, uint8_t source);

  /** \brief Returns a signal by its message ID and signal name. */
  [[nodiscard]] Signal* GetSignal(uint64_t message_id,
                                  const std::string& signal_name);
  /** \brief Returns a signal by its message ID and signal name. */
  [[nodiscard]] const Signal* GetSignal(uint64_t message_id,
                          const std::string& signal_name) const;
  /** \brief Returns a signal by its CAN ID and signal name. */
  [[nodiscard]] const Signal* GetSignalByCanId(uint64_t can_id,
                                        const std::string& signal_name) const;
  /** \brief Returns a signal by its name. */
  [[nodiscard]] const Signal* GetSignalByName(
      const std::string& signal_name) const;

  /** \brief Returns a signal group by its message ID and group name. */
  [[nodiscard]] const SignalGroup* GetSignalGroup(uint64_t message_id,
                                        const std::string& name) const;
  /** \brief Returns a signal group by its group name. */
  [[nodiscard]] const SignalGroup* GetSignalGroupByName(
      const std::string& name) const;

  /** \brief Returns the list of environment variables. */
  [[nodiscard]] const std::map<std::string, EnvVar>& EnvVars() const {
    return env_var_list_;
  }

  /** \brief Returns the list of messages. */
  [[nodiscard]] const MessageList& Messages() const {
    return message_list_;
  }

  /** \brief Returns the list of Nodes. */
  [[nodiscard]] const std::map<std::string, Node>& Nodes() const {
    return node_list_;
  }

  /** \brief Returns the list of signal groups. */
  [[nodiscard]] const std::vector<SignalGroup>& SignalGroups() const {
    return signal_group_list_;
  }

  /** \brief Returns the list of enumerates. */
  [[nodiscard]] const std::map<std::string, EnumMap>& Enums() const {
    return value_table_list_;
  }

  /** \brief Returns the list of attributes. */
  [[nodiscard]] const std::vector<Attribute>& Attributes() const {
    return attribute_list_;
  }
  /** \brief Returns an attribute by its name. */
  [[nodiscard]] Attribute* GetAttribute(const std::string& name);
  /** \brief Returns an attribute by its name. */
  [[nodiscard]] const Attribute* GetAttribute(const std::string& name) const;

  /** \brief Adds a enumerate. */
  void AddValueTable(const std::string& name, const EnumMap& list);

  /** \brief Adds a signal group. */
  void AddSignalGroup(const SignalGroup& group);

  // Parser only functions
  /** \brief Parser function that gets/creates an environment variable. */
  [[nodiscard]] EnvVar& GetEnvVar(const std::string& name);
  /** \brief Parser function that creates a node. */
  [[nodiscard]] Node& CreateNode(const std::string& name);
  /** \brief Parser function that creates a definition. */
  [[nodiscard]] Attribute& CreateDefinition(const std::string& name);
  /** \brief Parser function that creates an attribute. */
  [[nodiscard]] Attribute& CreateAttribute(const Attribute& definition);
  /** \brief Parser function that creates a message. */
  [[nodiscard]] Message& CreateMessage(uint64_t message_id);
  /** \brief Returns the last message. */
  [[nodiscard]] Message*  LastMessage();
 private:
  std::string filename_; ///< File name with path and extension.
  std::string version_; ///< File version.
  std::string comment_; ///< File description.
  std::map<std::string, EnvVar> env_var_list_; ///< Environment list.
  uint64_t last_message_id_ = 0; ///< Parser to track current message.
  bool j1939_ = false; ///< Indicate if this is a J1939 network

  // Only define the name and type of value
  std::map<std::string, Attribute> definition_list_; ///< Definition list.
  std::vector<Attribute> attribute_list_; ///< Attribute list.

  using NodeList = std::map<std::string, Node>; ///< Sorted node list.
  NodeList node_list_; ///< Node list.
  MessageList message_list_; ///< Message list.

  std::map<std::string, EnumMap> value_table_list_; ///< Enum list.
  std::vector<SignalGroup> signal_group_list_; ///< Signal group list.
};

}  // namespace dbc
