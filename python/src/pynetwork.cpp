/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */
#include "dbc/network.h"
#include <pybind11/stl.h>

using namespace pybind11;
using namespace dbc;

namespace pydbc {
void InitNetwork(pybind11::module& m) {

  auto protocol_type = enum_<ProtocolType>(m,"ProtocolType",
                                        "Type of protocol on the bus.");
  protocol_type.value("StandardCAN", ProtocolType::StandardCAN);
  protocol_type.value("J1939", ProtocolType::J1939);
  protocol_type.value("NMEA2000", ProtocolType::NMEA2000);
  protocol_type.value("OBD2", ProtocolType::OBD2);

  auto bus_type = enum_<BusType>(m,"BusType",
                                           "Type of bus.");
  bus_type.value("CAN", BusType::CAN);

  auto network = class_<Network>(m, "Network", "Interface against DBC network.");
  network.def_property("filename",
                    [](Network& self) {return self.Filename();},
                    [](Network& self,const std::string& filename) {
                      self.Filename(filename);
                    });
  network.def_property("protocol",
                       [](Network& self) {return self.Protocol();},
                       [](Network& self,ProtocolType type) {
                         self.Protocol(type);
                       });
  network.def_property("bus",
                       [](Network& self) {return self.Bus();},
                       [](Network& self, BusType type) {
                         self.Bus(type);
                       });
  network.def_property("version",
                       [](Network& self) {return self.Version();},
                       [](Network& self,const std::string& version) {
                         self.Version(version);
                       });
  network.def_property("comment",
                       [](Network& self) {return self.Comment();},
                       [](Network& self,const std::string& comment) {
                         self.Comment(comment);
                       });

  network.def("get_node", [] (Network& self, const std::string& name)  {
    const auto* node = self.GetNode(name);
    return cast(node, return_value_policy::reference_internal);
  }, "Returns the DBC node by name.", "name"_a);
  network.def("get_node", [] (Network& self, uint8_t source)  {
    const auto* node = self.GetNodeBySource(source);
    return cast(node, return_value_policy::reference_internal);
  }, "Returns the DBC node by source number.", "source"_a);

  network.def_property("j1939",
                       [](Network& self) {return self.J1939();},
                       [](Network& self, bool j1939) {
                         self.J1939(j1939);
                       });

  network.def("get_message_by_message_id", [] (Network& self, uint64_t message_id)  {
    const auto* message = self.GetMessage(message_id);
    return cast(message, return_value_policy::reference_internal);
  }, "Returns a DBC message by its message ID.", "message_id"_a);

  network.def("get_message_by_can_id", [] (Network& self, uint32_t can_id)  {
    const auto* message = self.GetMessageByCanId(can_id);
    return cast(message, return_value_policy::reference_internal);
  }, "Returns a DBC message by its CAN ID (29-bit).", "can_id"_a);

  network.def("get_message_by_pgn", [] (Network& self, uint32_t pgn)  {
    const auto* message = self.GetMessageByPgn(pgn);
    return cast(message, return_value_policy::reference_internal);
  }, "Returns a DBC message by its PGN.", "pgn"_a);

  network.def("get_message_by_pgn_and_source", [] (Network& self, uint32_t pgn, uint8_t source)  {
    const auto* message = self.GetMessageByPgnAndSource(pgn, source);
    return cast(message, return_value_policy::reference_internal);
  }, "Returns a DBC message by its PGN and source number.", "pgn"_a, "source"_a);

  network.def("get_signal_by_message_id_and_name", [] (Network& self, uint64_t message_id,
                                                      const std::string& name)  {
    const auto* signal = self.GetSignal(message_id, name);
    return cast(signal, return_value_policy::reference_internal);
  }, "Returns a DBC message by its message ID and name.", "message_id"_a, "name"_a);

  network.def("get_signal_by_can_id_and_name", [] (Network& self, uint32_t can_id,
                                                      const std::string& name)  {
    const auto* signal = self.GetSignalByCanId(can_id, name);
    return cast(signal, return_value_policy::reference_internal);
  }, "Returns a DBC signal by its message ID and name.", "can_id"_a, "name"_a);

  network.def("get_signal_by_name", [] (Network& self, const std::string& name)  {
    const auto* signal = self.GetSignalByName(name);
    return cast(signal, return_value_policy::reference_internal);
  }, "Returns a DBC signal by its name.", "name"_a);

  network.def("get_signal_group", [] (Network& self, uint64_t message_id,
                                                  const std::string& name)  {
    const auto* group = self.GetSignalGroup(message_id, name);
    return cast(group, return_value_policy::reference_internal);
  }, "Returns a DBC signal group by its message ID and name.", "message_id"_a, "name"_a);

  network.def("get_signal_group_by_name", [] (Network& self, const std::string& name)  {
    const auto* group = self.GetSignalGroupByName(name);
    return cast(group, return_value_policy::reference_internal);
  }, "Returns a DBC signal group by its name.", "name"_a);

  network.def_property_readonly("envvars",
                      [](Network& self) {
                        const auto& var_list = self.EnvVars();
                        dict temp_list;
                        for ( const auto& itr : var_list) {
                          const std::string& name = itr.first;
                          const auto& obj = itr.second;
                          temp_list[name.c_str()] = cast(obj, return_value_policy::reference );
                        }
                        return temp_list;
                      });

  network.def_property_readonly("messages",
                                [](Network& self) {
                                  const auto& msg_list = self.Messages();
                                  dict temp_list;
                                  for ( const auto& itr : msg_list) {
                                    uint64_t msg_id = itr.first;
                                    const auto& data = itr.second;

                                    temp_list[std::to_string(msg_id).c_str()] = cast(data);
                                  }
                                  return temp_list;
                                });

  network.def_property_readonly("nodes",
                                [](Network& self) {
                                  const auto& node_list = self.Nodes();
                                  dict temp_list;
                                  for ( const auto& itr : node_list) {
                                    const std::string& name = itr.first;
                                    const auto& obj = itr.second;
                                    temp_list[name.c_str()] = cast(obj, return_value_policy::reference );
                                  }
                                  return temp_list;
                                });

  network.def_property_readonly("signal_groups",
                                [](Network& self) {
                                  const auto& group_list = self.SignalGroups();
                                  list temp_list(group_list.size());
                                  for (size_t index = 0; index < group_list.size(); ++index) {
                                    const auto& group = group_list[index];
                                    temp_list[index] = cast(group, return_value_policy::reference );
                                  }
                                  return temp_list;
                                });
  network.def_property_readonly("enumerates",
                                [](Network& self) -> dict {
                                  const auto& enum_list = self.Enums();
                                  dict temp_list;
                                  for ( const auto& itr : enum_list) {
                                    const auto& enum_name = itr.first;
                                    const auto& enum_map = itr.second;
                                    const dict temp = cast(enum_map );
                                    temp_list[enum_name.c_str()] = temp;
                                  }
                                  return temp_list;
                                });
  network.def_property_readonly("attributes",
                                [](Network& self) {
                                  const auto& attr_list = self.Attributes();
                                  list temp_list(attr_list.size());
                                  for (size_t index = 0; index < attr_list.size(); ++index) {
                                    const auto& attr = attr_list[index];
                                    temp_list[index] = cast(attr, return_value_policy::reference );
                                  }
                                  return temp_list;
                                });

  network.def("get_attribute_by_name", [] (Network& self, const std::string& name)  {
    const auto* attr = self.GetAttribute(name);
    return cast(attr, return_value_policy::reference_internal);
  }, "Returns a DBC attribute by its name.", "name"_a);

  network.def("add_enumerate", [] (Network& self, const std::string& name, const dict& enumerate)-> void  {
    const auto temp_list = enumerate.cast<std::map<int64_t, std::string>>();
    self.AddValueTable(name, temp_list);
  }, "Adds an enumerate to the enumerate list", "name"_a, "enumerate"_a);

  network.def("add_signal_group", &Network::AddSignalGroup,
              "Adds a signal group to the network object", "group"_a);

}

} // end namespace pydbc