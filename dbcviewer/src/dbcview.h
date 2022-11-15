/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <wx/docview.h>
#include "dbcdocument.h"

namespace dbc::viewer {
 class DbcView : public wxView  {
  public:
   DbcView() = default;
   DbcDocument* GetDocument() const;

   bool OnCreate(wxDocument* doc, long flags) override;
   bool OnClose(bool del) override;

   void OnDraw(wxDC *dc) override;
   void OnUpdate(wxView *sender, wxObject *hint = nullptr) override;

  private:

   wxDECLARE_DYNAMIC_CLASS(DbcView);

 };
}





