/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#include <wx/docmdi.h>
#include "dbcview.h"
#include "dbcviewer.h"
#include "childframe.h"

namespace dbc::viewer {

wxIMPLEMENT_DYNAMIC_CLASS(DbcView,wxView) //NOLINT

DbcDocument *DbcView::GetDocument() const {
  return wxDynamicCast(wxView::GetDocument(),DbcDocument );
}

void DbcView::OnDraw(wxDC*) {

}
bool DbcView::OnCreate(wxDocument *doc, long flags) {
  if (!wxView::OnCreate( doc,flags)) {
    return false;
  }

  auto & app = wxGetApp();
  auto* parent = wxDynamicCast(app.GetTopWindow(),wxMDIParentFrame);
  wxFrame* sub_frame = new ChildFrame(doc, this, parent,wxID_ANY,"DBC File");
  sub_frame->Show();
  return true;
}

bool DbcView::OnClose(bool del) {
  return wxView::OnClose(del);
}
void DbcView::OnUpdate(wxView *sender, wxObject *hint) {
  wxView::OnUpdate(sender, hint);
  auto* frame = GetFrame();
  if (frame != nullptr) {
    frame->Update();
  }

}

}