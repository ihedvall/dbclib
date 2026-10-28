/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include <gtest/gtest.h>

#include <cstdint>
#include <bit>
#include <vector>

#include <boost/endian/buffers.hpp>

#include "dbc/signal.h"
#include "dbchelper.h"

using namespace boost::endian;

namespace dbc::test {

TEST(DbcHelper, TestLittleDouble) {

  uint8_t buffer[sizeof(double)] = {0};
  constexpr double reference_value = 123.45;
  constexpr bool little = true;
  constexpr size_t bit_start = 0;
  constexpr size_t bit_length = sizeof(double)*8;

  const little_float64_buf_t data(reference_value);

  EXPECT_EQ(reference_value, data.value());

  DbcHelper::DoubleToRaw(little, bit_start, bit_length, reference_value, buffer);
  const int cmp = memcmp(buffer, data.data(), sizeof(double));
  EXPECT_EQ(0, cmp);

  const double value = DbcHelper::RawToDouble(little, bit_start, bit_length, buffer);
  EXPECT_EQ(reference_value, value);
}

TEST(DbcHelper, TestBigDouble) {
  uint8_t buffer[sizeof(double)] = {0};
  constexpr double reference_value = 123.45;
  constexpr bool little = false;
  constexpr size_t bit_start = 7;
  constexpr size_t bit_length = sizeof(double)*8;

  const big_float64_buf_t data(reference_value);

  EXPECT_EQ(reference_value, data.value());

  DbcHelper::DoubleToRaw(little, bit_start, bit_length, reference_value, buffer);
  const int cmp = memcmp(buffer, data.data(), sizeof(double));
  EXPECT_EQ(0, cmp);

  const double value = DbcHelper::RawToDouble(little, bit_start, bit_length, buffer);
  EXPECT_EQ(reference_value, value);
}

TEST(DbcHelper, TestLittleFloat) {

  uint8_t buffer[sizeof(float)] = {0};
  constexpr float reference_value = 123.45;
  constexpr bool little = true;
  constexpr size_t bit_start = 0;
  constexpr size_t bit_length = sizeof(float)*8;

  const little_float32_buf_t data(reference_value);

  EXPECT_EQ(reference_value, data.value());

  DbcHelper::FloatToRaw(little, bit_start, bit_length, reference_value, buffer);
  const int cmp = memcmp(buffer, data.data(), sizeof(float));
  EXPECT_EQ(0, cmp);

  const float value = DbcHelper::RawToFloat(little, bit_start, bit_length, buffer);
  EXPECT_EQ(reference_value, value);
}

TEST(DbcHelper, TestBigFloat) {
  uint8_t buffer[sizeof(float)] = {0};
  constexpr float reference_value = 123.45;
  constexpr bool little = false;
  constexpr size_t bit_start = 7;
  constexpr size_t bit_length = sizeof(float)*8;

  const big_float32_buf_t data(reference_value);

  EXPECT_EQ(reference_value, data.value());

  DbcHelper::FloatToRaw(little, bit_start, bit_length, reference_value, buffer);
  const int cmp = memcmp(buffer, data.data(), sizeof(float));
  EXPECT_EQ(0, cmp);

  const float value = DbcHelper::RawToFloat(little, bit_start, bit_length, buffer);
  EXPECT_EQ(reference_value, value);
}

TEST(DbcHelper, TestLittleInt) {

  uint8_t buffer[sizeof(int32_t)] = {0};
  constexpr int32_t reference_value = -12345;
  constexpr bool little = true;
  constexpr size_t bit_start = 0;
  constexpr size_t bit_length = sizeof(int32_t)*8;

  const little_int32_buf_t data(reference_value);

  EXPECT_EQ(reference_value, data.value());

  DbcHelper::SignedToRaw(little, bit_start, bit_length, reference_value, buffer);
  const int cmp = memcmp(buffer, data.data(), sizeof(int32_t));
  EXPECT_EQ(0, cmp);

  const int64_t value = DbcHelper::RawToSigned(little, bit_start, bit_length, buffer);
  EXPECT_EQ(reference_value, value);
}

TEST(DbcHelper, TestBigInt) {
  uint8_t buffer[sizeof(int32_t)] = {0};
  constexpr int32_t reference_value = -12345;
  constexpr bool little = false;
  constexpr size_t bit_start = 7;
  constexpr size_t bit_length = sizeof(int32_t)*8;

  const big_int32_buf_t data(reference_value);

  EXPECT_EQ(reference_value, data.value());

  DbcHelper::SignedToRaw(little, bit_start, bit_length, reference_value, buffer);
  const int cmp = memcmp(buffer, data.data(), sizeof(int32_t));
  EXPECT_EQ(0, cmp);

  const int64_t value = DbcHelper::RawToSigned(little, bit_start, bit_length, buffer);
  EXPECT_EQ(reference_value, value);
}

TEST(DbcHelper, TestLittleUInt) {

  uint8_t buffer[sizeof(uint32_t)] = {0};
  constexpr uint32_t reference_value = 12345;
  constexpr bool little = true;
  constexpr size_t bit_start = 0;
  constexpr size_t bit_length = sizeof(uint32_t)*8;

  const little_uint32_buf_t data(reference_value);

  EXPECT_EQ(reference_value, data.value());

  DbcHelper::UnsignedToRaw(little, bit_start, bit_length, reference_value, buffer);
  const int cmp = memcmp(buffer, data.data(), sizeof(uint32_t));
  EXPECT_EQ(0, cmp);

  const uint64_t value = DbcHelper::RawToUnsigned(little, bit_start, bit_length, buffer);
  EXPECT_EQ(reference_value, value);
}

TEST(DbcHelper, TestBigUInt) {
  uint8_t buffer[sizeof(uint32_t)] = {0};
  constexpr uint32_t reference_value = 12345;
  constexpr bool little = false;
  constexpr size_t bit_start = 7;
  constexpr size_t bit_length = sizeof(uint32_t)*8;

  const big_uint32_buf_t data(reference_value);

  EXPECT_EQ(reference_value, data.value());

  DbcHelper::UnsignedToRaw(little, bit_start, bit_length, reference_value, buffer);
  const int cmp = memcmp(buffer, data.data(), sizeof(int32_t));
  EXPECT_EQ(0, cmp);

  const uint64_t value = DbcHelper::RawToUnsigned(little, bit_start, bit_length, buffer);
  EXPECT_EQ(reference_value, value);
}

TEST(DbcHelper, TestDouble) {
  uint8_t buffer[sizeof(double)] = {0};

  for (double orig = -122.34; orig < 122.34; orig += 0.1) { //NOLINT
  if (std::endian::native == std::endian::little) {
      // Convert orig -> buffer
      DbcHelper::DoubleToRaw(true, 0, sizeof(orig)*8, orig, buffer);
      double native = 0;
      memcpy(&native, buffer, sizeof(native));
      EXPECT_DOUBLE_EQ(native, orig);
      native = DbcHelper::RawToDouble(true, 0, sizeof(orig)*8, buffer);
      EXPECT_DOUBLE_EQ(native, orig);

      DbcHelper::DoubleToRaw(false, 7, sizeof(orig)*8, orig, buffer);
      const double big = DbcHelper::RawToDouble(false, 7,
                                                sizeof(orig)*8, buffer);
      EXPECT_DOUBLE_EQ(orig, big);

      // Test faulty start bit
      DbcHelper::DoubleToRaw(false, 0, sizeof(orig)*8, orig, buffer);
    } else {
      DbcHelper::DoubleToRaw(false, 7, sizeof(orig)*8, orig, buffer);
      double native = 0;
      memcpy(&native, buffer, sizeof(native));
      EXPECT_DOUBLE_EQ(native, orig);
      native = DbcHelper::RawToDouble(false, 7, sizeof(orig)*8, buffer);
      EXPECT_DOUBLE_EQ(native, orig);

      DbcHelper::DoubleToRaw(true, 0, sizeof(orig)*8, orig, buffer);
      const double little = DbcHelper::RawToDouble(true, 0,
                                                sizeof(orig)*8, buffer);
      EXPECT_DOUBLE_EQ(orig, little);
    }

  }
}

TEST(DbcHelper, TestFloat) {
  uint8_t buffer[40] = {}; // I'm using last 4 bytes only
  for (float orig = -122.34F; orig < 122.34F; orig += 0.1F) { //NOLINT

    if (std::endian::native == std::endian::little) {
      DbcHelper::FloatToRaw(true, 32, sizeof(orig)*8, orig, buffer);
      float native = 0;
      memcpy(&native, buffer + 4, sizeof(native));
      EXPECT_FLOAT_EQ(native, orig);
      native = DbcHelper::RawToFloat(true, 32, sizeof(orig)*8, buffer);
      EXPECT_FLOAT_EQ(native, orig);

      DbcHelper::FloatToRaw(false, 39, sizeof(orig)*8, orig, buffer);
      const float big = DbcHelper::RawToFloat(false, 39,
                                                sizeof(orig)*8, buffer);
      EXPECT_FLOAT_EQ(orig, big);

      // Test faulty start bit
      DbcHelper::FloatToRaw(false, 32, sizeof(orig)*8, orig, buffer);
    } else {
      DbcHelper::FloatToRaw(false, 39, sizeof(orig)*8, orig, buffer);
      float native = 0;
      memcpy(&native, buffer + 4, sizeof(native));
      EXPECT_FLOAT_EQ(native, orig);
      native = DbcHelper::RawToFloat(true, 39, sizeof(orig)*8, buffer);
      EXPECT_FLOAT_EQ(native, orig);

      DbcHelper::FloatToRaw(true, 32, sizeof(orig)*8, orig, buffer);
      const float little = DbcHelper::RawToFloat(true, 32,
                                                   sizeof(orig)*8, buffer);
      EXPECT_FLOAT_EQ(orig, little);
    }
  }
}

TEST(DbcHelper, TestSigned) {
  uint8_t buffer[40] = {};
  for (size_t length = 3; length <= 64; ++length) {
    for (int64_t orig = -3; orig <= 3; ++orig ) {
      DbcHelper::SignedToRaw(true, 0, length, orig, buffer);
      const auto little = DbcHelper::RawToSigned(true, 0, length, buffer);
      EXPECT_EQ(little, orig);

      DbcHelper::SignedToRaw(false, 7, length, orig, buffer);
      const auto big = DbcHelper::RawToSigned(false, 7, length, buffer);
      EXPECT_EQ(big, orig);
    }
  }

  int64_t orig0 = 0;
  DbcHelper::SignedToRaw(true, 0, 0, orig0, buffer);
  const auto little0 = DbcHelper::RawToSigned(true, 0, 0, buffer);
  EXPECT_EQ(little0, orig0);

  int64_t orig1 = -1;
  DbcHelper::SignedToRaw(true, 62, 1, orig1, buffer);
  const auto little1 = DbcHelper::RawToSigned(true, 62, 1, buffer);
  EXPECT_EQ(little1, orig1);

  int64_t orig64 = INT64_MIN;
  DbcHelper::SignedToRaw(true, 0, 64, orig64, buffer);
  const auto little64 = DbcHelper::RawToSigned(true, 0, 64, buffer);
  EXPECT_EQ(little64, orig64);
}

TEST(DbcHelper, TestUnsigned) {
  uint8_t buffer[40] = {};
  for (size_t length = 2; length <= 64; ++length) {
    for (uint64_t orig = 0; orig <= 3; ++orig ) {
      DbcHelper::UnsignedToRaw(true, 0, length, orig, buffer);
      const auto little = DbcHelper::RawToUnsigned(true, 0, length, buffer);
      EXPECT_EQ(little, orig);

      DbcHelper::UnsignedToRaw(false, 7, length, orig, buffer);
      const auto big = DbcHelper::RawToUnsigned(false, 7, length, buffer);
      EXPECT_EQ(big, orig);
    }
  }

  uint64_t orig0 = 0;
  DbcHelper::UnsignedToRaw(true, 0, 0, orig0, buffer);
  const auto little0 = DbcHelper::RawToUnsigned(true, 0, 0, buffer);
  EXPECT_EQ(little0, orig0);

  uint64_t orig1 = 1;
  DbcHelper::UnsignedToRaw(true, 62, 1, orig1, buffer);
  const auto little1 = DbcHelper::RawToUnsigned(true, 62, 1, buffer);
  EXPECT_EQ(little1, orig1);

  uint64_t orig64 = UINT64_MAX;
  DbcHelper::UnsignedToRaw(true, 0, 64, orig64, buffer);
  const auto little64 = DbcHelper::RawToUnsigned(true, 0, 64, buffer);
  EXPECT_EQ(little64, orig64);
}

TEST(DbcHelper, TestRawToByteArray) {
  constexpr uint8_t orig[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
  const std::vector<uint8_t> buffer = DbcHelper::RawToByteArray(7, 8*8, orig);
  ASSERT_EQ(buffer.size(), 8);
  for (size_t index = 0; index < 8; ++index) {
    EXPECT_EQ(buffer[index], orig[index]);
  }
}

TEST(DbcHelper, TestSetAllBits) {
  {
    uint8_t buffer[sizeof(uint32_t)] = {0,0,0,0};
    constexpr uint32_t reference_value = 0xFFFFFFFF;
    constexpr bool little = true;
    constexpr size_t bit_start = 0;
    constexpr size_t bit_length = sizeof(uint32_t)*8;

    const little_uint32_buf_t data(reference_value);

    EXPECT_EQ(reference_value, data.value());

    DbcHelper::SetAllBits(little, bit_start, bit_length, buffer);
    const int cmp = memcmp(buffer, data.data(), sizeof(uint32_t));
    EXPECT_EQ(0, cmp);
  }

  {
    uint8_t buffer[sizeof(uint32_t)] = {0,0,0,0};
    constexpr uint32_t reference_value = 0xFFFFFFFF;
    constexpr bool little = false;
    constexpr size_t bit_start = 7;
    constexpr size_t bit_length = sizeof(uint32_t)*8;

    const big_uint32_buf_t data(reference_value);

    EXPECT_EQ(reference_value, data.value());

    DbcHelper::SetAllBits(little, bit_start, bit_length, buffer);
    const int cmp = memcmp(buffer, data.data(), sizeof(uint32_t));
    EXPECT_EQ(0, cmp);
  }
}

TEST(DbcHelper, ParseJ1939FlagsLittle) {
  Signal signal;
  signal.Name("Little");
  signal.DataType(SignalDataType::UnsignedData);
  signal.BitStart(0);
  signal.BitLength(4*8);
  signal.LittleEndian(true);
  signal.Scale(1.0);
  signal.Offset(0.0);
  signal.Min(0.0);
  signal.Max(32000.0);

  {
    constexpr uint32_t na_value = 0xFFFFFFFF;
    const little_uint32_buf_t error(na_value);
    std::vector<uint8_t> message = DbcHelper::RawToByteArray(signal.BitStart(), signal.BitLength(), error.data());
    EXPECT_EQ(sizeof(uint32_t), message.size());
    signal.ParseMessage(message, 0, 0, true);
    EXPECT_FALSE(signal.IsValid());
    EXPECT_TRUE(signal.IsOutOfRange());
    EXPECT_TRUE(signal.IsNotAvailable());
    EXPECT_FALSE(signal.IsError());
    EXPECT_FALSE(signal.IsReserved());
  }

  {
    constexpr uint32_t error_value = 0xFFFFFFFE;
    const little_uint32_buf_t error(error_value);
    std::vector<uint8_t> message = DbcHelper::RawToByteArray(signal.BitStart(), signal.BitLength(), error.data());
    EXPECT_EQ(sizeof(uint32_t), message.size());
    signal.ParseMessage(message, 0, 0, true);
    EXPECT_FALSE(signal.IsValid());
    EXPECT_TRUE(signal.IsOutOfRange());
    EXPECT_FALSE(signal.IsNotAvailable());
    EXPECT_TRUE(signal.IsError());
    EXPECT_FALSE(signal.IsReserved());
  }
  {
    constexpr uint32_t reserved_value = 0xFFFFFFFD;
    const little_uint32_buf_t error(reserved_value);
    std::vector<uint8_t> message = DbcHelper::RawToByteArray(signal.BitStart(), signal.BitLength(), error.data());
    EXPECT_EQ(sizeof(uint32_t), message.size());
    signal.ParseMessage(message, 0, 0, true);
    EXPECT_FALSE(signal.IsValid());
    EXPECT_TRUE(signal.IsOutOfRange());
    EXPECT_FALSE(signal.IsNotAvailable());
    EXPECT_FALSE(signal.IsError());
    EXPECT_TRUE(signal.IsReserved());
  }

  {
    const auto max_value = static_cast<uint32_t>(signal.Max()) ;
    const little_uint32_buf_t error(max_value);
    std::vector<uint8_t> message = DbcHelper::RawToByteArray(signal.BitStart(), signal.BitLength(), error.data());
    EXPECT_EQ(sizeof(uint32_t), message.size());
    signal.ParseMessage(message, 0, 0, true);
    EXPECT_TRUE(signal.IsValid());
    EXPECT_FALSE(signal.IsOutOfRange());
    EXPECT_FALSE(signal.IsNotAvailable());
    EXPECT_FALSE(signal.IsError());
    EXPECT_FALSE(signal.IsReserved());
  }
}

TEST(DbcHelper, ParseJ1939FlagsBig) {
  Signal signal;
  signal.Name("Big");
  signal.DataType(SignalDataType::UnsignedData);
  signal.BitStart(7);
  signal.BitLength(4*8);
  signal.LittleEndian(false);
  signal.Scale(1.0);
  signal.Offset(0.0);
  signal.Min(0.0);
  signal.Max(32000.0);

  {
    constexpr uint32_t na_value = 0xFFFFFFFF;
    const big_uint32_buf_t error(na_value);
    std::vector<uint8_t> message = DbcHelper::RawToByteArray(signal.BitStart(), signal.BitLength(), error.data());
    EXPECT_EQ(sizeof(uint32_t), message.size());
    signal.ParseMessage(message, 0, 0, true);
    EXPECT_FALSE(signal.IsValid());
    EXPECT_TRUE(signal.IsOutOfRange());
    EXPECT_TRUE(signal.IsNotAvailable());
    EXPECT_FALSE(signal.IsError());
    EXPECT_FALSE(signal.IsReserved());
  }

  {
    constexpr uint32_t error_value = 0xFFFFFFFE;
    const big_uint32_buf_t error(error_value);
    std::vector<uint8_t> message = DbcHelper::RawToByteArray(signal.BitStart(), signal.BitLength(), error.data());
    EXPECT_EQ(sizeof(uint32_t), message.size());
    signal.ParseMessage(message, 0, 0, true);
    EXPECT_FALSE(signal.IsValid());
    EXPECT_TRUE(signal.IsOutOfRange());
    EXPECT_FALSE(signal.IsNotAvailable());
    EXPECT_FALSE(signal.IsError());
    EXPECT_FALSE(signal.IsReserved());
  }
  {
    constexpr uint32_t reserved_value = 0xFFFFFFFD;
    const big_uint32_buf_t error(reserved_value);
    std::vector<uint8_t> message = DbcHelper::RawToByteArray(signal.BitStart(), signal.BitLength(), error.data());
    EXPECT_EQ(sizeof(uint32_t), message.size());
    signal.ParseMessage(message, 0, 0, true);
    EXPECT_FALSE(signal.IsValid());
    EXPECT_TRUE(signal.IsOutOfRange());
    EXPECT_FALSE(signal.IsNotAvailable());
    EXPECT_FALSE(signal.IsError());
    EXPECT_FALSE(signal.IsReserved());
  }

  {
    const auto max_value = static_cast<uint32_t>(signal.Max()) ;
    const big_uint32_buf_t error(max_value);
    std::vector<uint8_t> message = DbcHelper::RawToByteArray(signal.BitStart(), signal.BitLength(), error.data());
    EXPECT_EQ(sizeof(uint32_t), message.size());
    signal.ParseMessage(message, 0, 0, true);
    EXPECT_TRUE(signal.IsValid());
    EXPECT_FALSE(signal.IsOutOfRange());
    EXPECT_FALSE(signal.IsNotAvailable());
    EXPECT_FALSE(signal.IsError());
    EXPECT_FALSE(signal.IsReserved());
  }
}

TEST(DbcHelper, TestIsAllBitsSet) {
  {
    constexpr uint32_t reference_value1 = 0xFFFFFFFF;
    constexpr uint32_t reference_value2 = 0xFFFFFFFE;
    constexpr bool little = true;
    constexpr size_t bit_start = 0;
    constexpr size_t bit_length = sizeof(uint32_t)*8;

    const little_uint32_buf_t data1(reference_value1);
    const little_uint32_buf_t data2(reference_value2);
    EXPECT_TRUE(DbcHelper::IsAllBitsSet(little, bit_start, bit_length, data1.data()));
    EXPECT_FALSE(DbcHelper::IsAllBitsSet(little, bit_start, bit_length, data2.data()));
  }

  {
    constexpr uint32_t reference_value1 = 0xFFFFFFFF;
    constexpr uint32_t reference_value2 = 0xFFFFFFFE;
    constexpr bool little = false;
    constexpr size_t bit_start = 7;
    constexpr size_t bit_length = sizeof(uint32_t)*8;

    const big_uint32_buf_t data1(reference_value1);
    const big_uint32_buf_t data2(reference_value2);
    EXPECT_TRUE(DbcHelper::IsAllBitsSet(little, bit_start, bit_length, data1.data()));
    EXPECT_FALSE(DbcHelper::IsAllBitsSet(little, bit_start, bit_length, data2.data()));

  }
}
TEST(DbcHelper, TestGetStem) {
  {
    const auto stem = DbcHelper::GetStem("");
    EXPECT_TRUE(stem.empty());
  }

  {
    const auto stem = DbcHelper::GetStem("olle.txt");
    EXPECT_STREQ(stem.c_str(), "olle");
  }

  {
    const auto stem = DbcHelper::GetStem("c:\\olle.txt");
    EXPECT_STREQ(stem.c_str(), "olle");
  }

  {
    const auto stem = DbcHelper::GetStem("c:\\daddy.cool/olle.txt");
    EXPECT_STREQ(stem.c_str(), "olle");
  }

  {
    const auto stem = DbcHelper::GetStem("//daddy.cool/olle.txt");
    EXPECT_STREQ(stem.c_str(), "olle");
  }
}

}
