/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/message.h"
#include <ranges>
#include <algorithm>

namespace {

constexpr uint64_t kMaxId = 0x07EF; ///< Max CAN ID for standard CAN
constexpr uint64_t kMaxExtendedId = 0x1FFFFFFFULL; ///< Max Extended CAN ID
constexpr uint64_t kExtendFlag = 0x80000000ULL; ///< Extended Msg ID

}
namespace dbc {

bool Message::IsExtended() const {
  return (ident_ & kExtendFlag) != 0;
}

uint32_t Message::CanId() const {
  return kMaxExtendedId & ident_;
}

Attribute& Message::CreateAttribute(const Attribute& definition) {
  Attribute temp(definition);
  attribute_list_.emplace_back(temp);
  return attribute_list_.back();
}

Signal* Message::GetSignal(const std::string& name) {
  auto itr = signal_list_.find(name);
  return itr != signal_list_.end() ? &itr->second : nullptr;
}

const Signal* Message::GetSignal(const std::string& name) const {
  const auto itr = signal_list_.find(name);
  return itr != signal_list_.cend() ? &itr->second : nullptr;
}

Signal& Message::CreateSignal(const std::string& name) {
  auto itr = signal_list_.find(name);
  if (itr == signal_list_.end()) {
    Signal temp;
    temp.Name(name);
    itr = signal_list_.insert({name, temp}).first;
  }
  return itr->second;
}

void Message::ParseMessage(const std::vector<uint8_t>& message) {
  // First fix signals without any multiplexed, so we get a channel
  // value for the multiplexor signal first.
  bool uses_mux = false;
  for (auto& itr : signal_list_) {
    auto& signal = itr.second;
    if (signal.Mux() == MuxType::Multiplexed ||
        signal.Mux() == MuxType::ExtendedMultiplexor) {
      uses_mux = true;
      continue;
    }
    signal.ParseMessage(message);
  }

  if (!uses_mux) {
    // No more parsing needed
    return;
  }

  // Fix extended MUX signals. Note only 1 level of extended MUX is implemented
  for (auto& itr : signal_list_) {
    auto& signal = itr.second;
    if (signal.Mux() != MuxType::ExtendedMultiplexor) {
      continue;
    }
    // Get the multiplexor signal
    const auto& mux = signal.GetExtendedMux();
    if (mux.multiplexor.empty()) {
      continue; // Catch this multiplexor in next for loop
    }
    auto* multiplexor = GetSignal(mux.multiplexor);
    if (multiplexor == nullptr) {
      // Might be considered as an error
      continue;
    }
    // Get the mux value
    size_t mux_value = 0;
    const auto valid = multiplexor->EngValue(mux_value);
    // Check if value is in range
    if (valid && mux.InRange(mux_value)) {
      signal.ParseMessage(message);
    }
  }

  // Fix  MUX signals.
  for (auto& itr : signal_list_) {
    auto& signal = itr.second;
    if (signal.Mux() == MuxType::Multiplexed) {
      signal.ParseMessage(message);
    }
    const auto& mux = signal.GetExtendedMux();
    Signal* multiplexor = mux.multiplexor.empty() ?
      GetMultiplexor() : GetSignal(mux.multiplexor);
    if (multiplexor == nullptr) {
      // Might be considered as an error
      continue;
    }
    size_t mux_value = 0;
    const auto valid = multiplexor->EngValue(mux_value);
    if (valid && signal.MuxValue() == mux_value) {
      signal.ParseMessage(message);
    }
  }
}

Signal* Message::GetMultiplexor() {
  for (auto& itr : signal_list_) {
    auto& signal= itr.second;
    if (signal.Mux() == MuxType::Multiplexor) {
      return &signal;
    }
  }
  return nullptr;
}

bool Message::IsNodeSender(const std::string& node_name) const {
  if (node_name == node_) {
    return true;
  }
  return std::ranges::any_of(sender_list_, [&] (const auto& sender) {
    return node_name == sender;
  });
}


}  // namespace dbc