/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/message.h"
#include <algorithm>
#include "dbchelper.h"
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
    const auto value = SignalList::value_type(name, temp);
    itr = signal_list_.insert(value).first;
  }
  return itr->second;
}

void Message::ParseMessage(uint64_t ns1970, uint32_t can_id) {
  // First fix signals without any multiplexed, so we get a channel
  // value for the multiplexor signal first.
  const bool j1939 = IsJ1939(); // Make extra valid check if all bits are set
  bool uses_mux = false;
  for (auto& itr : signal_list_) {
    auto& signal = itr.second;
    if (signal.Mux() == MuxType::Multiplexed ||
        signal.Mux() == MuxType::ExtendedMultiplexor) {
      uses_mux = true;
      continue;
    }
    const auto valid = !j1939 || !DbcHelper::IsAllBitsSet(signal.BitStart(),
                                           signal.BitLength(), data_.data());
    signal.Valid(valid);
    signal.ParseMessage(data_, ns1970, can_id);
    signal.StepSampleCounter();
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
    auto valid = multiplexor->EngValue(mux_value);
    // Check if value is in range
    if (valid && mux.InRange(mux_value)) {
      valid = !j1939 || !DbcHelper::IsAllBitsSet(signal.BitStart(),
                                             signal.BitLength(), data_.data());
      signal.Valid(valid);
      signal.ParseMessage(data_,ns1970, can_id);
      signal.StepSampleCounter();
    }
  }

  // Fix non-MUX signals.
  for (auto& itr : signal_list_) {
    auto& signal = itr.second;
    if (signal.Mux() != MuxType::Multiplexed) {
      continue;
    }
    const auto& extended_mux = signal.GetExtendedMux();
    const auto is_extended_mux = !extended_mux.multiplexor.empty();

    Signal* multiplexor = is_extended_mux ? GetSignal(extended_mux.multiplexor)
                                          : GetMultiplexor();
    if (multiplexor == nullptr) {
      // Might be considered as an error
      continue;
    }
    size_t mux_value = 0;
    auto valid = multiplexor->EngValue(mux_value);
    if (valid && signal.MuxValue() == mux_value) {
      valid = !j1939 || !DbcHelper::IsAllBitsSet(signal.BitStart(),
                                             signal.BitLength(), data_.data());
      signal.Valid(valid);
      signal.ParseMessage(data_,ns1970, can_id);
      signal.StepSampleCounter();
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
  return std::any_of(sender_list_.cbegin(),sender_list_.cend(),
                     [&] (const std::string& sender) {
    return node_name == sender;
  });
}

uint8_t Message::Priority() const {
  auto temp = CanId();
  temp >>= 18 + 8;
  return static_cast<uint8_t>(temp);
}

uint32_t Message::Pgn() const {
  auto temp = CanId();
  temp >>=  8;
  temp &= 0x3FFFF;
  return static_cast<uint32_t>(temp);
}

uint8_t Message::Source() const {
  auto temp = CanId();
  temp &= 0xFF;
  return static_cast<uint8_t>(temp);
}

bool Message::IsJ1939() const {
  if (!IsExtended()) {
    return false;
  }
  const auto* format = GetAttribute("VFrameFormat");
  if (format == nullptr) {
    return false;
  }
  return format->Value<std::string>() == "J1939PG";
}

const Attribute* Message::GetAttribute(const std::string& name) const {
  const auto itr = std::find_if(attribute_list_.cbegin(),
                                attribute_list_.cend(),
                                 [&] (const Attribute& attribute) {
    return name == attribute.Name();
  });
  return itr != attribute_list_.cend() ? &(*itr) : nullptr;
}

bool Message::ExtendedDataPage() const {
  return (CanId() & 0x20000) != 0;
}

bool Message::DataPage() const {
  return (CanId() & 0x10000) != 0;
}

uint8_t Message::PduFormat() const {
  return static_cast<uint8_t >((CanId() & 0xFF00) >> 8);
}

uint8_t Message::PduSpecific() const {
  return static_cast<uint8_t>(CanId() & 0xFF);
}

bool Message::IsPdu1() const {
  return PduFormat() <= 0xEF;
}
bool Message::IsPdu2() const {
  return PduFormat() >= 0xF0;
}

void Message::ResetSampleCounter() const {
  sample_counter_ = 0;
  for (const auto& itr : signal_list_) {
    itr.second.ResetSampleCounter();
  }
}

void Message::NofBytes(size_t bytes) {
  data_.resize(bytes, 0xFF);
}

size_t Message::NofBytes() const {
  return  data_.size();
}

bool Message::UpdateData(const std::vector<uint8_t>& message,
                         size_t offset, size_t data_index) {
  bool last_byte = false; // Set tor true if last byte was received
  for (auto index = offset; index < message.size(); ++index) {
    if (data_index < data_.size()) {
      data_[data_index] = message[index];
      ++data_index;
      if (data_index == data_.size()) {
        last_byte = true;
      }
    }
  }
  ++sequence_number_; // Next expected sequence
  return last_byte;
}

}  // namespace dbc