/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#include "dbcscanner.h"
#include <memory>
namespace dbc {

DbcScanner::DbcScanner(std::ifstream& message)
    : ddFlexLexer(&message), yylval(nullptr) {

}

Network& DbcScanner::GetNetwork() {
  if (!network_) {
    network_ .reset(new Network);
  }
  return *network_;
}

void DbcScanner::AddToStringList(const std::string& text) {
  string_list_.emplace_back(text);
}

const std::vector<std::string>& DbcScanner::StringList() const {
  return string_list_;
}

void DbcScanner::AddToEnumList(int64_t index, const std::string& text) {
  enum_list_.insert({index, text});
}

const std::map<int64_t, std::string>& DbcScanner::EnumList() const {
  return enum_list_;
}

void DbcScanner::ResetTempList() {
  enum_list_.clear();
  string_list_.clear();
  range_list_.clear();
}
void DbcScanner::AddToRangeList(size_t low, size_t high) {
  range_list_.emplace_back(low, high);
}

const std::vector<std::pair<size_t, size_t>>& DbcScanner::RangeList() const {
  return range_list_;
}

}  // namespace util::syslog