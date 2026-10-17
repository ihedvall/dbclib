/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */
#pragma once
#include <pybind11/pybind11.h>

namespace pydbc {

extern void InitDbcMessage(pybind11::module& m);
extern void InitAttribute(pybind11::module& m);
extern void InitEnvVar(pybind11::module& m);
extern void InitSignal(const pybind11::module& m);
extern void InitMessage(pybind11::module& m);
extern void InitNode(pybind11::module& m);
extern void InitSignalGroup(pybind11::module& m);
extern void InitNetwork(pybind11::module& m);
extern void InitDbcFile(pybind11::module& m);
extern void InitSignalObserver(pybind11::module& m);
} // pydbc
