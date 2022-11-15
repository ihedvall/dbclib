/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <wx/docview.h>
#include <wx/wx.h>

#include <memory>

#include "dbc/dbcfile.h"

namespace dbc::viewer {

class DbcDocument : public wxDocument {
 public:
  DbcDocument() = default;
  ~DbcDocument() override = default;

  bool OnOpenDocument(const wxString &filename) override;

  [[nodiscard]] const DbcFile* GetFile() const {
    return !dbc_file_  ? nullptr : dbc_file_.get();
  }

 private:
  std::unique_ptr<DbcFile> dbc_file_;

  void OnShowGroupData(wxCommandEvent& event);
  void OnUpdateShowGroupData(wxUpdateUIEvent& event);

  void OnShowChannelData(wxCommandEvent& event);
  void OnUpdateShowChannelData(wxUpdateUIEvent& event);

  void OnPlotChannelData(wxCommandEvent& event);
  void OnUpdatePlotChannelData(wxUpdateUIEvent& event);
  wxDECLARE_DYNAMIC_CLASS(DbcDocument);
  wxDECLARE_EVENT_TABLE();
};



}



