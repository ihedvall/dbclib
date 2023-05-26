/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */
/** \file dbcmessage.h
 * \brief Wrapper around a CAN message.
 */
#pragma once
#include <cstdint>
#include <vector>

namespace dbc {

/** \brief Wrapper class around a CAN message.
 *
 * Simple support class that holds a CAN message. CAN message has a time, ID
 * and none or more data bytes. This sound simple but there are several
 * protocols on top of CAN that treat the CAN ID and its data bytes
 * differently.
 */
class DbcMessage {
 public:
  DbcMessage() = default; ///< Default constructor.
  /** \brief Constructor that wraps a CAN message.
   *
   * Constructor that wraps a CAN message.
   * @param time Nano-seconds since 1970.
   * @param can_id 11/29-bit CAN ID.
   * @param data CAN data bytes.
   */
  DbcMessage(uint64_t time, uint32_t can_id, std::vector<uint8_t>  data);
  DbcMessage(const DbcMessage& message) = default; ///< Default destructor.


  void Time(uint64_t ns1970) {time_ = ns1970;} ///< Sets the time.
  [[nodiscard]] uint64_t Time() const {return time_;} ///< Message time.

  void CanId(uint32_t can_id) {can_id_ = can_id;} ///< Sets the CAN ID.
  [[nodiscard]] uint32_t CanId() const {return can_id_;} ///< CAN ID.

  /** \brief Sets the CAN data bytes. */
  void Data(const std::vector<uint8_t>& data) {data_ = data;}
  /** \brief Returns the CAN data bytes. */
  [[nodiscard]] const std::vector<uint8_t>& Data() const {return data_;}

  [[nodiscard]] uint32_t Pgn() const; ///< PGN Program number
  [[nodiscard]] uint8_t Priority() const; ///< Priority (0-8)
  [[nodiscard]] bool ExtendedDataPage() const; ///< True if extended data page.
  [[nodiscard]] bool DataPage() const; ///< True if data page.
  [[nodiscard]] uint8_t PduFormat() const; ///< PDU format.
  [[nodiscard]] uint8_t PduSpecific() const; ///< PDU specific.
  [[nodiscard]] uint8_t Source() const; ///< Source number.
 private:
  uint64_t time_ = 0;         ///< Nanoseconds since 1970
  uint32_t can_id_ = 0;       ///< 29-bit CAN ID
  std::vector<uint8_t> data_; ///< Data bytes
};

}  // namespace dbc
