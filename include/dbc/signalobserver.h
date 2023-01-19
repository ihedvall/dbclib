/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once
#include "dbc/isampleobserver.h"
#include "dbc/signal.h"
#include <optional>
#include <memory>

namespace dbc {

class SignalObserver : public ISampleObserver {
 public:
  explicit SignalObserver(const Signal& signal);
  SignalObserver() = delete;
  ~SignalObserver() override;

  void MaxSamples(size_t max_nof_samples);
  [[nodiscard]] size_t MaxSamples() const { return value_list_.size();}
  [[nodiscard]] const Signal& GetSignal() const {return signal_;}
  [[nodiscard]] uint64_t Time(size_t index) const;
  [[nodiscard]] uint32_t CanId(size_t index) const;
  template <typename V>
  bool ChannelValue(size_t index, uint64_t& ns1970, V& value) const;

  template <typename V>
  bool EngValue(size_t index, uint64_t& ns1970, V& value) const;

  void ResetSampleIndex();

  [[nodiscard]] size_t FirstIndex() const;
  [[nodiscard]] size_t LastIndex() const;
  [[nodiscard]] size_t NofSamples() const {return nof_samples_;}
  [[nodiscard]] size_t NofValidSamples() const;

  [[nodiscard]] size_t SampleToIndex(size_t sample) const;
  [[nodiscard]] std::optional<size_t> TimeToIndex(uint64_t time) const;
  void DetachObserver() override;
  void OnSample() override;

 protected:
 private:
  struct ChannelSample {
    uint64_t ns1970;
    uint32_t can_id;
    std::any value;

    [[nodiscard]] uint8_t Source() const {
      return static_cast<uint8_t>(can_id & 0xFF);
    }
  };
  const Signal& signal_;
  std::vector<ChannelSample> value_list_; ///< Channel values

  size_t sample_index_ = 0; ///< Points on next index
  size_t nof_samples_ = 0;
  bool attached_ = false;
};

template <typename V>
bool SignalObserver::ChannelValue(size_t index, uint64_t& ns1970,
                                     V& value) const {
  if (index >= value_list_.size()) {
    return false;
  }
  const auto& sample = value_list_[index];
  bool valid = sample.value.has_value();
  ns1970 = sample.ns1970;

  value = {};

  switch (signal_.DataType()) {
    case SignalDataType::SignedData: {
      try {
        const auto temp = std::any_cast<int64_t>(sample.value);
        value = static_cast<V>(temp);
      } catch (const std::exception&) {
        valid = false;
      }
      break;
    }

    case SignalDataType::UnsignedData: {
      size_t bytes = signal_.BitLength() / 8;
      if ((signal_.BitLength() % 8) != 0) {
        ++bytes;
      }
      if (bytes > 8) {
        valid = false;
      } else {
        try {
          const auto temp = std::any_cast<uint64_t>(sample.value);
          value = static_cast<V>(temp);
        } catch (const std::exception&) {
          valid = false;
        }
      }
      break;
    }

    case SignalDataType::FloatData: {
      try {
        const auto temp = std::any_cast<float>(sample.value);
        value = static_cast<V>(temp);
      } catch (const std::exception&) {
        valid = false;
      }
      break;
    }

    case SignalDataType::DoubleData: {
      try {
        const auto temp = std::any_cast<double>(sample.value);
        value = static_cast<V>(temp);
      } catch (const std::exception&) {
        valid = false;
      }
      break;
    }

    default:
      break;
  }
  return valid;
}

template <>
bool SignalObserver::ChannelValue(size_t index, uint64_t& ns1970,
                                  std::string& value) const;

template <typename V>
bool SignalObserver::EngValue(size_t index, uint64_t& ns1970,
                                 V& value) const {
  if (index >= value_list_.size()) {
    return false;
  }
  const auto& sample = value_list_[index];
  bool valid = sample.value.has_value();
  ns1970 = sample.ns1970;

  value = {};

  bool need_to_convert = true;
  // If it is an enumerate. We could convert the enum string but that's weird.
  if (!signal_.EnumList().empty()) {
    need_to_convert = false;
  }
  // Avoid truncation
  if (signal_.Scale() == 1.0 && signal_.Offset() == 0) {
    need_to_convert = false;
  }

  switch (signal_.DataType()) {
    case SignalDataType::SignedData: {
      int64_t channel = 0;
      valid = ChannelValue(index, ns1970, channel);

      if (need_to_convert) {
        auto temp = static_cast<double>(channel);
        temp *= signal_.Scale();
        temp += signal_.Offset();
        value = static_cast<V>(temp);
      } else {
        value = static_cast<V>(channel);
      }
      break;
    }

    case SignalDataType::UnsignedData: {
      uint64_t channel = 0;
      valid = ChannelValue(index, ns1970, channel);
      if (need_to_convert) {
        auto temp = static_cast<double>(channel);
        temp *= signal_.Scale();
        temp += signal_.Offset();
        value = static_cast<V>(temp);
      } else {
        value = static_cast<V>(channel);
      }
      break;
    }

    case SignalDataType::FloatData: {
      float channel = 0;
      valid = ChannelValue(index, ns1970, channel);
      if (need_to_convert) {
        auto temp = static_cast<double>(channel);
        temp *= signal_.Scale();
        temp += signal_.Offset();
        value = static_cast<V>(temp);
      } else {
        value = static_cast<V>(channel);
      }
      break;
    }

    case SignalDataType::DoubleData: {
      double channel = 0;
      valid = ChannelValue(index, ns1970, channel);
      if (need_to_convert) {
        auto temp = channel;
        temp *= signal_.Scale();
        temp += signal_.Offset();
        value = static_cast<V>(temp);
      } else {
        value = static_cast<V>(channel);
      }
      break;
    }

    default:
      break;
  }
  return valid;
}

template <>
bool SignalObserver::EngValue(size_t index, uint64_t& ns1970,
                              std::string& value) const;

using SignalObserverList = std::vector<std::unique_ptr<SignalObserver>>;

}  // namespace dbc
