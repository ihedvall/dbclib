/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <wx/wx.h>
#include <wx/docmdi.h>
#include <wx/splitter.h>
#include <wx/treectrl.h>
#include <wx/listctrl.h>
#include <wx/imaglist.h>

#include "dbcdocument.h"

namespace dbc::viewer {
class ChildFrame : public wxDocMDIChildFrame {
 public:
  ChildFrame(wxDocument *doc,
            wxView *view,
            wxMDIParentFrame *parent,
            wxWindowID id,
            const wxString& title);
  ChildFrame() = default;

  void Update() override;
  void RedrawTreeList();
  void RedrawListView();
 protected:
  [[nodiscard]] DbcDocument* GetDoc();

 private:
  wxTreeCtrl* left_ = nullptr;
  wxTreeItemId selected_;

  wxListView* property_view_ = nullptr;
  wxListView* message_view_ = nullptr;
  wxListView* signal_view_ = nullptr;
  wxListView* node_view_ = nullptr;
  wxListView* group_view_ = nullptr;

  wxSplitterWindow* splitter_ = nullptr;
  wxImageList image_list_;


  void RedrawMessageList(const Network& network);
  void RedrawMessage(const Message& message, const wxTreeItemId& root);
  void RedrawSignalList(const Message& message, const wxTreeItemId& root);
  void RedrawNodeList(const Network& network);
  void RedrawSignalGroupList(const Network& network);
  void RedrawAllSignalList(const Network& network);
  void RedrawEnvVarList(const Network& network);
  void RedrawEnumList(const Network& network);

  void RedrawNetworkView(const Network& network);
  void RedrawMessageListView(const Network& network);
  void RedrawMessageView(const Message& message);
  void RedrawSignalView(const Signal& signal);
  void RedrawNodeView(const Node& signal);
  void RedrawGroupView(const SignalGroup& group);

  void RedrawSignalListView(const Network& network);
  void RedrawNodeListView(const Network& network);
  void RedrawGroupListView(const Network& network);

  void OnTreeSelected(wxTreeEvent& event);
  void OnTreeRightClick(wxTreeEvent& event);
  void OnListItemActivated(wxListEvent& event);

  void OnShowMessageData(wxCommandEvent& event);
  void OnUpdateShowMessageData(wxUpdateUIEvent& event);
  void OnShowSignalData(wxCommandEvent& event);
  void OnUpdateShowSignalData(wxUpdateUIEvent& event);
  void OnPlotSignalData(wxCommandEvent& event);
  void OnUpdatePlotSignalData(wxUpdateUIEvent& event);

  wxDECLARE_EVENT_TABLE();
};
}




