/*
* Copyright 2023 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "pydbcmessage.h"
#include "pydbcfile.h"
#include <pybind11/pybind11.h>

using namespace pydbc;
using namespace pybind11;

PYBIND11_MODULE(pydbc, m) {
  auto msg = class_<PyDbcMessage>(m, "DbcMessage");
  msg.def(init<>());
  msg.def_property("time", &PyDbcMessage::GetTime, &PyDbcMessage::SetTime);

  auto file = class_<PyDbcFile>(m, "DbcFile");
  file.def(init<>());
  file.def_property("filename", &PyDbcFile::GetFilename, &PyDbcFile::SetFilename);
  file.def_property_readonly("name", &PyDbcFile::Name);
  file.def_property_readonly("last_error", &PyDbcFile::LastError);
  file.def_property("base_time", &PyDbcFile::GetBaseTime, &PyDbcFile::SetBaseTime);
  file.def_property("message_size", &PyDbcFile::GetMessageSize, &PyDbcFile::SetMessageSize);

  file.def("parse_file", &PyDbcFile::ParseFile);

}