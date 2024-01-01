/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once
#include <dbc/dbcmessage.h>

namespace pydbc {

 class PyDbcMessage : public dbc::DbcMessage {
  public:
   void SetTime(uint64_t ns1970) { Time(ns1970); }
   [[nodiscard]] uint64_t GetTime() const  { return Time(); }

};

} // pydbc

