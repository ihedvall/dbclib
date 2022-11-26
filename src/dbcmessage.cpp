/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include <utility>

#include "dbc/dbcmessage.h"

namespace dbc {

DbcMessage::DbcMessage(uint64_t time, uint32_t can_id,
                       std::vector<uint8_t>  data)
  : time_(time),
    can_id_(can_id),
    data_(std::move(data)) {
}

uint32_t DbcMessage::Pgn() const {
  auto temp = can_id_;
  temp >>=  8;
  temp &= 0x3FFFF;
  return static_cast<uint32_t>(temp);
}

uint8_t DbcMessage::Priority() const {
  auto temp = can_id_;
  temp >>= 18 + 8;
  return static_cast<uint8_t>(temp);
}

uint8_t DbcMessage::Source() const {
  auto temp = can_id_;
  temp &= 0xFF;
  return static_cast<uint8_t>(temp);
}

bool DbcMessage::ExtendedDataPage() const {
  return (can_id_ & 0x20000) != 0;
}

bool DbcMessage::DataPage() const {
  return (can_id_ & 0x10000) != 0;
}

uint8_t DbcMessage::PduFormat() const {
  return static_cast<uint8_t >((can_id_ & 0xFF00) >> 8);
}

uint8_t DbcMessage::PduSpecific() const {
  return static_cast<uint8_t>(can_id_ & 0xFF);
}
}  // namespace dbc