/*
 * Copyright 2021 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#include "testread.h"
#include <filesystem>
#include <map>
#include <string_view>
#include <string>
#include <cctype>    // std::tolower
#include <algorithm> // std::equal
#include "dbc/dbcfile.h"

using namespace std::filesystem;

namespace {
constexpr std::string_view kDbcSourceDir = "k:/test/dbc";
constexpr std::string_view kLocaleDbc = "proba";

using DbcList = std::map<std::string, std::string>;
DbcList kDbcList;

bool IEquals(const std::string& text1, const std::string& text2) {
  return std::equal(text1.cbegin(), text1.cend(),
                    text2.cbegin(), text2.cend(),
                    [] (const char ain, const char bin)->bool {
                      return std::tolower(static_cast<unsigned char>(ain)) ==
                             std::tolower(static_cast<unsigned char>(bin));
                    });
}
std::string GetDbcFile(const std::string &name) {

  const auto exist = std::find_if( kDbcList.cbegin(), kDbcList.cend(),
                       [&] (const auto& itr) {
                           return IEquals(itr.first, name);
                         });
  return exist == kDbcList.cend() ? std::string() : exist->second;
}

}  // namespace

namespace dbc::test {

void TestRead::SetUpTestSuite() {
  kDbcList.clear();
  try {
    for (const directory_entry &entry : recursive_directory_iterator(kDbcSourceDir)) {
      if (!entry.is_regular_file()) {
        continue;
      }
      const auto &p = entry.path();

      if (p.has_extension() && p.extension().string() == ".dbc") {
        kDbcList.emplace(p.stem().string(), p.string());
      }
    }
  } catch (const std::exception &error) {
    std::cout << "Failed to fetch the DBC test files. Error: "
                << error.what();
  }
}

void TestRead::TearDownTestSuite() {
}

TEST_F(TestRead, CheckParser)
{
  if (kDbcList.empty()) {
    GTEST_SKIP_("No files to parse.");
  }
  for (const auto &[name, filename] : kDbcList) {
    dbc::DbcFile file;
    file.Filename(filename);
    const auto parse = file.ParseFile();
    EXPECT_TRUE(parse) << name;
    auto* network = file.GetNetwork();
    EXPECT_TRUE(network != nullptr);

    std::cout << file.Name() << (parse ? " : OK" : " : FAIL") << std::endl;
  }
}

TEST_F(TestRead, CheckMessage)
{
  if (kDbcList.empty()) {
    GTEST_SKIP_("No files to parse.");
  }

  dbc::DbcFile file;
  file.Filename(kDbcList.cbegin()->second);
  const auto parse = file.ParseFile();
  EXPECT_TRUE(parse) << file.Name();
  auto* network = file.GetNetwork();
  ASSERT_TRUE(network != nullptr);
  const auto& message_list = network->Messages();
  for (const auto& itr : message_list) {
    const auto& message = itr.second;
    std::cout << "ID: " << message.CanId()
              << (message.IsExtended() ? "E" : "S")
              << ", Name: " << message.Name()
              << ", Bytes: " << message.NofBytes()
              << ", Node: " << message.NodeName()
              << ". Comment: " << message.Comment()
              << std::endl;
  }
}

TEST_F(TestRead, CheckLocaleFloat) {
  const std::string test_file = GetDbcFile(kLocaleDbc.data());
  if (test_file.empty()) {
    GTEST_SKIP_("Test test file doesn't exist");
  }
  std::setlocale(LC_ALL, "de_DE");

  dbc::DbcFile file;
  file.Filename(test_file);
  const auto parse = file.ParseFile();
  EXPECT_TRUE(parse) << file.Name();

  const auto* network = file.GetNetwork();
  ASSERT_TRUE(network != nullptr);

  const auto& message_list = network->Messages();
  EXPECT_EQ(message_list.size(), 1);

  for (const auto& [message_id, message ] : message_list) {
    EXPECT_STREQ(message.Name().c_str(), "proba_msg");
    EXPECT_EQ(message_id, 1306);

    std::cout << "ID: " << message.CanId()
              << (message.IsExtended() ? "E" : "S")
              << ", Name: " << message.Name()
              << ", Bytes: " << message.NofBytes()
              << ", Node: " << message.NodeName()
              << ". Comment: " << message.Comment()
              << std::endl;

    const auto& signal_list = message.Signals();
    EXPECT_EQ(signal_list.size(), 2);
    for (const auto& [signal_name, signal] : signal_list) {
      if (signal_name == "Corriente") {
        EXPECT_DOUBLE_EQ(signal.Scale(), 10.9);
        EXPECT_DOUBLE_EQ(signal.Offset(), 9.8);
      } else if (signal_name == "Tension") {
        EXPECT_DOUBLE_EQ(signal.Scale(), 10.8);
        EXPECT_DOUBLE_EQ(signal.Offset(), 12);
      } else {
        ADD_FAILURE() << "Invalid signal. " << signal_name;
      }
    }
  }

}

}  // namespace mdf::test
