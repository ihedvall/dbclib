/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once
#include <cstdint>
#include <vector>

namespace dbc {

class DbcMessage {
 public:
  DbcMessage() = default;
  DbcMessage(uint64_t time, uint32_t can_id, std::vector<uint8_t>  data);
  DbcMessage(const DbcMessage& message) = default;
  void Time(uint64_t ns1970) {time_ = ns1970;}
  [[nodiscard]] uint64_t Time() const {return time_;}

  void CanId(uint32_t can_id) {can_id_ = can_id;}
  [[nodiscard]] uint32_t CanId() const {return can_id_;}

  void Data(const std::vector<uint8_t>& data) {data_ = data;}
  [[nodiscard]] const std::vector<uint8_t>& Data() const {return data_;}

  [[nodiscard]] uint32_t Pgn() const;
  [[nodiscard]] uint8_t Priority() const;
  [[nodiscard]] bool ExtendedDataPage() const;
  [[nodiscard]] bool DataPage() const;
  [[nodiscard]] uint8_t PduFormat() const;
  [[nodiscard]] uint8_t PduSpecific() const;
  [[nodiscard]] uint8_t Source() const;
 private:
  uint64_t time_ = 0;         ///< Nanoseconds since 1970
  uint32_t can_id_ = 0;       ///< 29-bit CAN ID
  std::vector<uint8_t> data_; ///< Data bytes
};

}  // namespace dbc
