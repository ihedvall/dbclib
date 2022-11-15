/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#include <sstream>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <util/timestamp.h>
#include <util/stringutil.h>
#include "childframe.h"
#include "dbcdocument.h"
#include "windowid.h"
#include <map>

namespace {
#include "img/sub.xpm"
#include "img/tree_list.xpm"
// Bitmap index for the tree control (tree_list.bmp)
constexpr int TREE_NETWORK = 0;
constexpr int TREE_NODE = 1;
constexpr int TREE_MESSAGE = 2;
constexpr int TREE_SIGNAL = 3;
constexpr int TREE_SIGNAL_GROUP = 4;
constexpr int TREE_ENV_VAR = 5;
constexpr int TREE_ENUM = 6;
constexpr int TREE_NODE_ROOT = 7;
constexpr int TREE_MESSAGE_ROOT = 8;
constexpr int TREE_SIGNAL_ROOT = 9;
constexpr int TREE_SIGNAL_GROUP_ROOT = 10;
constexpr int TREE_ENV_VAR_ROOT = 11;
constexpr int TREE_DEFINITION_ROOT = 12;
constexpr int TREE_ENUM_ROOT = 13;

// Fake file positions which select a list of blocks
enum class ItemTreeType : int {
  NetworkItem,
  NodeListItem,
  NodeItem,
  MessageListItem,
  MessageItem,
  SignalListItem,
  SignalItem,
  SignalGroupListItem,
  SignalGroupItem,
  EnvVarItem,
  EnvVarListItem,
  DefinitionListItem,
  EnumItem,
  EnumListItem,
};


class TreeItemData : public wxTreeItemData {
 public:
  TreeItemData(ItemTreeType type, uint64_t ident, const std::string& name)
    : type_(type),
      ident_(ident),
      name_(name)
  {
  }

  [[nodiscard]] ItemTreeType Type() const { return type_; }
  [[nodiscard]] uint64_t Ident() const { return ident_; }
  [[nodiscard]] const std::string& Name() const { return name_; }
 private:
  ItemTreeType type_ = ItemTreeType::NetworkItem;
  uint64_t ident_ = 0;
  std::string name_;
};

void AddHeader(wxListView& list, long& line, const std::string& text) {
  auto index = list.InsertItem(line, wxString::From8BitData(text.c_str()));
  auto font = list.GetItemFont(index);
  font.MakeItalic();
  list.SetItemFont(index, font);
  ++line;
}

void AddBlank(wxListView& list, long& line) {
  auto index = list.InsertItem(line, "");
  ++line;
}

void AddProperty(wxListView& list, long& line,
                 const std::string& label, const std::string& text) {
  list.InsertItem(line, wxString::From8BitData(label.c_str()));
  list.SetItem(line, 1, wxString::From8BitData(text.c_str()));
  ++line;
}

void AddAttributeList(wxListView& list, long& line,
                 const std::vector<dbc::Attribute>& attribute_list) {
  std::multimap<std::string, const dbc::Attribute&, util::string::IgnoreCase>
      sorted_list;
  for (const auto& attr : attribute_list) {
    sorted_list.insert({attr.Name(), attr});
  }

  for (const auto& itr : sorted_list) {
    const auto& attribute = itr.second;
    list.InsertItem(line, wxString::From8BitData(attribute.Name().c_str()));
    list.SetItem(line, 1, wxString::From8BitData(
                              attribute.Value<std::string>().c_str()));
    list.SetItem(line, 2, attribute.ValueTypeAsString());
    if (attribute.Max() > attribute.Min()) {
      list.SetItem(line, 3, wxString::Format("%g", attribute.Min()));
      list.SetItem(line, 4, wxString::Format("%g", attribute.Max()));
    }
    std::ostringstream comment;
    const auto& enum_list = attribute.EnumList();
    for (const auto& text : enum_list) {
      if (!comment.str().empty()) {
        comment << ",";
      }
      comment << text;
    }
    list.SetItem(line, 5, wxString::From8BitData(comment.str().c_str()));
    ++line;
  }

}

wxTreeItemId FindId(const wxTreeCtrl &list, //NOLINT
                    const wxTreeItemId &root,
                    const wxTreeItemId &key) {
  for (auto item = root; item.IsOk() && key.IsOk(); item = list.GetNextSibling(item)) {
    if (item.GetID() == key.GetID()) {
      return item;
    }
    if (list.ItemHasChildren(item)) {
      wxTreeItemIdValue cookie;
      auto find = FindId(list, list.GetFirstChild(item, cookie), key);
      if (find.IsOk()) {
        return find;
      }
    }
  }
  return {};
}


} // Empty namespace

