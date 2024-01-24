/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/dbcmessage.h"
#include <vector>
#include <pybind11/stl.h>

using namespace pybind11;
using namespace dbc;

namespace {
DbcMessage CreateDbcMessage(uint64_t time,
                            uint32_t can_id,
                            const list& data) {
  const auto temp_list =  data.cast<std::vector<uint8_t>>();
  return {time, can_id, temp_list};
}

}

namespace pydbc {

void InitDbcMessage(pybind11::module& m) {
  constexpr std::string_view msg_doc = R"(
Wrapper class around a CAN message.

Simple support class that holds a CAN message. CAN message has a time, ID
and none or more data bytes. This sound simple but there are several
protocols on top of CAN that treat the CAN ID and its data bytes
differently.
)";

  auto msg = class_<DbcMessage>(m, "DbcMessage", msg_doc.data());
  msg.def(init<>());

  constexpr std::string_view msg_init_doc = R"(
Constructor that wraps a CAN message.

Constructor that wraps a CAN message.

Attributes:
  time: Nano-seconds since 1970.
  can_id: 11/29-bit CAN ID.
  data: CAN data bytes.
)";
  msg.def(init(&CreateDbcMessage),
      msg_init_doc.data(), "ns1970"_a, "can_id"_a, "message"_a);

  msg.def_property("time",
                   [] (DbcMessage& self) {return self.Time();},
                   [] (DbcMessage& self, uint64_t ns1970) {self.Time(ns1970);});
  msg.def_property("can_id",
                   [] (DbcMessage& self) {return self.CanId();},
                   [] (DbcMessage& self, uint32_t can_id) {self.CanId(can_id);});
  msg.def_property("data",
                   [] (DbcMessage& self) {
                     pybind11::list temp_list = pybind11::cast(self.Data());
                     return temp_list;
                   },
                   [] (DbcMessage& self, const pybind11::list& data_list) {
                     self.Data(data_list.cast<std::vector<uint8_t>>());
                   });
  msg.def_property_readonly("pgn", &DbcMessage::Pgn);
  msg.def_property_readonly("priority", &DbcMessage::Priority);
  msg.def_property_readonly("extended_data_page",
                            &DbcMessage::ExtendedDataPage);
  msg.def_property_readonly("data_page", &DbcMessage::DataPage);
  msg.def_property_readonly("pdu_format", &DbcMessage::PduFormat);
  msg.def_property_readonly("pdu_specific", &DbcMessage::PduSpecific);
  msg.def_property_readonly("source", &DbcMessage::Source);
}



} // pydbc



