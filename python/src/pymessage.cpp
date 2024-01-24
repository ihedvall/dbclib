/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/message.h"
#include <pybind11/stl.h>
#include "dbc/signal.h"
#include "dbc/attribute.h"

using namespace pybind11;
using namespace dbc;

namespace pydbc {

void InitMessage(pybind11::module& m) {
  constexpr std::string_view msg_doc = R"(
Support object that purpose is to hold one signal value.

support object that is used when parsing CAN messages. The
object hold the last parsed messages signal value.
)";
  auto msg = class_<Message>(m, "Message", msg_doc.data());
  msg.def(init<>());
  msg.def_property("message_id",
                   [](Message& self) {
                     return self.Ident();
                   },[](Message& self, uint64_t ident) {
                     self.Ident(ident);
                   });
  msg.def_property_readonly("extended",&Message::IsExtended,
                            "Returns true if the message uses extended 29-bit address.");
  msg.def_property_readonly("j1939",&Message::IsJ1939,
                            "Returns true if the message uses J1939 address logic.");
  msg.def_property_readonly("can_id",&Message::CanId,
                            "Returns the message CAN ID.");
  msg.def_property_readonly("priority",&Message::Priority,
                            "Returns the J1939 priority.");
  msg.def_property_readonly("pgn",&Message::Pgn, "Returns the J1939 PGN.");
  msg.def_property_readonly("source",&Message::Source, "Returns the J1939 source ID.");
  msg.def_property_readonly("extended_data_page",&Message::ExtendedDataPage,
                            "Returns true if this is a J1939 extended data page.");
  msg.def_property_readonly("data_page",&Message::DataPage,
                            "Returns true if this is a J1939 data page.");
  msg.def_property_readonly("pdu_format",&Message::PduFormat,
      "Returns the J1939 PDU format (PF).");
  msg.def_property_readonly("pdu_specific",&Message::PduSpecific,
                            "Returns the J1939 PDU specific (PS).");
  msg.def_property_readonly("pdu1",&Message::IsPdu1,
                            "Returns true if the message is of type PDU1.");
  msg.def_property_readonly("pdu2",&Message::IsPdu2,
                            "Returns true if the message is of type PDU2.");

  msg.def_property("name",
                   [](Message& self) {
                     return self.Name();
                   },[](Message& self, const std::string& name) {
                     self.Name(name);
                   });
  msg.def_property("comment",
                   [](Message& self) {
                     return self.Comment();
                   },[](Message& self, const std::string& comment) {
                     self.Comment(comment);
                   });
  msg.def_property("nof_bytes",
                   [](Message& self) {
                     return self.NofBytes();
                   },[](Message& self, size_t nof_bytes) {
                     self.NofBytes(nof_bytes);
                   });

  msg.def("add_node", &Message::Node,
                   "Adds a node or sets the node name", "node"_a);
  msg.def_property_readonly("node_name",&Message::NodeName,
                            "Returns the node name.");

  msg.def("get_signal", [] (Message& self, const std::string& name) -> Signal* {
    return self.GetSignal(name);
  }, "Returns the signal object by its name", "name"_a,
          return_value_policy::reference_internal);

  msg.def("get_multiplexor", &Message::GetMultiplexor,
          "Returns the signal object that is the multiplexor",
          return_value_policy::reference_internal);
  msg.def("get_attribute", &Message::GetAttribute,
          "Returns the attribute object by its name", "name"_a,
          return_value_policy::reference_internal);

  msg.def_property_readonly("signals", [] (Message& self) -> dict {
    const auto& signal_list = self.Signals();
    dict temp_list;
    for (const auto& itr : signal_list) {
      const auto& name = itr.first;
      const auto& signal = itr.second;
      temp_list[name.c_str()] = cast(signal, return_value_policy::reference);
    }
    return temp_list;
  }, "Returns a list of signal objects");

  msg.def_property_readonly("senders", [] (Message& self) -> list {
    const auto& sender_list = self.Senders();
    list temp_list = cast(sender_list);
    return temp_list;
  }, "Returns a list of sender nodes for this message");

  msg.def_property_readonly("attributes", [] (Message& self) -> list {
    const auto& attribute_list = self.Attributes();
    list temp_list(attribute_list.size());
    for (size_t index = 0; index < attribute_list.size(); ++index) {
      const auto& attribute = attribute_list[index];
      temp_list[index] = cast(attribute, return_value_policy::reference);
    }
    return temp_list;
  }, "Returns a list of attribute objects");

  msg.def("node_sender",&Message::IsNodeSender,
          "Returns true if the node name is a sender of this message.","node_name"_a);

  msg.def_property_readonly("data", [] (Message& self) -> list {
    const auto& data_list = self.Data();
    list temp_list = cast(data_list);
    return temp_list;
  }, "Returns the last message data bytes");

  constexpr std::string_view update_data_doc = R"(
Update the internal data buffer.

Sets the internal last message data buffer. Note that the input offset
and destination offset is used if the message requires more than one
CAN data message before it is complete.

Args:
  data_bytes: Message data.
  offset: Offset in the message data buffer (input index).
  index: Offset in the last message data buffer (dest index).

Returns:
  True if this was the last bytes (complete message).
)";
  msg.def("update_data", [] (Message& self, const list& data_bytes,
                            size_t offset, size_t index) -> bool {
    const auto temp_list = data_bytes.cast<std::vector<uint8_t>>();
    return self.UpdateData(temp_list, offset, index);
  }, update_data_doc.data(), "data_bytes"_a, "offset"_a = 0, "index"_a = 0);

  msg.def("parse_message", &Message::ParseMessage,"Parses a CAN message",
          "ns1970"_a, "can_id"_a);
  msg.def("reset_sequence_number", &Message::ResetSequenceNumber,
          "Resets the internal sequence number that keep track of CAN messages > 8 bytes");
  msg.def_property_readonly("sequence_number", &Message::NextSequenceNumber,
          "Returns the next sequence number that keep track of CAN messages > 8 bytes");
  msg.def("reset_sample_counter", &Message::ResetSampleCounter,
          "Resets the internal sample counter.");
  msg.def("step_sample_counter", &Message::StepSampleCounter,
          "Increments the internal sample counter.");
  msg.def_property_readonly("sample_counter", &Message::SampleCounter,
          "Returns the internal sample counter.");

  msg.def("create_attribute", &Message::CreateAttribute,
             return_value_policy::reference_internal,
             "Creates a new attribute to the message using the input attribute as template.",
             "attribute"_a);
  msg.def("create_signal", &Message::CreateSignal,
          return_value_policy::reference_internal,
          "Creates a new signal with the supplied name.",
          "name"_a);
}

}  // namespace pydbc