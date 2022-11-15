/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include <fstream>
#include <string>
#include <memory>

#ifndef yyFlexLexerOnce

#undef yyFlexLexer
#define yyFlexLexer ddFlexLexer
#include <FlexLexer.h>

#endif

#include "dbcparser.hpp"
#include "dbc/network.h"
#include <vector>
#include <map>
namespace dbc {


class DbcScanner : public ddFlexLexer  {
 public:
  explicit DbcScanner(std::ifstream& in);
  int ddlex(DbcParser::value_type* yylval);

  Network& GetNetwork();

  void AddToStringList(const std::string& text);
  [[nodiscard]] const std::vector<std::string>& StringList() const;

  void AddToEnumList(int64_t index, const std::string& text);
  [[nodiscard]] const std::map<int64_t, std::string>& EnumList() const;

  void AddToRangeList(size_t low, size_t high);
  [[nodiscard]] const std::vector<std::pair<size_t, size_t>>& RangeList() const;

  void ResetTempList();

  void LastError(const std::string& error) { last_error_ = error; }
  [[nodiscard]] const std::string& LastError() const { return last_error_; }

  Network* ReleaseNetwork() { return network_.release(); }

 private:
  std::ostringstream utf8_stream_;
  DbcParser::semantic_type* yylval = nullptr;
  std::unique_ptr<Network> network_;

  std::vector<std::string> string_list_; ///< Temporary storage of text strings
  std::map<int64_t, std::string> enum_list_; ///< Temporary storage of enums
  std::vector<std::pair<size_t, size_t>> range_list_;

  std::string last_error_;
};

}  // namespace util::syslog
