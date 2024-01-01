/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once

#include <dbc/dbcfile.h>
namespace pydbc {

 class PyDbcFile : public dbc::DbcFile {
 public:
  void SetFilename(const std::string &filename) { Filename(filename); }
  [[nodiscard]] const std::string &GetFilename() const { return Filename(); }

  void SetBaseTime(uint64_t ns1970) { BaseTime(ns1970); }
  [[nodiscard]] uint64_t GetBaseTime() const { return BaseTime(); }

  void SetMessageSize(size_t nof_messages) { MessageSize(nof_messages); }
  [[nodiscard]] size_t GetMessageSize() const { return MessageSize(); }

};

} // End namespace pydbc