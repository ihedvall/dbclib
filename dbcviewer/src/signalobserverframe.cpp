/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#include "signalobserverframe.h"
namespace {
#include "img/sub.xpm"
}

namespace dbc::viewer {

SignalObserverFrame::SignalObserverFrame(std::unique_ptr<SignalObserverList>&
    observer_list, wxWindow *parent, wxWindowID id, const wxString &title)
: wxFrame(parent, id,title,wxDefaultPosition,parent->GetClientSize(),
          wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT) {
#ifdef _WIN32
  wxIcon sub("SUB_ICON", wxBITMAP_TYPE_ICO_RESOURCE);
#else
  wxIcon sub {wxICON(sub)};
#endif
  SetIcon(sub);
  list_view_ = new SignalObserverListView(this);
  list_view_->AppendColumn(wxString::FromUTF8("Sample"));
  list_view_->AppendColumn(wxString::FromUTF8("Absolute Time"));
  list_view_->AppendColumn(wxString::FromUTF8("Relative Time [s]"));
  list_view_->AppendColumn(wxString::FromUTF8("Node"));
  for ( const auto& obs : *observer_list) {
    if (!obs) {
      continue;
    }
    const auto& signal = obs->GetSignal();
    std::ostringstream label;
    label << signal.Name();
    const std::string& unit = signal.Unit();
    if (!unit.empty()) {
      label << " [" << unit << "]";
    }
    list_view_->AppendColumn(wxString::From8BitData(label.str().c_str()));
  }

  list_view_->ObserverList(observer_list);
  list_view_->SetItemCount(
      static_cast<long>(list_view_->NofSamples()));
  for (int col = 0; col < list_view_->GetColumnCount(); ++col) {
    list_view_->SetColumnWidth(col, wxLIST_AUTOSIZE_USEHEADER);
  }
}

void SignalObserverFrame::BaseTime(uint64_t ns1970) {
  if (list_view_ != nullptr) {
    list_view_->BaseTime(ns1970);
  }
}

void SignalObserverFrame::SetNetwork(const Network* network) {
  if (list_view_ != nullptr) {
    list_view_->SetNetwork(network);
  }
}
}