/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <wx/wx.h>
#include <dbc/network.h>

namespace dbc::viewer {

class ProtocolDialog : public wxDialog {
 public:
  explicit ProtocolDialog(wxWindow* parent);

  void Protocol(ProtocolType type);
  [[nodiscard]] ProtocolType Protocol() const;

  void Bus(BusType type);
  [[nodiscard]] BusType Bus() const;

 private:
  wxChoice* protocol_ = nullptr;
  wxChoice* bus_ = nullptr;
};

}  // namespace dbc
