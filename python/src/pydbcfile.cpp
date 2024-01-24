/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once

#include <dbc/dbcfile.h>
#include <pybind11/stl.h>

using namespace pybind11;
using namespace dbc;

namespace pydbc {

void InitDbcFile(pybind11::module& m) {
  auto file = class_<DbcFile>(m, "DbcFile");
  file.def(init<>());

  file.def_property("filename",
                    [](DbcFile& self) {return self.Filename();},
                    [](DbcFile& self, const std::string& filename) {
                      self.Filename(filename);
                    });

  file.def_property_readonly("name", &DbcFile::Name,
                             "Returns the filename without any path and extension");

  file.def_property_readonly("last_error", &DbcFile::LastError,
                             "Returns the last parser error.");

  file.def("get_network",[](DbcFile& self) {
    return cast(self.GetNetwork(), return_value_policy::reference);
  });

  file.def("parse_file", &DbcFile::ParseFile,
           "Parses the DBC file and returns true if the parsing was successful.");

  constexpr std::string_view base_time_doc = R"(
Start (absolute) time of messages.

The base time is the time of the first message. If not set, the
add_message() function will set it to the first message. The time
should be nano-seconds since 1970.
)";
  file.def_property("base_time",
                    [](DbcFile& self) {return self.BaseTime();},
                    [](DbcFile& self, uint64_t ns1970) {
                      self.BaseTime(ns1970);
                    }, base_time_doc.data());

  file.def_property("message_size",
                    [](DbcFile& self) {return self.MessageSize();},
                    [](DbcFile& self, size_t nof_messages) {
                      self.MessageSize(nof_messages);
                    }, "Sets the maximum number of messages in the internal message queue.");

  file.def("add_message", &DbcFile::AddMessage,
           "Adds a message to the internal message queue.",
           "index"_a, "message"_a);

  file.def("parse_message", &DbcFile::ParseMessage,
           "Parses a message i.e. converting tne message into signal values.",
           "message"_a);

  file.def("reset_sample_counter", &DbcFile::ResetSampleCounter,
           "Resets the sample counter for all signals.");

  file.def("reparse_messages", &DbcFile::ReparseMessageList,
           "Reparse all messages in the internal message queue.");

}

} // End namespace pydbc