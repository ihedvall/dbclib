/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */
/** \file signalobserver.h
 * \brief The sample observer holds sample values for a signal.
 */
#pragma once
#include "dbc/isampleobserver.h"
#include "dbc/signal.h"
#include <utility>
#include <memory>

namespace dbc {
/** \brief The sample observer hold a number of samples.
 *
 * The observer holds signal values in a circular buffer of
 * a maximum number of samples size. The user shall access the samples
 * in normal sample order i.e the first sample is 0 while the internal circular
 * index might be something else.
 *
 */
class SignalObserver : public ISampleObserver {
 public:
  explicit SignalObserver(const Signal& signal); ///< Constructor
  SignalObserver() = delete; ///< Default constructor.
  ~SignalObserver() override; ///< Default destructor.

  /** \brief Sets the maximum number of samples. */
  void MaxSamples(size_t max_nof_samples);
  /** \brief Returns the max number of samples. */
  [[nodiscard]] size_t MaxSamples() const { return value_list_.size();}

  /** \brief Returns the signal object. */
  [[nodiscard]] const Signal& GetSignal() const {return signal_;}

  /** \brief Returns the absolute time for a sample. */
  [[nodiscard]] uint64_t Time(size_t index) const;

  /** \brief Returns the CAN ID for a sample. */
  [[nodiscard]] uint32_t CanId(size_t index) const;

  /** \brief Returns the unscaled signal value.
   *
   * Returns the unscaled signal value for a specific sample.
   * @tparam V Value type.
   * @param index Sample index (0..).
   * @param ns1970 Sample time nano-seconds since 1970.
   * @param value Sample value.
   * @return True if value is valid.
   */
  template <typename V>
  bool ChannelValue(size_t index, uint64_t& ns1970, V& value) const;

  /** \brief Returns the scaled signal value.
   *
   * Returns the scaled signal value for a specific sample.
   * @tparam V Value type.
   * @param index Sample index (0..).
   * @param ns1970 Sample time nano-seconds since 1970.
   * @param value Sample value.
   * @return True if value is valid.
   */
  template <typename V>
  bool EngValue(size_t index, uint64_t& ns1970, V& value) const;

  void ResetSampleIndex(); ///< Reset the sample index

  [[nodiscard]] size_t FirstIndex() const; ///< First sample.
  [[nodiscard]] size_t LastIndex() const; ///< Last sample.
  /** \brief Returns number of samples. */
  [[nodiscard]] size_t NofSamples() const {return nof_samples_;}
  /** \brief Returns number of valid samples. */
  [[nodiscard]] size_t NofValidSamples() const;

  /** \brief Sample number (0..) to internal index. */
  [[nodiscard]] size_t SampleToIndex(size_t sample) const;

  /** \brief Sample time to internal index. */
  [[nodiscard]] std::pair<size_t, bool> TimeToIndex(uint64_t time) const;

  void DetachObserver() override; ///< Detach an observer.
  void OnSample() override; ///< On sample callback handler.

 protected:
 private:
  /** \brief Sample value. */
  struct ChannelSample {
    uint64_t ns1970 = 0; ///< Nano-seconds since 1970.
    uint32_t can_id = 0; ///< CAN ID
    SignalValue value; ///< Unscaled signal value.

    /** \brief Returns the source number from the CAN ID. */
    [[nodiscard]] uint8_t Source() const {
      return static_cast<uint8_t>(can_id & 0xFF);
    }
  };
  const Signal& signal_; ///< Reference to the signal configuration.
  std::vector<ChannelSample> value_list_; ///< Channel values

  size_t sample_index_ = 0; ///< Points on next index
  size_t nof_samples_ = 0; ///< Number of samples.
  bool attached_ = false; ///< True if the observer is attached.
};

template <typename V>
bool SignalObserver::ChannelValue(size_t index, uint64_t& ns1970,
                                     V& value) const {
  if (index >= value_list_.size()) {
    return false;
  }
  const auto& sample = value_list_[index];
  bool valid = sample.value.valid;
  ns1970 = sample.ns1970;

  value = {};

  switch (signal_.DataType()) {
    case SignalDataType::SignedData: {
      try {
        const auto temp = sample.value.signed_value;
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
          const auto temp = sample.value.unsigned_value;
          value = static_cast<V>(temp);
        } catch (const std::exception&) {
          valid = false;
        }
      }
      break;
    }

    case SignalDataType::DoubleData:
    case SignalDataType::FloatData: {
      try {
        const auto temp = sample.value.float_value;
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
/** \brief Returns the unscaled signal value as a string. */
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
  bool valid = sample.value.valid;
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

/** \brief Returns the scaled signal value as a string' */
template <>
bool SignalObserver::EngValue(size_t index, uint64_t& ns1970,
                              std::string& value) const;

/** \brief List of observer. */
using SignalObserverList = std::vector<std::unique_ptr<SignalObserver>>;

}  // namespace dbc
