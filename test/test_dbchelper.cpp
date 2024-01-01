/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include <gtest/gtest.h>
#include "dbchelper.h"
#include <bit>

namespace dbc::test {

TEST(DbcHelper, TestDouble) {
  uint8_t buffer[40] = {};
  for (double orig = -122.34; orig < 122.34; orig += 0.1) { //NOLINT
  if (std::endian::native == std::endian::little) {
      // Convert orig -> buffer
      DbcHelper::DoubleToRaw(true, 0, sizeof(orig)*8, orig, buffer);
      double native = 0;
      memcpy(&native, buffer, sizeof(native));
      EXPECT_DOUBLE_EQ(native, orig);
      native = DbcHelper::RawToDouble(true, 0, sizeof(orig)*8, buffer);
      EXPECT_DOUBLE_EQ(native, orig);

      DbcHelper::DoubleToRaw(false, 0, sizeof(orig)*8, orig, buffer);
      const double big = DbcHelper::RawToDouble(false, 0,
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
