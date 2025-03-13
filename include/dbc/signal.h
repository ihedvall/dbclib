/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */
/** \file signal.h
 * \brief Interface against a DBC signal configuration.
 */
#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <utility>

#include "dbc/attribute.h"
#include "dbc/isampleobserver.h"

namespace dbc {
/** \brief Support function that holds the channel value for a signal. */
struct SignalValue {
  bool valid = false; ///< True if the value is valid.
  int64_t signed_value = 0; ///< Integer value.
  uint64_t unsigned_value = 0; ///< Unsigned value.
  double float_value = 0; ///< Float value.
  std::vector<uint8_t> array_value; ///< Array or string value.
  /** \brief Resets the value. */
  void Clear() {
    valid = false;
    signed_value = 0;
    unsigned_value = 0;
    float_value = 0;
    array_value.clear();
  }
};

/** \brief Signal data type. */
enum class SignalDataType : int {
  SignedData, ///< Signed integer.
  UnsignedData, ///< Unsigned integer.
  FloatData, ///< Float value.
  DoubleData ///< Double value
};

/** \brief Multiplexer type.
 *
 * A signal may be multiplexed i.e. have different value depending on
 * another multiplexor signal.Then someone invented the extended multiplexed
 * value which makes every thing confusing.
 */
enum class MuxType : int {
  NotMultiplexed, ///< Normal signal
  Multiplexor, ///< Multiplexor signal.
  Multiplexed, ///< Multiplexed signal.
  ExtendedMultiplexor ///< Extended multiplexor signal.
};

/** \brief Min and Max range definition. */
using RangePair = std::pair<size_t, size_t>;

/** \brief Support function for the extended multiplexor functionality. */
struct ExtendedMux {
  std::string multiplexor; ///< Signal name of the multiplexor.
  std::vector<RangePair> range_list; ///< Active range for the multiplexor.
  [[nodiscard]] bool InRange(size_t value) const; ///< True if value is active.
};

/** \brief Interface against a DBC signal configuration.
 *
 */
class Signal {
 public:
  virtual ~Signal(); ///< Destructor

  /** \brief Sets the signal name. */
  void Name(const std::string& name) { name_ = name; }
  /** \brief Returns the signal name. */
  [[nodiscard]] const std::string& Name() const { return name_; }

  /** \brief Sets the unit of measure. */
  void Unit(const std::string& unit) { unit_ = unit; }
  /** \brief Returns the unit of measure. */
  [[nodiscard]] const std::string& Unit() const { return unit_; }

  /** \brief Sets the descriptive text. */
  void Comment(const std::string& comment) { comment_ = comment; }
  /** \brief Returns the descriptive text. */
  [[nodiscard]] const std::string& Comment() const { return comment_; }

  /** \brief Sets the data type. */
  void DataType(SignalDataType type) { data_type_ = type; }
  /** \brief Returns the data type. */
  [[nodiscard]] SignalDataType DataType() const { return data_type_; }
  /** \brief Returns the data type as text. */
  [[nodiscard]] std::string DataTypeAsString() const;

  /** \brief Sets the multiplexer type. */
  void Mux(MuxType type) { mux_type_ = type; }
  /** \brief Returns the multiplexer type. */
  [[nodiscard]] MuxType Mux() const { return mux_type_; }
  /** \brief Returns the multiplexer type as text. */
  [[nodiscard]] std::string MuxAsString() const;

  /** \brief Sets the multiplexor value. */
  void MuxValue(int value) { mux_value_ = value; }
  /** \brief Returns the multiplexor value. */
  [[nodiscard]] int MuxValue() const { return mux_value_; }

  /** \brief Sets the start bit. */
  void BitStart(size_t start) { bit_start_ = start; }
  /** \brief Returns the start bit. */
  [[nodiscard]] size_t BitStart() const { return bit_start_; }

  /** \brief Sets the bit length. */
  void BitLength(size_t length) { bit_length_ = length; }
  /** \brief Returns the bit length. */
  [[nodiscard]] size_t BitLength() const { return bit_length_; }

  /** \brief Set true if little endian byte order. */
  void LittleEndian(bool endian) { little_endian_ = endian; }
  /** \brief Return true if little endian byte order. */
  [[nodiscard]] bool LittleEndian() const { return little_endian_; }

  void Scale(double scale) { scale_ = scale; } ///< Sets the scaling constant.
  [[nodiscard]] double Scale() const { return scale_; } ///< Scaling constant.

  void Offset(double offset) { offset_ = offset; } ///< Sets the offset
  [[nodiscard]] double Offset() const { return offset_; } ///< Return offset.

