/*
 * Copyright 2021 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#include "testread.h"

#include <chrono>
#include <filesystem>
#include <map>
#include <string>

#include "dbc/dbcfile.h"

using namespace std::filesystem;
using namespace std::chrono_literals;

namespace {
const std::string dbc_source_dir = "k:/test/dbc";
using DbcList = std::map<std::string, std::string>;
DbcList dbc_list;

std::string GetDbcFile(const std::string &name) {
  auto itr = dbc_list.find(name);
  return itr == dbc_list.cend() ? std::string() : itr->second;
}

}  // namespace

namespace dbc::test {

void TestRead::SetUpTestSuite() {
  dbc_list.clear();
  try {
    for (const auto &entry : recursive_directory_iterator(dbc_source_dir)) {
      if (!entry.is_regular_file()) {
        continue;
      }
      const auto &p = entry.path();

      if (p.has_extension() && p.extension().string() == ".dbc") {
        dbc_list.emplace(p.stem().string(), p.string());

      }
    }
  } catch (const std::exception &error) {
    std::cout << "Failed to fetch the DBC test files. Error: "
                << error.what();
  }
}

void TestRead::TearDownTestSuite() {
}

TEST_F(TestRead, CheckParser)  // NOLINT
{
  for (const auto &itr : dbc_list) {
    dbc::DbcFile file;
    file.Filename(itr.second);
    const auto parse = file.ParseFile();
    EXPECT_TRUE(parse) << itr.first;
    auto* network = file.GetNetwork();
    EXPECT_TRUE(network != nullptr);

    std::cout << file.Name() << (parse ? " : OK" : " : FAIL") << std::endl;
  }
}

TEST_F(TestRead, CheckMessage)  // NOLINT
{
  if (!dbc_list.empty()) {
    dbc::DbcFile file;
    file.Filename(dbc_list.begin()->second);
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
                //<< ", Node: " << message.Node()
                << ". Comment: " << message.Comment()
                << std::endl;
    }


  }
}


}  // namespace mdf::test
