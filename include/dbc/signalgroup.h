/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace dbc {

class SignalGroup {
 public:
  void MessageId(uint64_t message_id) { message_id_ = message_id; }
  [[nodiscard]] uint64_t MessageId() const { return message_id_; }

  void Name( const std::string& name) { name_ = name; }
  [[nodiscard]] const std::string& Name() const { return name_; }

  void Repetition(size_t rep) { repetition_ = rep; }
  [[nodiscard]] size_t Repetition() const { return repetition_; }

  void Signals(const std::vector<std::string>& signals );
  [[nodiscard]] const std::vector<std::string>& Signals() const;

 private:
  uint64_t message_id_ = 0;
  std::string name_;
  size_t repetition_ = 1;
  std::vector<std::string> signal_list_;
};

}  // namespace dbc
