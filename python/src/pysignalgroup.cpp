/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/signalgroup.h"
#include <pybind11/stl.h>

using namespace pybind11;
using namespace dbc;

namespace pydbc {

void InitSignalGroup(pybind11::module& m) {
  auto group = class_<SignalGroup>(m, "SignalGroup",
                                   "Interface against an DBC signal group");
  group.def_property("message_id",
                   [](SignalGroup& self) {
                     return self.MessageId();
                   },[](SignalGroup& self, uint64_t message_id) {
                     self.MessageId(message_id);
                   });

  group.def_property("name",
                     [](SignalGroup& self) {
                       return self.Name();
                     },[](SignalGroup& self, const std::string& name) {
                       self.Name(name);
                     });

  group.def_property("repetition",
                     [](SignalGroup& self) {
                       return self.Repetition();
                     },[](SignalGroup& self, size_t repetition) {
                       self.Repetition(repetition);
                     });

  group.def_property("signals",
                     [](SignalGroup& self) -> list {
                       return cast(self.Signals());
                     },[](SignalGroup& self, const list& signal_list) -> void {
                       self.Signals(signal_list.cast<std::vector<std::string>>());
                     });

}

} // end namespace pydbc
