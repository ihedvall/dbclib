/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/envvar.h"
#include <pybind11/stl.h>

using namespace pybind11;
using namespace dbc;

namespace pydbc {

void InitEnvVar(pybind11::module& m) {

  constexpr std::string_view enum_type_doc =
      R"(Defines the data type of the environment variable.)";
  auto enum_type = enum_<EnvType>(m,"EnvType", enum_type_doc.data());
  enum_type.value("IntegerType", EnvType::IntegerType);
  enum_type.value("FloatType", EnvType::FloatType);
  enum_type.value("StringType", EnvType::StringType);
  enum_type.value("DataType", EnvType::DataType);

  constexpr std::string_view enum_access_doc =
      R"(Defines the access of the environment variable.)";
  auto enum_access = enum_<AccessType>(m,"AccessType", enum_access_doc.data());
  enum_access.value("Unrestricted", AccessType::Unrestricted);
  enum_access.value("ReadOnly", AccessType::ReadOnly);
  enum_access.value("WriteOnly", AccessType::WriteOnly);
  enum_access.value("ReadWrite", AccessType::ReadWrite);

  constexpr std::string_view env_doc = R"(
Wrapper around an DBC environment variable.
)";
  auto env = class_<EnvVar>(m, "EnvVar", env_doc.data());
  env.def(init<>());
  env.def_property("ident",
                    [](EnvVar& self) {return self.Ident();},
                    [](EnvVar& self, uint64_t ident) {self.Ident(ident);});
  env.def_property("name",
                    [](EnvVar& self) {return self.Name();},
                    [](EnvVar& self,const std::string& name) {self.Name(name);});
  env.def_property("comment",
                   [](EnvVar& self) {return self.Comment();},
                   [](EnvVar& self,const std::string& comment) {self.Comment(comment);});
  env.def_property("unit",
                   [](EnvVar& self) {return self.Unit();},
                   [](EnvVar& self,const std::string& unit) {self.Unit(unit);});
  env.def_property("type",
                   [](EnvVar& self) {return self.Type();},
                   [](EnvVar& self, EnvType type) {self.Type(type);});
  env.def_property("access",
                   [](EnvVar& self) {return self.Access();},
                   [](EnvVar& self, AccessType access) {self.Access(access);});
  env.def_property("min",
                   [](EnvVar& self) {return self.Min();},
                   [](EnvVar& self, double min) {self.Min(min);});
  env.def_property("max",
                   [](EnvVar& self) {return self.Max();},
                   [](EnvVar& self, double max) {self.Max(max);});
  env.def_property("initial_value",
                   [](EnvVar& self) {return self.InitValue();},
                   [](EnvVar& self, double value) {self.InitValue(value);});
  env.def_property("enumerate",
                    [](EnvVar& self) {
                      pybind11::dict temp_list = pybind11::cast(self.EnumList());
                      return temp_list;
                    },
                    [](EnvVar& self, const dict& enum_list) {
                      self.EnumList(enum_list.cast<std::map<int64_t, std::string>>());
                    });
  env.def_property("nodes",
                   [](EnvVar& self) {
                     pybind11::list temp_list = pybind11::cast(self.NodeList());
                     return temp_list;
                   },
                   [](EnvVar& self, const list& node_list) {
                     self.NodeList(node_list.cast<std::vector<std::string>>());
                   });
}

}  // namespace pydbc