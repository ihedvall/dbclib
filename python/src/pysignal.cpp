/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/signal.h"
#include <pybind11/stl.h>

#include "dbc/attribute.h"

using namespace pybind11;
using namespace dbc;

namespace pydbc {

void InitSignal(pybind11::module& m) {

  constexpr std::string_view signal_value_doc = R"(
Support object that purpose is to hold one signal value.

support object that is used when parsing CAN messages. The
object hold the last parsed messages signal value.
)";
  auto value = class_<SignalValue>(m,"SignalValue",
                signal_value_doc.data());
  value.def(init<>());
  value.def_readwrite("valid", &SignalValue::valid);
  value.def_readwrite("signed_value", &SignalValue::signed_value);
  value.def_readwrite("unsigned_value", &SignalValue::unsigned_value);
  value.def_readwrite("float_value", &SignalValue::float_value);
  value.def_readwrite("array_value", &SignalValue::array_value,
      "The array value is used for signal that have more than 8 bytes.");
  value.def("clear", &SignalValue::Clear,
            "Reset all buffered values");

  auto type = enum_<SignalDataType>(m, "SignalDataType",
                                    "Data type for signal values");
  type.value("SignedData", SignalDataType::SignedData, "Signed integer.");
  type.value("UnsignedData", SignalDataType::UnsignedData, "Unsigned integer.");
  type.value("FloatData", SignalDataType::FloatData, "32-bit floating point value.");
  type.value("DoubleData", SignalDataType::DoubleData, "64-bit floating point value.");

