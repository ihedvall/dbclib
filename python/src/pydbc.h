/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */
#pragma once
#include <pybind11/pybind11.h>

namespace pydbc {

void InitDbcMessage(pybind11::module& m);
void InitAttribute(pybind11::module& m);
void InitEnvVar(pybind11::module& m);
void InitSignal(pybind11::module& m);
void InitMessage(pybind11::module& m);
void InitNode(pybind11::module& m);
void InitSignalGroup(pybind11::module& m);
void InitNetwork(pybind11::module& m);
void InitDbcFile(pybind11::module& m);
void InitSignalObserver(pybind11::module& m);
} // pydbc
