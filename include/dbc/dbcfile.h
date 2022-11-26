/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once
#include <string>
#include <memory>
#include "dbc/network.h"
#include "dbc/dbcmessage.h"

namespace dbc {

class DbcFile {
 public:
  void Filename(const std::string& filename) {filename_ = filename; }
  [[nodiscard]] const std::string& Filename() const {return filename_; }

  [[nodiscard]] std::string Name() const;

  [[nodiscard]] const std::string& LastError() const { return last_error_; }
  [[nodiscard]] Network* GetNetwork() { return network_.get(); }
  [[nodiscard]] const Network* GetNetwork() const { return network_.get(); }

  [[nodiscard]] bool ParseFile();
  void BaseTime(uint64_t ns1970) {base_time_ = ns1970;}
  [[nodiscard]] uint64_t BaseTime() const {return base_time_;}
  void SetMessageSize(size_t nof_messages);
  void AddMessage(size_t index, const DbcMessage& message);
  bool ParseMessage(const DbcMessage& message);
  void ResetSampleCounter() const;
  void ReparseMessageList();

 private:
  bool ParseStandardCAN(const DbcMessage& message);
  bool ParseJ1939(const DbcMessage& message);
  bool ParseNMEA2000(const DbcMessage& message);
  std::string filename_; ///< Full path name
  mutable std::string last_error_; ///< Last error message
  std::unique_ptr<Network> network_;
  std::vector<DbcMessage> message_list_;
  uint64_t base_time_ = 0;
};

}  // namespace dbc
