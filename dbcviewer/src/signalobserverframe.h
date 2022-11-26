/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <wx/frame.h>

#include <memory>

#include "signalobserverlistview.h"
namespace dbc::viewer {

class SignalObserverFrame : public wxFrame {
 public:
  SignalObserverFrame(std::unique_ptr<SignalObserverList>& observer_list,
                      wxWindow *parent, wxWindowID id, const wxString& title);
  void BaseTime(uint64_t ns1970);

 private:
  SignalObserverListView* list_view_ = nullptr;
};

} // namespace dbc::viewer