  constexpr std::string_view enum_mux_doc =
      R"(
Multiplexer type.

A signal may be multiplexed i.e. have different value depending on
another multiplexor signal.Then someone invented the extended multiplexed
value which makes every thing confusing.
)";
  auto enum_type = enum_<MuxType>(m,"MuxType", enum_mux_doc.data());
  enum_type.value("NotMultiplexed", MuxType::NotMultiplexed,
                  "Standard non-multiplexed signal.");
  enum_type.value("Multiplexor", MuxType::Multiplexor,
                  "The signal is the multiplexor value.");
  enum_type.value("Multiplexed", MuxType::Multiplexed,
                  "The signal is the multiplexed value.");
  enum_type.value("ExtendedMultiplexor", MuxType::ExtendedMultiplexor,
                  "The signal is the extended multiplexor value.");


  auto extended_mux = class_<ExtendedMux>(m,"ExtendedMux",
                                          "Wrapper for extended multiplexer support.");
  extended_mux.def(init<>());
  extended_mux.def_readwrite("multiplexor",
                             &ExtendedMux::multiplexor,
                             "Signal name of the multiplexer.");
  extended_mux.def_readwrite("range_list", &ExtendedMux::range_list,
                             "List of min/max tuples");
  extended_mux.def("in_range", &ExtendedMux::InRange,
                   "Test if a specific value is in range for this multiplexor",
                   "value"_a);

  auto signal = class_<Signal>(m, "Signal",
                                 "Interface against a DBC signal object." );
  signal.def(init<>());
  signal.def_property("name",
                    [](Signal& self) {return self.Name();},
                    [](Signal& self,const std::string& name) {self.Name(name);});
  signal.def_property("unit",
                      [](Signal& self) {return self.Unit();},
                      [](Signal& self,const std::string& unit) {self.Unit(unit);});
  signal.def_property("comment",
                      [](Signal& self) {return self.Comment();},
                      [](Signal& self,const std::string& comment) {self.Comment(comment);});
  signal.def_property("data_type",
                      [](Signal& self) {return self.DataType();},
                      [](Signal& self, SignalDataType type) {self.DataType(type);});
  signal.def_property("mux",
                      [](Signal& self) {return self.Mux();},
                      [](Signal& self, MuxType type) {self.Mux(type);},
                      "Specifies if and what type of multiplexer. Default is not multiplexed");
  signal.def_property("mux_value",
                      [](Signal& self) {return self.MuxValue();},
                      [](Signal& self, int value) {self.MuxValue(value);});
  signal.def_property("bit_start",
                      [](Signal& self) {return self.BitStart();},
                      [](Signal& self, size_t start) {self.BitStart(start);});
  signal.def_property("bit_length",
                      [](Signal& self) {return self.BitLength();},
                      [](Signal& self, size_t length) {self.BitLength(length);});
  signal.def_property("little_endian",
                      [](Signal& self) {return self.LittleEndian();},
                      [](Signal& self, bool endian) {self.LittleEndian(endian);},
                      "Defines the byte order.");
  signal.def_property("scale",
                      [](Signal& self) {return self.Scale();},
                      [](Signal& self, double scale) {self.Scale(scale);});
  signal.def_property("offset",
                      [](Signal& self) {return self.Offset();},
                      [](Signal& self, double offset) {self.Offset(offset);});
  signal.def_property("min",
                      [](Signal& self) {return self.Min();},
                      [](Signal& self, double min) {self.Min(min);});
  signal.def_property("max",
                      [](Signal& self) {return self.Max();},
                      [](Signal& self, double max) {self.Max(max);});
  signal.def_property("enumerate",
                      [](Signal& self) {
                        dict temp_list = cast(self.EnumList());
                        return temp_list;
                      },
                      [](Signal& self, const dict& enum_list) {
                        self.EnumList(enum_list.cast<std::map<int64_t, std::string>>());
                      });
  signal.def_property("receivers",
                      [](Signal& self) {
                        list temp_list = cast(self.Receivers());
                        return temp_list;
                      },
                      [](Signal& self, const list& receivers) {
                        self.Receivers(receivers.cast<std::vector<std::string>>());
                      });
  signal.def_property("attributes",
                      [](Signal& self) {
                        const auto& attr_list = self.Attributes();
                        list temp_list(attr_list.size());
                        for (size_t index = 0; index < temp_list.size(); ++index) {
                          const auto& attribute = attr_list[index];
                          temp_list[index] = cast(attribute, return_value_policy::reference );
                        }
                        return temp_list;
                      },
                      [](Signal& self, const list& attributes) {
                        std::vector<Attribute> temp_list(attributes.size());
                        for (size_t index = 0; index < temp_list.size(); ++ index) {
                          const auto obj = attributes[index];
                          const auto temp = obj.cast<Attribute>();
                          temp_list[index] = temp;
                        }
                       self.Attributes(temp_list);
                      });
  signal.def_property("message_id",
                      [](Signal& self) {return self.MessageId();},
                      [](Signal& self, uint64_t message_id ) {self.MessageId(message_id);},
                      "Specifies which CAN message the signal belongs to.");

  signal.def_property_readonly("multiplexed", &Signal::IsMultiplexed,
                               "Returns true if this signal is multiplexed.");
  signal.def_property_readonly("array_value", &Signal::IsArrayValue,
     "Returns true if number of bytes > 8 i.e. cannot be handled as its specified data type");
  signal.def("create_attribute", &Signal::CreateAttribute,
             return_value_policy::reference_internal,
             "Creates a new attribute to the signal using the input attribute as template.",
             "attribute"_a);
  signal.def_property_readonly("extended_mux", &Signal::GetExtendedMux,
                               return_value_policy::reference_internal,
                    "Returns a reference to the internal extended multiplex object");
  signal.def("get_enum_string", &Signal::GetEnumString,
             "Returns the enumerate text for a specific value.",
             "index"_a);
  signal.def("parse_message", [](Signal& self, const list& message,
                                         uint64_t ns1970, uint32_t can_id) {
             const auto temp_list = message.cast<std::vector<uint8_t>>();
             self.ParseMessage(temp_list, ns1970, can_id); },
             "Parses out the signal value, in a CAN message.",
             "message"_a, "ns1970"_a, "can_id"_a);

  signal.def("reset_sample_counter", &Signal::ResetSampleCounter );
  signal.def("step_sample_counter", &Signal::StepSampleCounter );


  signal.def_property_readonly("sample_counter", &Signal::SampleCounter);
  signal.def_property("sample_time",
                      [](Signal& self) {return self.SampleTime();},
                      [](Signal& self, uint64_t ns1970) {self.SampleTime(ns1970);},
                      "The sample time. Note absolute time, nano-seconds since 1970");
  signal.def_property("valid",
                      [](Signal& self) {return self.Valid();},
                      [](Signal& self, bool valid) {self.Valid(valid);});

  signal.def_property_readonly("signal_value", &Signal::GetSignalValue,
                               return_value_policy::reference_internal,
                               "Returns a reference to the internal signal value object");

  signal.def_property_readonly("channel_value", [] (Signal& self) -> tuple  {

    switch (self.DataType()) {
      case SignalDataType::SignedData: {
        std::pair<bool, int64_t> value(false, 0);
        value.first = self.ChannelValue(value.second);
        return cast(value);
      }

      case SignalDataType::UnsignedData: {
        if (self.IsArrayValue()) {
          // This is a most likely a string value
          std::pair<bool, std::string> value(false, "");
          try {
            value.first = self.ChannelValue(value.second);
          } catch (const std::exception&) {
             value.first = false;
          }
          return cast(value);
        } else {
          std::pair<bool, uint64_t> value(false, 0);
          value.first = self.ChannelValue(value.second);
          return cast(value);
        }
      }

      case SignalDataType::FloatData: {
        std::pair<bool, float> value(false, 0.0F);
        value.first = self.ChannelValue(value.second);
        return cast(value);
      }

      case SignalDataType::DoubleData: {
        std::pair<bool, double> value(false, 0.0);
        value.first = self.ChannelValue(value.second);
        return cast(value);
      }

      default:
        break;
    }

    const std::pair<bool, int64_t> invalid = {false, 0};
    return cast(invalid);

  }, "Returns a tuple (valid,value) of the latest signal value.");

  signal.def_property_readonly("channel_array_value", [](Signal& self) -> tuple {
    std::vector<uint8_t> temp_list;
    const bool valid = self.ChannelValue(temp_list);
    const list byte_array = cast(temp_list);
    const std::pair<bool,list> value(valid,byte_array);
    return cast(value);
    }, "Returns a tuple (valid,list) of the latest array value.");

  signal.def_property_readonly("channel_text_value", [](Signal& self) -> tuple {
    std::string text;
    const bool valid = self.ChannelValue(text);
    const std::pair<bool,std::string> value(valid,text);
    return cast(value);
  }, "Returns a tuple (valid,str) of the latest value.");

  signal.def_property_readonly("eng_value", [](Signal& self) -> tuple {
    double temp = 0.0;
    const bool valid = self.EngValue(temp);
    const std::pair<bool,double> value(valid,temp);
    return cast(value);
  }, "Returns a tuple (valid,double) of the latest scaled value.");

  signal.def_property_readonly("eng_text", [](Signal& self) -> tuple {
    std::string text;
    const bool valid = self.EngValue(text);
    const std::pair<bool,std::string> value(valid,text);
    return cast(value);
  }, "Returns a tuple (valid,str) of the latest scaled value.");
};

}  // namespace pydbc