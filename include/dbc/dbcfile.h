/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once
#include <string>
#include <memory>
#include "dbc/network.h"

namespace dbc {

class DbcFile {
 public:
  void Filename(const std::string& filename) {filename_ = filename; }
  [[nodiscard]] const std::string& FileName() const {return filename_; }

  [[nodiscard]] std::string Name() const;

  [[nodiscard]] const std::string& LastError() const { return last_error_; }

  [[nodiscard]] const Network* GetNetwork() const { return network_.get(); }

  [[nodiscard]] bool ParseFile();
 private:
  std::string filename_; ///< Full path name
  mutable std::string last_error_; ///< Last error message
  std::unique_ptr<Network> network_;
};

}  // namespace dbc
