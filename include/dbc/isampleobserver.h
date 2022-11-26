/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once
#include <cstdint>
namespace dbc {

class ISampleObserver {
 public:
  ISampleObserver() = default;
  virtual ~ISampleObserver() = default;
  virtual void OnSample() = 0;
  virtual void DetachObserver() = 0;
};

}  // namespace dbc
