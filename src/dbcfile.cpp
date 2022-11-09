/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/dbcfile.h"
#include <filesystem>
#include <fstream>
#include "dbcscanner.h"

using namespace std::filesystem;

namespace dbc {

std::string DbcFile::Name() const {
  try {
    const path filename(filename_);
    return filename.stem().string();
  } catch (const std::exception& err) {
    last_error_ = err.what();
  }
  return {};
}
bool DbcFile::ParseFile() {
  int ret = -1;
  try {
    const path filename(filename_);
    if (!exists(filename)) {
      std::ostringstream error;
      error << "The file doesn't exist. File: " << filename_;
      return false;
    }

    std::ifstream temp(filename_);
    DbcScanner scanner(temp);
    DbcParser parser(scanner);
    ret = parser.parse();
    last_error_ = scanner.LastError();
    temp.close();
    network_.reset(scanner.ReleaseNetwork());
  } catch (const std::exception& err) {
    std::ostringstream error;
    error << "Internal error. Error: " << err.what()
          << ". File: " << filename_;
    last_error_ = error.str();
    ret = -1;
  }
  return ret == 0;
}

}  // namespace dbc