  void Min(double min) { min_ = min; } ///< Sets min range.
  [[nodiscard]] double Min() const { return min_; } ///< Min range.

  void Max(double max) { max_ = max; } ///< Sets the max range.
  [[nodiscard]] double Max() const { return max_; } ///< Max range.

  /** \brief Sets the enumeration. */
  void EnumList(const std::map<int64_t, std::string>& enum_list);
  /** \brief Returns the enumeration. */
  [[nodiscard]] const std::map<int64_t, std::string>& EnumList() const;

  /** \brief Sets the receiver list. */
  void Receivers(const std::vector<std::string>& receiver_list);
  /** \brief Return the receiver list. */
  [[nodiscard]] const std::vector<std::string>& Receivers() const;

  /** \brief Sets the attribute list. */
  void Attributes(const std::vector<Attribute>& attribute_list) {
    attribute_list_ = attribute_list;
  }
  /** \brief Returns the attribute list. */
  [[nodiscard]] const std::vector<Attribute>& Attributes() const {
    return attribute_list_;
  }

  /** \brief Sets the signals message ID. */
  void MessageId(uint64_t message_id) { message_id_ = message_id;}

  /** \brief Returns the message ID that the signal belongs to. */
  [[nodiscard]] uint64_t MessageId() const { return message_id_; }

  [[nodiscard]] bool IsMultiplexed() const; ///< True if multiplexed signal.

  /**
   * \brief Return true if this signal should be treated as a string.
   *
   * This function checks if this signal may be treated as a string
   * value. The condition is if nof bytes > 8 i.e. cannot be converted
   * any CAN data type. In theory, it could be a byte array but this
   * is not used with any CAN protocols so far.
   * @return True if this signal should be treated as a text or byte
   * array value.
   */
  [[nodiscard]] bool IsArrayValue() const;
  /** \brief Creates an attribute. */
  [[nodiscard]] Attribute& CreateAttribute(const Attribute& definition);

  /** \brief Creates an extended multiplexor struct. */
  [[nodiscard]] ExtendedMux& GetExtendedMux();

  /** \brief Returns the enumerate text for an index. */
  [[nodiscard]] std::string GetEnumString(int64_t index) const;

  /** \brief Parse out the signal value from a message data buffer. */
  void ParseMessage(const std::vector<uint8_t>& message, uint64_t ns1970,
                    uint32_t can_id);
  /** \brief Resets the sample counter. */
  void ResetSampleCounter() const {sample_counter_ = 0;}
  /** \brief Steps the sample counter. */
  void StepSampleCounter() const {++sample_counter_;}
  /** \brief Returns the sample counter. */
  size_t SampleCounter() const {return sample_counter_;}

  /** \brief Sets the sample time. */
  void SampleTime(uint64_t ns1970) {sample_time_ = ns1970;}
  /** \brief Returns the sample time. */
  [[nodiscard]] uint64_t SampleTime() const {return sample_time_;}

  /** \brief Sets the CAN ID for the sample. */
  void SampleCanId(uint32_t can_id) {sample_can_id_ = can_id;}
  /** \brief Returns the CAN ID for latest sample. */
  [[nodiscard]] uint64_t SampleCanId() const {return sample_can_id_;}

  void Valid(bool valid) {valid_ = valid;} ///< Set to true if valid value.
  [[nodiscard]] bool Valid() const {return valid_;} ///< Trie if value is valid.

  /**
   * \brief Returns a reference to the internal signal value-
   *
   * The function returns the internal signal value object which
   * is the latest channel value.
   * @return Reference to the internal signal value object.
   */
  [[nodiscard]] const SignalValue& GetSignalValue() const {
    return channel_value_;
  }
  /** \brief Returns the channel value. */
  template <typename T>
  bool ChannelValue( T& value ) const;

  /** \brief Returns the scaled engineering value. */
  template <typename T>
  bool EngValue( T& value ) const;

  /** \brief Attach a sample observer. */
  void AttachObserver(std::shared_ptr<ISampleObserver>& observer) const;
  /** \brief Detach a sample observer. */
  void ClearObserverList() const;

 protected:
  std::string name_; ///< Signal nsame.
  std::string comment_; ///< Signal description.
  std::string unit_; ///< Signal unit.

  std::vector<std::string> receiver_list_; ///< Receiver list.