namespace dbc::viewer {

wxBEGIN_EVENT_TABLE(ChildFrame, wxDocMDIChildFrame) // NOLINT(cert-err58-cpp)
        EVT_TREE_SEL_CHANGED(kIdLeftTree,ChildFrame::OnTreeSelected)
        EVT_LIST_ITEM_ACTIVATED(kIdPropertyList, ChildFrame::OnListItemActivated)
        EVT_TREE_ITEM_RIGHT_CLICK(kIdLeftTree, ChildFrame::OnTreeRightClick)
wxEND_EVENT_TABLE()

ChildFrame::ChildFrame(wxDocument *doc,
                     wxView *view,
                     wxMDIParentFrame *parent,
                     wxWindowID id,
                     const wxString& title)
    : wxDocMDIChildFrame(doc, view, parent, id, title,
                         wxDefaultPosition, wxDefaultSize,
                         wxDEFAULT_FRAME_STYLE, wxASCII_STR(wxFrameNameStr)),
                         image_list_(16,16,false,11) {
#ifdef _WIN32
  wxIcon sub("SUB_ICON", wxBITMAP_TYPE_ICO_RESOURCE);
#else
  wxIcon sub {wxICON(sub)};
#endif
  SetIcon(sub);

  auto* main_panel = new wxPanel(this);

  splitter_ = new wxSplitterWindow(main_panel, wxID_ANY,
                                   wxDefaultPosition, wxDefaultSize,
                                   wxSP_3D | wxCLIP_CHILDREN);

  left_ = new wxTreeCtrl(splitter_,kIdLeftTree);

  property_view_ = new wxListView(splitter_, kIdPropertyList,
                                  wxDefaultPosition, wxDefaultSize,
                                  wxLC_REPORT | wxLC_SINGLE_SEL);
  property_view_->AppendColumn("Name", wxLIST_FORMAT_LEFT, 150);
  property_view_->AppendColumn("Value", wxLIST_FORMAT_LEFT, 200);
  property_view_->AppendColumn("Unit/Type", wxLIST_FORMAT_LEFT, 75);
  property_view_->AppendColumn("Min", wxLIST_FORMAT_LEFT, 50);
  property_view_->AppendColumn("Max", wxLIST_FORMAT_LEFT, 50);
  property_view_->AppendColumn("Comment", wxLIST_FORMAT_LEFT, 200);

  message_view_ = new wxListView(splitter_, kIdMessageList,
                                 wxDefaultPosition, wxDefaultSize,
                                  wxLC_REPORT | wxLC_SINGLE_SEL);
  message_view_->AppendColumn("Name", wxLIST_FORMAT_LEFT, 150);
  message_view_->AppendColumn("CAN ID", wxLIST_FORMAT_LEFT, 75);
  message_view_->AppendColumn("Ext", wxLIST_FORMAT_LEFT, 50);
  message_view_->AppendColumn("Comment", wxLIST_FORMAT_LEFT, 250);
  message_view_->AppendColumn("Bytes", wxLIST_FORMAT_LEFT, 50);
  message_view_->AppendColumn("Node", wxLIST_FORMAT_LEFT, 100);
  message_view_->Hide();

  signal_view_ = new wxListView(splitter_, kIdSignalList,
                                wxDefaultPosition, wxDefaultSize,
                                 wxLC_REPORT | wxLC_SINGLE_SEL);
  signal_view_->AppendColumn("Name", wxLIST_FORMAT_LEFT, 200);
  signal_view_->AppendColumn("Unit", wxLIST_FORMAT_LEFT, 75);
  signal_view_->AppendColumn("Comment", wxLIST_FORMAT_LEFT, 100);
  signal_view_->AppendColumn("Type", wxLIST_FORMAT_LEFT, 75);
  signal_view_->AppendColumn("Mux", wxLIST_FORMAT_LEFT, 50);
  signal_view_->AppendColumn("Start", wxLIST_FORMAT_LEFT, 50);
  signal_view_->AppendColumn("Length", wxLIST_FORMAT_LEFT, 50);
  signal_view_->Hide();

  node_view_ = new wxListView(splitter_, kIdNodeList,
                                wxDefaultPosition, wxDefaultSize,
                                wxLC_REPORT | wxLC_SINGLE_SEL);
  node_view_->AppendColumn("Name", wxLIST_FORMAT_LEFT, 150);
  node_view_->AppendColumn("Comment", wxLIST_FORMAT_LEFT, 250);
  node_view_->Hide();

  group_view_ = new wxListView(splitter_, kIdNodeList,
                              wxDefaultPosition, wxDefaultSize,
                              wxLC_REPORT | wxLC_SINGLE_SEL);
  group_view_->AppendColumn("Name", wxLIST_FORMAT_LEFT, 150);
  group_view_->AppendColumn("Message ID", wxLIST_FORMAT_LEFT, 100);
  group_view_->AppendColumn("Repetition", wxLIST_FORMAT_LEFT, 75);
  group_view_->AppendColumn("Nof", wxLIST_FORMAT_LEFT, 50);
  group_view_->AppendColumn("Signals", wxLIST_FORMAT_LEFT, 200);
  group_view_->Hide();

  splitter_->SplitVertically(left_, property_view_, 400);
#ifdef _WIN32
  wxBitmap tree_list("TREE_LIST", wxBITMAP_TYPE_BMP_RESOURCE);
#else
  wxBitmap tree_list {wxICON(tree_list)};
#endif

  image_list_.Add(tree_list);
  left_->SetImageList(&image_list_);

  auto* main_sizer = new wxBoxSizer(wxVERTICAL);
  main_sizer->Add(splitter_, 1 , wxALL | wxGROW,0);
  main_panel->SetSizerAndFit(main_sizer);
}

void ChildFrame::RedrawTreeList() {
  selected_ = left_->GetSelection();
  left_->DeleteAllItems();

  auto* doc = wxDynamicCast(GetDocument(),DbcDocument ); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
  if (doc == nullptr) {
    return;
  }
  const auto* file = doc->GetFile();
   if (file == nullptr) {
    return;
  }
  const auto* network = file->GetNetwork();
  if (network == nullptr) {
    return;
  }
  std::ostringstream root_name;
  root_name << file->Name();
  if (!network->Comment().empty()) {
    root_name << " - ";
    if (network->Comment().size() > 17) {
      root_name << network->Comment().substr(0, 17) << "...";
    } else {
      root_name << network->Comment();
    }
  }
  if (!network->Version().empty()) {
    root_name << " - ";
    if (network->Version().size() > 17) {
      root_name << network->Version().substr(0, 17) << "...";
    } else {
      root_name << network->Version();
    }
  }
  left_->AddRoot(root_name.str(), TREE_NETWORK, TREE_NETWORK,
       new TreeItemData(ItemTreeType::NetworkItem, 0, ""));
  RedrawMessageList(*network);
  RedrawAllSignalList(*network);
  RedrawNodeList(*network);
  RedrawSignalGroupList(*network);
  // RedrawEnvVarList(*network);
  // RedrawEnumList(*network);

  auto found = FindId(left_, left_->GetRootItem(), selected_);
  if (found.IsOk()) {
    left_->SelectItem(found);
    left_->EnsureVisible(found);
  }

}

void ChildFrame::RedrawMessageList(const Network& network) {
  const auto& list = network.Messages();
  if (list.empty()) {
    return;
  }
  std::multimap<std::string, const Message&> sorted_list;
  for (const auto& mess : list) {
    const Message& message = mess.second;
    sorted_list.insert({message.Name(), message});
  }
  auto root = left_->GetRootItem();
  auto list_root = left_->AppendItem(root, "CAN Messages",
                    TREE_MESSAGE_ROOT, TREE_MESSAGE_ROOT,
             new TreeItemData(ItemTreeType::MessageListItem, 0,""));
  for (const auto& itr : sorted_list) {
    RedrawMessage(itr.second, list_root);
  }

  // Message root is by default expanded
  if (!selected_.IsOk()) {
    selected_ = list_root;
    left_->SelectItem(selected_);
    left_->Expand(selected_);
  }
}

void ChildFrame::RedrawMessage(const Message& message,
                               const wxTreeItemId &root) {
  std::ostringstream label;
  label << message.Name() << " - " << message.CanId();
  auto message_root = left_->AppendItem(root,
                                 wxString::From8BitData(label.str().c_str()),
                                 TREE_MESSAGE, TREE_MESSAGE,
                                 new TreeItemData(
                                            ItemTreeType::MessageItem,
                                            message.Ident(),
                                            message.Name()));
  RedrawSignalList(message, message_root);
}

void ChildFrame::RedrawSignalList(const Message& message,
                                  const wxTreeItemId &root) {
  const auto& list = message.Signals();
  if (list.empty()) {
    return;
  }
  for (const auto& itr : list) {
    const auto& signal = itr.second;
    std::ostringstream label;
    label << signal.Name();
    if (!signal.Unit().empty()) {
      label << " [" << signal.Unit() << "]";
    }
    left_->AppendItem(root, wxString::From8BitData(label.str().c_str()),
                      TREE_SIGNAL, TREE_SIGNAL,
                      new TreeItemData(ItemTreeType::SignalItem, message.Ident(),
                                       signal.Name()));
  }
}

void ChildFrame::RedrawNodeList(const Network& network) {
  const auto& list = network.Nodes();
  if (list.empty()) {
    return;
  }
  const auto& message_list = network.Messages();
  auto root = left_->GetRootItem();
  auto list_root = left_->AppendItem(root, "CAN Nodes",
                     TREE_NODE_ROOT, TREE_NODE_ROOT,
                     new TreeItemData(ItemTreeType::NodeListItem, 0,""));
  for (const auto& itr : list) {
    const auto&  node = itr.second;
    std::ostringstream label;
    label << node.Name();
    if (!node.Comment().empty()) {
      label << " - ";
      if (node.Comment().size() > 17) {
        label << node.Comment().substr(0, 17) << "...";
      } else {
        label << node.Comment();
      }
    }
    auto node_root = left_->AppendItem(list_root,
                                wxString::From8BitData(label.str().c_str()),
                                TREE_NODE, TREE_NODE,
         new TreeItemData(ItemTreeType::NodeItem,0,node.Name()));
    for (const auto& mess : message_list) {
      const auto& message = mess.second;
      if (message.IsNodeSender(node.Name())) {
        RedrawMessage(message, node_root);
      }
    }
  }
}

void ChildFrame::RedrawSignalGroupList(const Network& network) {
  const auto& list = network.SignalGroups();
  if (list.empty()) {
    return;
  }
  std::multimap<std::string, const SignalGroup&> sorted_list;
  for (const auto& grp : list) {
    sorted_list.insert({grp.Name(), grp});
  }
  auto root = left_->GetRootItem();
  auto list_root = left_->AppendItem(root, "Signal Groups",
       TREE_SIGNAL_GROUP_ROOT, TREE_SIGNAL_GROUP_ROOT,
       new TreeItemData(ItemTreeType::SignalGroupListItem, 0,""));
  for (const auto& itr : sorted_list) {
    const auto& group = itr.second;
    std::ostringstream label;
    label << group.Name() << " - " << group.MessageId();
    auto group_root = left_->AppendItem(list_root,
      wxString::From8BitData(label.str().c_str()),
      TREE_SIGNAL_GROUP, TREE_SIGNAL_GROUP,
      new TreeItemData(ItemTreeType::SignalGroupItem,group.MessageId(),
                                       group.Name()));
    const auto* message = network.GetMessage(group.MessageId());
    if (message == nullptr) {
      continue;
    }

    const auto& signal_name_list = group.Signals();
    for (const auto& signal_name : signal_name_list) {
      const auto* signal = message->GetSignal(signal_name);
      if (signal == nullptr) {
        continue;
      }
      std::ostringstream signal_label;
      signal_label << signal->Name();
      if (!signal->Unit().empty()) {
        signal_label << " [" << signal->Unit() << "]";
      }
      left_->AppendItem(group_root,
                        wxString::From8BitData(signal_label.str().c_str()),
                        TREE_SIGNAL, TREE_SIGNAL,
                        new TreeItemData(ItemTreeType::SignalItem,
                                         message->Ident(),
                                         signal->Name()));
    }
  }
}

void ChildFrame::RedrawAllSignalList(const Network& network) {
  const auto& message_list = network.Messages();
  if (message_list.empty()) {
    return;
  }
  std::multimap<std::string, const Signal&, util::string::IgnoreCase>
      sorted_list;
  for (const auto& mess : message_list) {
    const auto& message = mess.second;
    const auto& signal_list = message.Signals();
    for (const auto& sig : signal_list) {
      const auto& signal = sig.second;
      sorted_list.insert({signal.Name(), signal});
    }
  }
  auto root = left_->GetRootItem();
  auto list_root = left_->AppendItem(root, "CAN Signals",
                       TREE_SIGNAL_ROOT, TREE_SIGNAL_ROOT,
                       new TreeItemData(ItemTreeType::SignalListItem, 0,""));
  for (const auto& itr : sorted_list) {
    const auto& signal = itr.second;
    std::ostringstream label;
    label << signal.Name();
    if (!signal.Unit().empty()) {
      label << " [" << signal.Unit() << "]";
    }
    left_->AppendItem(list_root, wxString::From8BitData(label.str().c_str()),
                                          TREE_SIGNAL, TREE_SIGNAL,
                      new TreeItemData(ItemTreeType::SignalItem,
                                       signal.MessageId(),
                                       signal.Name()));
  }
}

void ChildFrame::RedrawEnvVarList(const Network& network) {
  const auto& list = network.EnvVars();
  if (list.empty()) {
    return;
  }
  auto root = left_->GetRootItem();
  auto list_root = left_->AppendItem(root, "Environment Variables",
                                     TREE_ENV_VAR_ROOT, TREE_ENV_VAR_ROOT,
                                     new TreeItemData(
                                         ItemTreeType::EnvVarListItem, 0,""));
  for (const auto& itr : list) {
    const auto& variable = itr.second;
    std::ostringstream label;
    label << variable.Name();
    if (!variable.Unit().empty()) {
      label << " [" << variable.Unit() << "]";
    }
    left_->AppendItem(list_root, wxString::From8BitData(label.str().c_str()),
                      TREE_ENV_VAR, TREE_ENV_VAR,
                      new TreeItemData(ItemTreeType::EnvVarItem,
                                       variable.Ident(),
                                       variable.Name()));
  }
}

void ChildFrame::RedrawEnumList(const Network& network) {
  const auto& list = network.Enums();
  if (list.empty()) {
    return;
  }
  auto root = left_->GetRootItem();
  auto list_root = left_->AppendItem(root, "Enumerates",
                                     TREE_ENUM_ROOT, TREE_ENUM_ROOT,
                                     new TreeItemData(
                                         ItemTreeType::EnumListItem, 0,""));
  for (const auto& itr : list) {
    const auto& name = itr.first;
    const auto& enum_map = itr.second;
    std::ostringstream label;
    label << name;
    if (!enum_map.empty()) {
      const auto item = enum_map.cbegin();
      label << " (" << item->first <<":" << item->second << ",...)";
    }
    left_->AppendItem(list_root, wxString::From8BitData(label.str().c_str()),
                      TREE_ENUM, TREE_ENUM,
                      new TreeItemData(ItemTreeType::EnvVarItem,
                                       0,name));
  }
}

void ChildFrame::Update() {
  RedrawTreeList();
  RedrawListView();
}


void ChildFrame::OnTreeSelected(wxTreeEvent& event) {
  const auto selected = event.GetItem();
  const auto* data = dynamic_cast<TreeItemData*>(left_->GetItemData(selected));
   if (data == nullptr || left_ == nullptr) {
    return;
  }

    // Check which list
  auto* current_window = splitter_->GetWindow2();

  switch (data->Type()) {
    case ItemTreeType::MessageListItem:
      if (current_window != message_view_) {
        if (current_window != nullptr) {
          current_window->Hide();
        }
        splitter_->ReplaceWindow(current_window, message_view_);
        message_view_->Show();
      }
      break;

    case ItemTreeType::SignalListItem:
      if (current_window != signal_view_) {
        if (current_window != nullptr) {
          current_window->Hide();
        }
        splitter_->ReplaceWindow(current_window, signal_view_);
        signal_view_->Show();
      }
      break;

    case ItemTreeType::NodeListItem:
      if (current_window != node_view_) {
        if (current_window != nullptr) {
          current_window->Hide();
        }
        splitter_->ReplaceWindow(current_window, node_view_);
        node_view_->Show();
      }
      break;

    case ItemTreeType::SignalGroupListItem:
      if (current_window != group_view_) {
        if (current_window != nullptr) {
          current_window->Hide();
        }
        splitter_->ReplaceWindow(current_window, group_view_);
        group_view_->Show();
      }
      break;

    default:
      if (current_window != property_view_) {
        if (current_window != nullptr) {
          current_window->Hide();
        }
        splitter_->ReplaceWindow(current_window, property_view_);
        property_view_->Show();
      }
      break;
  }
  RedrawListView();
}

void ChildFrame::OnTreeRightClick(wxTreeEvent& event) {
  OnTreeSelected(event);
  wxMenu menu;
  menu.Append(kIdShowGroupData, "Show Group Data");
  menu.Append(kIdShowChannelData, "Show Channel Data");
  menu.AppendSeparator();
  menu.Append(kIdPlotChannelData, "Plot Channel Data");
  menu.AppendSeparator();
  menu.Append(kIdSaveAttachment, "Save Attachment File");
  menu.AppendSeparator();
  menu.Append(kIdOpenLogFile, "Open Log File");

  PopupMenu(&menu);
}

void ChildFrame::OnListItemActivated(wxListEvent& event) {
  if (splitter_->GetWindow2() != property_view_) {
    return;
  }

  auto index = event.GetIndex();
  if (index < 0) {
    return;
  }
/*
  const auto line = static_cast<size_t>(index);
  if (line >= property_list_.size()) {
    return;
  }

  auto block_id = property_list_[line].Link();
  if (block_id <= 0) {
    return;
  }

  auto* doc = wxDynamicCast(GetDocument(),MdfDocument ); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
  if (doc == nullptr) {
    return;
  }

  const auto* file = doc->GetFile();
  if (file == nullptr) {
    return;
  }

  const mdf::detail::MdfBlock* block = nullptr;
  if (file->IsMdf4()) {
    const auto* file4 = dynamic_cast<const mdf::detail::Mdf4File*>(file);
    if (file4 != nullptr) {
      block = file4->Find(block_id);
    }
  } else {
    const auto* file3 = dynamic_cast<const mdf::detail::Mdf3File*>(file);
    if (file3 != nullptr) {
      block = file3->Find(block_id);
    }
  }
  if (block == nullptr) {
    return;
  }
    // If TX block, show the text in a dialog window
  if (block->BlockType() == "TX") {
    if (file->IsMdf4()) {
      const auto* tx = dynamic_cast<const mdf::detail::Tx4Block*>(block);
      if (tx != nullptr) {
        wxMessageBox(wxString::FromUTF8(tx->Text()), "TX Block (Text)", wxICON_INFORMATION);
      }
    } else {
      const auto* tx = dynamic_cast<const mdf::detail::Tx3Block*>(block);
      if (tx != nullptr) {
        wxMessageBox(wxString::FromUTF8(tx->Text()), "TX Block (Text)", wxICON_INFORMATION);
      }
    }
    return;
  }

  if (block->BlockType() == "MD") {
    // Show the XML in a dialog window
    const auto* md = dynamic_cast<const mdf::detail::Md4Block*>(block);
    if (md != nullptr) {
      wxMessageBox(wxString::FromUTF8(md->Text()), "MD block (XML)", wxICON_INFORMATION);
    }
    return;
  }

  if (block->BlockType() == "PR") {
    // Show the XML in a dialog window
    const auto* pr3 = dynamic_cast<const mdf::detail::Pr3Block*>(block);
    if (pr3 != nullptr) {
      wxMessageBox(wxString::FromUTF8(pr3->Text()), "PR block", wxICON_INFORMATION);
    }
    return;
  }

  auto tree_item = FindId(left_,left_->GetRootItem(), block_id);
  int64_t parent_id = -1;
  int64_t grand_parent_id = -1;
  if (tree_item.IsOk()) {
    auto parent_item = left_->GetItemParent(tree_item);
    if (parent_item.IsOk()) {
      parent_id = GetBlockId(left_,parent_item);
      auto grand_parent_item = left_->GetItemParent(parent_item);
      if (grand_parent_item.IsOk()) {
        grand_parent_id = GetBlockId(left_,grand_parent_item);
      }
    }
    doc->SetSelectedBlockId(block_id, parent_id, grand_parent_id);
    left_->SelectItem(tree_item);
    left_->EnsureVisible(tree_item);
    doc->SetSelectedBlockId(block_id, parent_id, grand_parent_id);
  } else {
    doc->SetSelectedBlockId(block_id, parent_id, grand_parent_id);
  }
  */
  RedrawListView();

}

void ChildFrame::RedrawListView() {
  property_view_->DeleteAllItems();
  message_view_->DeleteAllItems();
  signal_view_->DeleteAllItems();
  node_view_->DeleteAllItems();

  if (left_ == nullptr) {
    return;
  }
  const auto selected = left_->GetSelection();
  if (!selected.IsOk()) {
    return;
  }

  const auto* data = dynamic_cast<TreeItemData*>(left_->GetItemData(selected));
  const auto* doc = GetDoc();
  const auto* file = doc != nullptr ? doc->GetFile() : nullptr;
  const auto* network = file != nullptr ? file->GetNetwork() : nullptr;
  if (network == nullptr || data == nullptr || left_ == nullptr) {
    return;
  }
  switch (data->Type()) {
    case ItemTreeType::NetworkItem:
      RedrawNetworkView(*network);
      break;

    case ItemTreeType::MessageListItem:
     RedrawMessageListView(*network);
     break;

    case ItemTreeType::MessageItem: {
      const auto* message = network->GetMessage(data->Ident());
      if (message != nullptr) {
        RedrawMessageView(*message);
      }
      break;
    }

    case ItemTreeType::SignalItem: {
      const auto* signal = network->GetSignal(
          data->Ident(), data->Name());
      if (signal != nullptr) {
        RedrawSignalView(*signal);
      }
      break;
    }

    case ItemTreeType::NodeItem: {
      const auto* node = network->GetNode(data->Name());
      if (node != nullptr) {
        RedrawNodeView(*node);
      }
      break;
    }

    case ItemTreeType::SignalGroupItem: {
      const auto* group = network->GetSignalGroup(data->Ident(), data->Name());
      if (group != nullptr) {
        RedrawGroupView(*group);
      }
      break;
    }

    case ItemTreeType::SignalListItem:
      RedrawSignalListView(*network);
      break;

    case ItemTreeType::NodeListItem:
      RedrawNodeListView(*network);
      break;

    case ItemTreeType::SignalGroupListItem:
      RedrawGroupListView(*network);
      break;

    default:
      break;
  }
}

void ChildFrame::RedrawNetworkView(const Network& network) {
  if (property_view_ == nullptr || splitter_->GetWindow2() != property_view_) {
    return;
  }
  long line = 0;
  AddHeader(*property_view_, line, "Properties:");
  AddProperty(*property_view_, line, "Version", network.Version());
  AddProperty(*property_view_, line, "Comment", network.Comment());
  AddBlank(*property_view_, line);

  AddHeader(*property_view_, line, "Attributes:");
  const auto& attribute_list = network.Attributes();
  AddAttributeList(*property_view_, line, attribute_list);
}

void ChildFrame::RedrawMessageView(const Message& message) {
  if (property_view_ == nullptr || splitter_->GetWindow2() != property_view_) {
    return;
  }
  long line = 0;
  AddHeader(*property_view_, line, "Properties:");
  AddProperty(*property_view_, line, "Message ID",
              std::to_string(message.Ident()));
  AddProperty(*property_view_, line, "CAN ID",
              std::to_string(message.CanId()));
  AddProperty(*property_view_, line, "Extended",
              message.IsExtended() ? "Yes" : "No");
  AddProperty(*property_view_, line, "Name", message.Name());
  AddProperty(*property_view_, line, "Comment", message.Comment());
  AddProperty(*property_view_, line, "Bytes",
              std::to_string(message.NofBytes()));
  std::ostringstream node;
  const auto& sender_list = message.Senders();
  for (const auto& sender : sender_list) {
    if (!node.str().empty()) {
      node << ",";
    }
    node << sender;
  }
  AddProperty(*property_view_, line, "Sender Nodes", node.str());

  AddBlank(*property_view_, line);

  AddHeader(*property_view_, line, "Attributes:");

  const auto& attribute_list = message.Attributes();
  AddAttributeList(*property_view_, line, attribute_list);
}

void ChildFrame::RedrawSignalView(const Signal& signal) {
  if (property_view_ == nullptr || splitter_->GetWindow2() != property_view_) {
    return;
  }

  long line = 0;
  AddHeader(*property_view_, line, "Properties:");
  AddProperty(*property_view_, line, "Name", signal.Name());
  AddProperty(*property_view_, line, "Unit", signal.Unit());
  AddProperty(*property_view_, line, "Comment", signal.Comment());
  AddProperty(*property_view_, line, "Data Type", signal.DataTypeAsString());
  AddProperty(*property_view_, line, "Message ID",
              std::to_string(signal.MessageId()));
  AddProperty(*property_view_, line, "Multiplex", signal.MuxAsString());
  AddProperty(*property_view_, line, "Bit Start",
              std::to_string(signal.BitStart()));
  AddProperty(*property_view_, line, "Bit Length",
              std::to_string(signal.BitLength()));
  AddProperty(*property_view_, line, "Endian",
              signal.LittleEndian() ? "Little Endian" : "Big Endian");
  {
    std::ostringstream scale;
    scale << signal.Scale();
    AddProperty(*property_view_, line, "Scale", scale.str());
  }
  {
    std::ostringstream offset;
    offset << signal.Offset();
    AddProperty(*property_view_, line, "Offset", offset.str());
  }
  if (signal.Max() > signal.Min()) {
    std::ostringstream min;
    min << signal.Min();
    AddProperty(*property_view_, line, "Min", min.str());

    std::ostringstream max;
    max << signal.Max();
    AddProperty(*property_view_, line, "Max", max.str());
  }

  const auto& enum_list = signal.EnumList();
  if (!enum_list.empty()) {
    std::ostringstream enum_text;
    for (const auto& enum_obj : enum_list) {
      if (!enum_text.str().empty()) {
        enum_text << " ";
      }
      enum_text << enum_obj.first << ":" << enum_obj.second;
    }
    AddProperty(*property_view_, line, "Enumerate", enum_text.str());
  }

  const auto& receiver_list = signal.Receivers();
  if (!receiver_list.empty()) {
    std::ostringstream receiver_text;
    for (const auto& receiver : receiver_list) {
      if (!receiver_text.str().empty()) {
        receiver_text << ",";
      }
      receiver_text << receiver;
    }
    AddProperty(*property_view_, line, "Receiver", receiver_text.str());
  }

  AddBlank(*property_view_, line);
  AddHeader(*property_view_, line, "Attributes:");
  const auto& attribute_list = signal.Attributes();
  AddAttributeList(*property_view_, line, attribute_list);
}

void ChildFrame::RedrawNodeView(const Node& node) {
  if (property_view_ == nullptr || splitter_->GetWindow2() != property_view_) {
    return;
  }

  long line = 0;
  AddHeader(*property_view_, line, "Properties:");
  AddProperty(*property_view_, line, "Name", node.Name());
  AddProperty(*property_view_, line, "Comment", node.Comment());

  AddBlank(*property_view_, line);
  AddHeader(*property_view_, line, "Attributes:");
  const auto& attribute_list = node.Attributes();
  AddAttributeList(*property_view_, line, attribute_list);
}

void ChildFrame::RedrawGroupView(const SignalGroup& group) {
  if (property_view_ == nullptr || splitter_->GetWindow2() != property_view_) {
    return;
  }

  long line = 0;
  AddHeader(*property_view_, line, "Properties:");
  AddProperty(*property_view_, line, "Name", group.Name());
  AddProperty(*property_view_, line, "Message ID",
              std::to_string(group.MessageId()));
  AddProperty(*property_view_, line, "Repetition",
                          std::to_string(group.Repetition()));

  AddBlank(*property_view_, line);
  AddHeader(*property_view_, line, "Signals:");
  const auto& signal_list = group.Signals();
  for (const auto& signal : signal_list) {
    AddProperty(*property_view_, line, signal,"");
  }
}

void ChildFrame::RedrawMessageListView(const Network& network) {
  if (message_view_ == nullptr || splitter_->GetWindow2() != message_view_) {
    return;
  }
  long line = 0;
  const auto& list = network.Messages();
  std::multimap<std::string, const Message&, util::string::IgnoreCase>
      sorted_list;
  for (const auto& mess : list) {
    const auto& message = mess.second;
    sorted_list.insert({message.Name(),message});
  }
  for (const auto& itr : sorted_list) {
    const auto& message = itr.second;
    message_view_->InsertItem(line,
                              wxString::From8BitData(message.Name().c_str()));
    message_view_->SetItem(line, 1, std::to_string(message.CanId()));
    message_view_->SetItem(line, 2, message.IsExtended() ? "Yes" : "");
    message_view_->SetItem(line, 3,
                           wxString::From8BitData(message.Comment().c_str()));
    message_view_->SetItem(line, 4, std::to_string(message.NofBytes()));
    message_view_->SetItem(line, 5,
                           wxString::From8BitData(message.Node().c_str()));
    ++line;
  }
}

void ChildFrame::RedrawSignalListView(const Network& network) {
  if (signal_view_ == nullptr || splitter_->GetWindow2() != signal_view_) {
    return;
  }
  std::multimap<std::string, const Signal&, util::string::IgnoreCase>
      sorted_list;

  const auto& message_list = network.Messages();
  for (const auto& mess : message_list) {
    const auto& message = mess.second;
    const auto& signal_list = message.Signals();
    for (const auto& sig : signal_list) {
      const auto& signal = sig.second;
      sorted_list.insert({signal.Name(), signal});
    }
  }
  long line = 0;
  for (const auto& itr : sorted_list) {
    const auto& signal = itr.second;
    signal_view_->InsertItem(line,
                             wxString::From8BitData(signal.Name().c_str()));
    signal_view_->SetItem(line, 1,
                          wxString::From8BitData(signal.Unit().c_str()));
    signal_view_->SetItem(line, 2,
                          wxString::From8BitData(signal.Comment().c_str()));
    signal_view_->SetItem(line, 3, signal.DataTypeAsString());
    signal_view_->SetItem(line, 4, signal.Mux() == MuxType::NotMultiplexed ?
                                    "" : "Yes");
    signal_view_->SetItem(line, 5, std::to_string(signal.BitStart()));
    signal_view_->SetItem(line, 6, std::to_string(signal.BitLength()));
    ++line;
  }
}

void ChildFrame::RedrawNodeListView(const Network& network) {
  if (node_view_ == nullptr || splitter_->GetWindow2() != node_view_) {
    return;
  }
  long line = 0;
  const auto& list = network.Nodes();
  for (const auto& itr : list) {
    const auto& node = itr.second;
    node_view_->InsertItem(line, wxString::From8BitData(node.Name().c_str()));
    node_view_->SetItem(line, 1,
                        wxString::From8BitData(node.Comment().c_str()));
    ++line;
  }
}

void ChildFrame::RedrawGroupListView(const Network& network) {
  if (group_view_ == nullptr || splitter_->GetWindow2() != group_view_) {
    return;
  }
  const auto& list = network.SignalGroups();
  std::multimap<std::string, const SignalGroup&, util::string::IgnoreCase>
      sorted_list;
  for (const auto& grp : list) {
    sorted_list.insert({grp.Name(), grp});
  }

  long line = 0;
  for (const auto& itr : sorted_list) {
    const auto& group = itr.second;
    group_view_->InsertItem(line, wxString::From8BitData(group.Name().c_str()));
    group_view_->SetItem(line, 1, std::to_string(group.MessageId()));
    group_view_->SetItem(line, 2, std::to_string(group.Repetition()));

    const auto& signal_list = group.Signals();
    group_view_->SetItem(line, 3, std::to_string(signal_list.size()));

    std::ostringstream temp;
    for (const auto& signal : signal_list) {
      if (!temp.str().empty()) {
        temp << ",";
      }
      temp << signal;
    }
    group_view_->SetItem(line, 4, wxString::From8BitData(temp.str().c_str()));
    ++line;
  }
}

DbcDocument *ChildFrame::GetDoc() {
  return wxDynamicCast(GetDocument(),DbcDocument ); // NOLINT
}

}



