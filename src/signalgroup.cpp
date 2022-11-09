/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */

#include "dbc/signalgroup.h"

namespace dbc {

void SignalGroup::Signals(const std::vector<std::string>& signals) {
  signal_list_ = signals;
}

const std::vector<std::string>& SignalGroup::Signals() const {
  return signal_list_;
}

}  // namespace dbc