  MuxType mux_type_ = MuxType::NotMultiplexed; ///< Multiplexer type.
  int mux_value_ = 0; ///< Temporary storage of mux value.
  size_t bit_start_ = 0; ///< Bit start.
  size_t bit_length_ = 0; ///< Bit length.
  bool little_endian_ = true; ///< Byte order. True if little endian.
  SignalDataType data_type_ = SignalDataType::SignedData; ///< Data type.
  double scale_ = 1.0; ///< Scale
  double offset_ = 0.0; ///< Offset
  double min_ = 0.0; ///< Min range
  double max_ = 0.0; ///< Max range.
  ExtendedMux extended_mux_; ///< Extended mux support struct.

  std::vector<Attribute> attribute_list_; ///< Attribute list.
  std::map<int64_t, std::string> enum_list_; ///< Enumeration list.

  SignalValue channel_value_; ///< Unscaled value (last reported value)

  uint64_t message_id_ = 0; ///< Message ID of last message.
  mutable size_t sample_counter_ = 0; ///< Number of samples received.
  bool valid_ = true; ///< Trie if valid.
  uint64_t sample_time_ = 0;    ///< Last sample time
  uint32_t sample_can_id_ = 0;  ///< Last Can ID

  mutable std::vector<std::shared_ptr<ISampleObserver>> observer_list_; ///< Observer list.
  void FireOnSample(); ///< Fire OnSample event.

};

template <typename T>
bool Signal::ChannelValue(T& value) const {
  bool valid = channel_value_.valid && Valid();
  value = {};

  switch (data_type_) {
    case SignalDataType::SignedData: {
      const auto temp = channel_value_.signed_value;
      value = static_cast<T>(temp);
      break;
    }

    case SignalDataType::UnsignedData: {
      if (IsArrayValue()) {
        valid = false;
      } else {
        const auto temp = channel_value_.unsigned_value;
        value = static_cast<T>(temp);
      }
      break;
    }

    case SignalDataType::DoubleData:
    case SignalDataType::FloatData: {
      const auto temp = channel_value_.float_value;
      value = static_cast<T>(temp);
      break;
    }

    default:
      valid = false;
      break;
   }
   return valid;
}

/**
 * \brief Returns the value a text string.
 * @param value Destination string.
 * @return True if the value is valid.
 */
template <>
bool Signal::ChannelValue(std::string& value) const;

/**
 * \brief Returns the channel value as a byte array.
 *
 * Returns the channel value as a byte array. No meaning if it
 * is a standard value but if the number of bytes > 8, it
 * normally indicates that the value id a text value but may also
 * be a byte array.
 * @param value Destination byte array.
 * @return True if the value is valid.
 */
template <>
bool Signal::ChannelValue(std::vector<uint8_t>& value) const;

/** \brief Returns the signal value as a signal value */
template <>
bool Signal::ChannelValue(SignalValue& value) const;


template <typename T>
bool Signal::EngValue(T& value) const {
  bool valid = false;
  value = {};
  bool need_to_convert = true;
  // If it is an enumerate. We could convert the enum string but that's weird.
  if (!enum_list_.empty()) {
    need_to_convert = false;
  }
  // Avoid truncation
  if (scale_ == 1.0 && offset_ == 0) {
    need_to_convert = false;
  }

  switch (data_type_) {
    case SignalDataType::SignedData: {
      int64_t channel = 0;
      valid = ChannelValue(channel);

      if (need_to_convert) {
        auto temp = static_cast<double>(channel);
        temp *= scale_;
        temp += offset_;
        value = static_cast<T>(temp);
      } else {
        value = static_cast<T>(channel);
      }
      break;
    }

    case SignalDataType::UnsignedData: {
      uint64_t channel = 0;
      valid = ChannelValue(channel);
      if (need_to_convert) {
        auto temp = static_cast<double>(channel);
        temp *= scale_;
        temp += offset_;
        value = static_cast<T>(temp);
      } else {
        value = static_cast<T>(channel);
      }
      break;
    }

    case SignalDataType::FloatData: {
      float channel = 0;
      valid = ChannelValue(channel);
      if (need_to_convert) {
        auto temp = static_cast<double>(channel);
        temp *= scale_;
        temp += offset_;
        value = static_cast<T>(temp);
      } else {
        value = static_cast<T>(channel);
      }
      break;
    }

    case SignalDataType::DoubleData: {
      double channel = 0;
      valid = ChannelValue(channel);
      if (need_to_convert) {
        auto temp = channel;
        temp *= scale_;
        temp += offset_;
        value = static_cast<T>(temp);
      } else {
        value = static_cast<T>(channel);
      }
      break;
    }

    default:
      break;
  }
  return valid;
}

/** \brief Returns the engineering value as a string value */
template <>
bool Signal::EngValue(std::string& value) const;

}  // namespace dbc
