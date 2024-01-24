/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/attribute.h"
#include <vector>
#include <pybind11/stl.h>

using namespace pybind11;
using namespace dbc;

namespace pydbc {

void InitAttribute(pybind11::module& m) {
  constexpr std::string_view enum_type_doc =
      R"(Defines what type of network object the attribute is valid for.)";
  auto enum_type = enum_<AttributeType>(m,"AttributeType",
                                        enum_type_doc.data());
  enum_type.value("DbcNetwork", AttributeType::DbcNetwork);
  enum_type.value("DbcNode", AttributeType::DbcNode);
  enum_type.value("DbcMessage", AttributeType::DbcMessage);
  enum_type.value("DbcSignal", AttributeType::DbcSignal);
  enum_type.value("EnvironmentVariable", AttributeType::EnvironmentVariable);
  enum_type.value("NodeSignalRelation", AttributeType::NodeSignalRelation);
  enum_type.value("NodeMessageRelation", AttributeType::NodeMessageRelation);

  constexpr std::string_view enum_value_type_doc =
      R"(Data type of the attribute.)";
  auto enum_value_type = enum_<AttributeValueType>(m,"AttributeValueType",
                                                   enum_value_type_doc.data());
  enum_value_type.value("IntegerValue", AttributeValueType::IntegerValue);
  enum_value_type.value("FloatValue", AttributeValueType::FloatValue);
  enum_value_type.value("StringValue", AttributeValueType::StringValue);
  enum_value_type.value("EnumValue", AttributeValueType::EnumValue);
  enum_value_type.value("HexValue", AttributeValueType::HexValue);

  constexpr std::string_view attribute_doc = R"(
Support class for handling attributes of network objects.

The Attribute class is a support class for handling attributes attached
to DBC objects.

The DBC file first specify a definition of an attribute.
This definition defines range and data type i.e. a sort of template.
Then the DBC file define the attribute that references a definition and
has a value (constant).
)";
  auto attr = class_<Attribute>(m, "Attribute", attribute_doc.data());

  constexpr std::string_view attribute_init_doc = R"(
Constructor for an attribute or definition.

Attributes:
      type: Type of attribute
      name: Name of the attribute
)";
  attr.def(init<>());
  attr.def(init<dbc::AttributeType, const std::string&>(),
      attribute_init_doc.data(), "type"_a, "name"_a);
  attr.def_property("name",
                    [](Attribute& self) {return self.Name();},
                    [](Attribute& self,const std::string& name) {
                      self.Name(name);
                    });
  attr.def_property("type",
                    [](Attribute& self) {return self.Type();},
                    [](Attribute& self, AttributeType type) {self.Type(type);});
  attr.def_property("value_type",
                    [](Attribute& self) {return self.ValueType();},
                    [](Attribute& self, AttributeValueType type) {self.ValueType(type);});
  attr.def_property("min",
                    [](Attribute& self) {return self.Min();},
                    [](Attribute& self, double min) {self.Min(min);});
  attr.def_property("max",
                    [](Attribute& self) {return self.Max();},
                    [](Attribute& self, double max) {self.Max(max);});
  attr.def_property("enumerate",
                    [](Attribute& self) {
                      pybind11::list temp_list = pybind11::cast(self.EnumList());
                      return temp_list;
                    },
                    [](Attribute& self, const list& enum_list) {
                      self.EnumList(enum_list.cast<std::vector<std::string>>());
                    });
  attr.def_property("value",
                    [](Attribute& self) {return self.Value<std::string>();},
                    [](Attribute& self, const std::string& value) {self.Value(value);});
  attr.def_property("value",
                    [](Attribute& self) {return self.Value<int>();},
                    [](Attribute& self, int value) {self.Value(value);});
  attr.def_property("value",
                    [](Attribute& self) {return self.Value<double>();},
                    [](Attribute& self, double value) {self.Value(value);});
}


}  // namespace pydbc