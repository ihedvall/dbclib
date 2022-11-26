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

  [[nodiscard]] DbcFile* GetFile() const {
    return !dbc_file_  ? nullptr : dbc_file_.get();
  }

 private:
  std::unique_ptr<DbcFile> dbc_file_;
  void OnImportCanMessageFile(wxCommandEvent& event);
  void OnUpdateImportCanMessageFile(wxUpdateUIEvent& event);

  wxDECLARE_DYNAMIC_CLASS(DbcDocument);
  wxDECLARE_EVENT_TABLE();
};



}



