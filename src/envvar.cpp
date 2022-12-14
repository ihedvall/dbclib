/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/envvar.h"

namespace dbc {

void EnvVar::EnumList(const std::map<int64_t, std::string>& enum_list) {
  enum_list_ = enum_list;
}

const std::map<int64_t, std::string>& EnvVar::EnumList() const {
  return enum_list_;
}

std::string EnvVar::TypeAsString() const {
  switch (type_) {
    case EnvType::IntegerType:
      return "Integer";

    case EnvType::FloatType:
      return "Float";

    case EnvType::StringType:
      return "String";

    case EnvType::DataType:
      return "Data";

    default:
      break;
  }
  return {};
}
}  // namespace dbc