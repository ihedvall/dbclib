/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
/** \file signalgroup.h
 * \brief Defines a signal group.
 */
#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace dbc {

/** \brief Interface against a signal group. */
class SignalGroup {
 public:
  /** \brief Sets the message ID. */
  void MessageId(uint64_t message_id) { message_id_ = message_id; }
  /** \brief Returns the message ID. */
  [[nodiscard]] uint64_t MessageId() const { return message_id_; }

  void Name( const std::string& name) { name_ = name; } ///< Sets the name.
  [[nodiscard]] const std::string& Name() const { return name_; } ///< Name

  void Repetition(size_t rep) { repetition_ = rep; } ///< Sets the repetition.
  [[nodiscard]] size_t Repetition() const {return repetition_;} ///< Repetition

  /** \brief Returns a list of signal names. */
  void Signals(const std::vector<std::string>& signals );
  /** \brief Returns a list of signal names. */
  [[nodiscard]] const std::vector<std::string>& Signals() const;

 private:
  uint64_t message_id_ = 0; ///< Message eID.
  std::string name_; ///< Name.
  size_t repetition_ = 1; ///< Repetition.
  std::vector<std::string> signal_list_; ///< Signal list.
};

}  // namespace dbc
