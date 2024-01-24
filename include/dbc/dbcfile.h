/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */
/** \file dbcfile.h
 * \brief The DBC file object is the main user object.
 */
#pragma once
#include <string>
#include <memory>
#include "dbc/network.h"
#include "dbc/dbcmessage.h"

namespace dbc {

/** \brief Main user object that is an interface against a DBC file.
 *
 * The DBC file is the only object the user shall create. It handle the parsing
 * of the file. A DBC file defines nodes, messages and signals for one CAN
 * network.
 */
class DbcFile {
 public:
  /** \brief Sets the file name. Full path required. */
  void Filename(const std::string& filename) {filename_ = filename; }
  /** \brief Returns the file name with full path. */
  [[nodiscard]] const std::string& Filename() const {return filename_; }

  /** \brief Returns the File name without path and extension. */
  [[nodiscard]] std::string Name() const;

  /** \brief Returns the last (parser) error text. */
  [[nodiscard]] const std::string& LastError() const { return last_error_; }

  /** \brief Returns the network object. */
  [[nodiscard]] Network* GetNetwork() { return network_.get(); }
  /** \brief Returns the network object. */
  [[nodiscard]] const Network* GetNetwork() const { return network_.get(); }

  /** \brief Parses the DBC file. Returns true on success. */
  [[nodiscard]] bool ParseFile();

  /** \brief Start time of messages.
   *
   * The base time is the time of the first message. If not set, the
   * AddMessage will set it to the first DBCMessage.
   * @param ns1970 Nano-seconds since 1970.
   */
  void BaseTime(uint64_t ns1970) {base_time_ = ns1970;}
  /** \brief Returns the base (start) time of first message. */
  [[nodiscard]] uint64_t BaseTime() const {return base_time_;}

  /** \brief Sets the maximum message queue size. */
  void MessageSize(size_t nof_messages);

  /** \brief Sets the maximum message queue size. */
  [[nodiscard]] size_t MessageSize() const;

  /** \brief Adds a message to the message queue. */
  void AddMessage(size_t index, const DbcMessage& message);
  /** \brief Parses the message into signal values. */
  bool ParseMessage(const DbcMessage& message);
  /** \brief Resets the sample counter for all signals. */
  void ResetSampleCounter() const;
  /** \brief Reparse the message queue.
   *
   * This function is used to reparse the message queue. This function is
   * used when the first parse message round just count number of samples
   * while the next round, the user selects signals (SignalObserver) and
   * reparse the message queue.
   *
   */
  void ReparseMessageList();
  void ClearObserverList();
 private:
  /** \brief Parses standard CAN messages. */
  bool ParseStandardCAN(const DbcMessage& message);
  /** \brief Parses J1939 messages. */
  bool ParseJ1939(const DbcMessage& message);
  /** \brief Parses NMEA2000 messages. */
  bool ParseNMEA2000(const DbcMessage& message);
  std::string filename_; ///< Full path name
  mutable std::string last_error_; ///< Last error message
  std::unique_ptr<Network> network_; ///< Pointer to the network object.
  std::vector<DbcMessage> message_list_; ///< List of CAN messages.
  uint64_t base_time_ = 0; ///< Time that samples times are related to.
};

}  // namespace dbc
