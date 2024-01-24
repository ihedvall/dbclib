/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */
#include "dbc/node.h"
#include <pybind11/stl.h>

using namespace pybind11;
using namespace dbc;

namespace pydbc {

void InitNode(pybind11::module& m) {
  constexpr std::string_view node_doc = R"(
Interface against an DBC node object.
)";
  auto node = class_<Node>(m, "Node", node_doc.data());
  node.def(init<>());

  node.def_property("name",
                   [](Node& self) {
                     return self.Name();
                   },[](Node& self, const std::string& name) {
                     self.Name(name);
                   });
  node.def_property("source",
                    [](Node& self) {
                      return self.Source();
                    },[](Node& self, uint8_t source) {
                      self.Source(source);
                    });
  node.def_property("comment",
                   [](Node& self) {
                     return self.Comment();
                   },[](Node& self, const std::string& comment) {
                     self.Comment(comment);
                   });

  node.def_property_readonly("attributes", [] (Node& self) -> list {
    const auto& attribute_list = self.Attributes();
    list temp_list(attribute_list.size());
    for (size_t index = 0; index < attribute_list.size(); ++index) {
      const auto& attribute = attribute_list[index];
      temp_list[index] = cast(attribute, return_value_policy::reference);
    }
    return temp_list;
  }, "Returns a list of attribute objects");

  node.def("create_attribute", &Node::CreateAttribute,
          return_value_policy::reference_internal,
          "Creates a new attribute to the message using the input attribute as template.",
          "attribute"_a);

  node.def("get_attribute", &Node::GetAttribute,
          "Returns the attribute object by its name", "name"_a,
          return_value_policy::reference_internal);

}

} // end namespace pydbc