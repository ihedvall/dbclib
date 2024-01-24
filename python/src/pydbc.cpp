/*
* Copyright 2024 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "pydbc.h"

#include <pybind11/pybind11.h>

using namespace pydbc;
using namespace pybind11;

PYBIND11_MODULE(pydbc, m) {
  InitDbcMessage(m);
  InitAttribute(m);
  InitEnvVar(m);
  InitSignal(m);
  InitMessage(m);
  InitNode(m);
  InitSignalGroup(m);
  InitNetwork(m);
  InitDbcFile(m);
  InitSignalObserver(m);
}