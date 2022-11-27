/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/signalobserver.h"
#include <ranges>
#include <algorithm>

namespace dbc {

SignalObserver::SignalObserver(const Signal& signal)
: signal_(signal) {
  signal_.AttachObserver(this);
  attached_ = true;
  MaxSamples(signal.SampleCounter());
}

SignalObserver::~SignalObserver() {
  SignalObserver::DetachObserver();
}

void SignalObserver::DetachObserver() {
  if (attached_) {
    signal_.DetachObserver(this);
    attached_ = false;
  }
}

void SignalObserver::MaxSamples(size_t max_nof_samples) {
  if (max_nof_samples == 0) {
    value_list_.clear();
  } else {
    value_list_.resize(max_nof_samples);
  }
  ResetSampleIndex();
}

void SignalObserver::ResetSampleIndex() {
  sample_index_ = 0;
  nof_samples_ = 0;
}

size_t SignalObserver::FirstIndex() const {
  if (nof_samples_ < value_list_.size()) {
    return 0;
  }
  return sample_index_; // Next index == first index
}

size_t SignalObserver::LastIndex() const {
  if (nof_samples_ < value_list_.size()) {
    return sample_index_ > 0 ? sample_index_ - 1 : 0;
  }
  return sample_index_ > 0 ? sample_index_ - 1 : value_list_.size() - 1;
}

void SignalObserver::OnSample() {
  if (sample_index_ >= value_list_.size()) {
    return;
  }

  ChannelSample sample;
  sample.ns1970 = signal_.SampleTime();
  sample.can_id = signal_.SampleCanId();
  signal_.ChannelValue(sample.value);

  value_list_[sample_index_] = sample;
  ++sample_index_;
  if (sample_index_ >= value_list_.size()) {
    sample_index_ = 0;
  }
  if (nof_samples_ < value_list_.size()) {
    ++nof_samples_;
  } else {
    nof_samples_ = value_list_.size();
  }
}

size_t SignalObserver::SampleToIndex(size_t sample) const {
  size_t index = FirstIndex() + sample;
  if (index >= value_list_.size()) {
    index -= value_list_.size();
  }
  return index;
}

uint64_t SignalObserver::Time(size_t index) const {
    return index < value_list_.size() ? value_list_[index].ns1970 : 0;
}

uint32_t SignalObserver::CanId(size_t index) const {
  return index < value_list_.size() ? value_list_[index].can_id : 0;
}

std::optional<size_t> SignalObserver::TimeToIndex(uint64_t time) const {
  size_t index;
  for (index = 0; index < value_list_.size(); ++index) {
      if (time == value_list_[index].ns1970) {
        break;
      }
  }
  return index < value_list_.size() ? std::optional<size_t>(index)
      : std::optional<size_t>();
}

size_t SignalObserver::NofValidSamples() const {
  return std::ranges::count_if(value_list_, [] (const auto& sample) {
    return sample.value.has_value();
  });
}

template <>
bool SignalObserver::ChannelValue(size_t index, uint64_t& ns1970,
                                  std::string& value) const {
  if (index >= value_list_.size()) {
    return false;
  }
  const auto& sample = value_list_[index];
  bool valid = sample.value.has_value();
  ns1970 = sample.ns1970;

  value.clear();

    switch (signal_.DataType()) {
      case SignalDataType::SignedData: {
        try {
          const auto temp = std::any_cast<int64_t>(sample.value);
          value = std::to_string(temp);
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
          try {
            const auto temp = std::any_cast<std::vector<uint8_t>>(sample.value);
            std::ostringstream out;
            for (const auto input : temp) {
              if (input == 0 || input == 0xFF) {
                break;
              }
              out << static_cast<char>(input);
            }
            value = out.str();
          } catch (const std::exception&) {
            valid = false;
          }
        } else {
          try {
            const auto temp = std::any_cast<uint64_t>(sample.value);
            value = std::to_string(temp);
          } catch (const std::exception&) {
            valid = false;
          }
        }
        break;
      }

      case SignalDataType::FloatData: {
        try {
          const auto temp = std::any_cast<float>(sample.value);
          std::ostringstream temp_text;
          temp_text << temp;
          value =temp_text.str();
        } catch (const std::exception&) {
          valid = false;
        }
        break;
      }

      case SignalDataType::DoubleData: {
        try {
          const auto temp = std::any_cast<double>(sample.value);
          std::ostringstream temp_text;
          temp_text << temp;
          value =temp_text.str();
        } catch (const std::exception&) {
          valid = false;
        }
        break;
      }

      default:
        break;
    }
    if (!valid) {
      value = "*";
    }
    return valid;
}

template <>
bool SignalObserver::EngValue(size_t index, uint64_t& ns1970,
                              std::string& value) const {
  if (index >= value_list_.size()) {
    return false;
  }
  const auto& sample = value_list_[index];
  bool valid = sample.value.has_value();
  ns1970 = sample.ns1970;

  value.clear();

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
        std::ostringstream conv;
        conv << temp;
        value = conv.str();
      } else if (!signal_.EnumList().empty()) {
        value = signal_.GetEnumString(channel);
      } else {
        value = std::to_string(channel);
      }
      break;
    }

    case SignalDataType::UnsignedData: {
      size_t bytes = signal_.BitLength() / 8;
      if ((signal_.BitLength() % 8) != 0) {
        ++bytes;
      }
      if (bytes > 8) {
        valid = ChannelValue(index, ns1970, value); // Return the channel value
      } else {
        uint64_t channel = 0;
        valid = ChannelValue(index, ns1970, channel);
        if (need_to_convert) {
          auto temp = static_cast<double>(channel);
          temp *= signal_.Scale();
          temp += signal_.Offset();
          std::ostringstream conv;
          conv << temp;
          value = conv.str();
        } else if (!signal_.EnumList().empty()) {
          value = signal_.GetEnumString(static_cast<int64_t>(channel));
        } else {
          value = std::to_string(channel);
        }
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
        std::ostringstream conv;
        conv << temp;
        value = conv.str();
      } else {
        value = std::to_string(channel);
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
        std::ostringstream conv;
        conv << temp;
        value = conv.str();
      } else {
        value = std::to_string(channel);
      }
      break;
    }

    default:
      break;
  }
  if (!valid) {
    value = "*";
  }
  return valid;
}

}  // namespace dbc