/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/signalobserver.h"
#include <vector>
#include <pybind11/stl.h>

using namespace pybind11;
using namespace dbc;

namespace pydbc {

void InitSignalObserver(pybind11::module& m) {
  constexpr std::string_view observer_class_doc = R"(
The sample observer hold a number of samples.

The observer holds signal values in a circular buffer of
a maximum number of samples size. The user shall access the samples
in normal sample order i.e the first sample is 0 while the internal circular
index might be something else.
)";

  auto observer = class_<SignalObserver, std::shared_ptr<SignalObserver>>(m,
                                                                          "SignalObserver",
                                                                          observer_class_doc.data());

  observer.def_static("create_observer", &SignalObserver::CreateSignalObserver,
                      "Creates a signal observer object", "signal"_a);

  observer.def_property("max_samples",
                    [](const SignalObserver& self) { return self.MaxSamples();},
                    [](SignalObserver& self, size_t max_samples) {
                      self.MaxSamples(max_samples);
                    });

  observer.def_property_readonly("signal", &SignalObserver::GetSignal,
                                 "Returns a reference to the observers signal object.",
                                 return_value_policy::reference_internal);

  observer.def("time", &SignalObserver::Time,
                                 "Returns the absolute time in nano-seconds since 1970 for a message.",
                                 "index"_a);

  observer.def("can_id", &SignalObserver::Time,
               "Returns the CAN ID for a message.",
               "index"_a);

  observer.def("channel_value_as_int", [](const SignalObserver& self, size_t index) -> tuple {
    uint64_t time = 0;
    int64_t value = 0;
    const auto valid = self.ChannelValue(index, time, value);
    return make_tuple(valid, value, time);
  },"Returns a tuple(valid,value,time) for a sample.", "index"_a);

  observer.def("channel_value_as_uint", [](const SignalObserver& self, size_t index) -> tuple {
    uint64_t time = 0;
    uint64_t value = 0;
    const auto valid = self.ChannelValue(index, time, value);
    return make_tuple(valid, value, time);
  },"Returns a tuple(valid,value,time) for a sample.", "index"_a);

  observer.def("channel_value_as_double", [](const SignalObserver& self, size_t index) -> tuple {
    uint64_t time = 0;
    double value = 0;
    const auto valid = self.ChannelValue(index, time, value);
    return make_tuple(valid, value, time);
  },"Returns a tuple(valid,value,time) for a sample.", "index"_a);

  observer.def("channel_value_as_string", [](const SignalObserver& self, size_t index) -> tuple {
    uint64_t time = 0;
    std::string value;
    const auto valid = self.ChannelValue(index, time, value);
    return make_tuple(valid, cast(value), time);
  },"Returns a tuple(valid,value,time) for a sample.", "index"_a);

  observer.def("eng_value_as_int", [](const SignalObserver& self, size_t index) -> tuple {
    uint64_t time = 0;
    int64_t value = 0;
    const auto valid = self.EngValue(index, time, value);
    return make_tuple(valid, value, time);
  },"Returns a tuple(valid,value,time) for a sample.", "index"_a);

  observer.def("eng_value_as_uint", [](const SignalObserver& self, size_t index) -> tuple {
    uint64_t time = 0;
    uint64_t value = 0;
    const auto valid = self.EngValue(index, time, value);
    return make_tuple(valid, value, time);
  },"Returns a tuple(valid,value,time) for a sample.", "index"_a);

  observer.def("eng_value_as_double", [](const SignalObserver& self, size_t index) -> tuple {
    uint64_t time = 0;
    double value = 0;
    const auto valid = self.EngValue(index, time, value);
    return make_tuple(valid, value, time);
  },"Returns a tuple(valid,value,time) for a sample.", "index"_a);

  observer.def("eng_value_as_string", [](const SignalObserver& self, size_t index) -> tuple {
    uint64_t time = 0;
    std::string value;
    const auto valid = self.ChannelValue(index, time, value);
    return make_tuple(valid, cast(value), time);
  },"Returns a tuple(valid,value,time) for a sample.", "index"_a);

  observer.def("reset_sample_index", &SignalObserver::ResetSampleIndex);

  observer.def_property_readonly("first_index", &SignalObserver::FirstIndex);
  observer.def_property_readonly("last_index", &SignalObserver::FirstIndex);
  observer.def_property_readonly("nof_samples", &SignalObserver::NofSamples);
  observer.def_property_readonly("nof_valid_samples", &SignalObserver::NofValidSamples);
  observer.def("sample_to_index", &SignalObserver::SampleToIndex,
                "sample"_a);
  observer.def("time_to_index", &SignalObserver::TimeToIndex,
               "time"_a);
}

} // end namespace pydbc