/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */
/** \file isampleobserver.h
 * \brief Internal object that define an observer interface that handle samples.
 */
#pragma once
#include <cstdint>
namespace dbc {
/** \brief Interface that handles samples. Internal usage.
 */
class ISampleObserver {
 public:

  virtual ~ISampleObserver() = default; ///< Default destructor.

  virtual void OnSample() = 0; ///< Handle a sample.

 protected:
  ISampleObserver() = default; ///< Default constructor.
};

}  // namespace dbc
