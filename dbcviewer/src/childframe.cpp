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
#include <dbc/signalobserver.h>
#include "signalobserverframe.h"
#include <boost/filesystem.hpp>
#include "dbcviewer.h"
#include <util/csvwriter.h>
#include <util/logstream.h>
#include <boost/process.hpp>
#if (_MSC_VER)
#include <boost/process/windows.hpp>
#endif
using namespace util::log;

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

constexpr uint64_t kMaxExtendedId = 0x1FFFFFFFULL; ///< Max Extended CAN ID

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
  [[nodiscard]] bool operator == (const TreeItemData& data) const {
    return Type() == data.Type() &&
           (Ident() & kMaxExtendedId) == (data.Ident() & kMaxExtendedId) &&
           Name() == data.Name();
  }
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

wxTreeItemId FindTreeItem(const wxTreeCtrl &list, //NOLINT
                      const wxTreeItemId &root,
                      const TreeItemData &key) {
  for (auto item = root; item.IsOk() ; item = list.GetNextSibling(item)) {
    auto* item_data = dynamic_cast<TreeItemData*>(list.GetItemData(item));
    if (item_data != nullptr && *item_data == key) {
      return item;
    }
    if (list.ItemHasChildren(item)) {
      wxTreeItemIdValue cookie;
      auto find = FindTreeItem(list, list.GetFirstChild(item, cookie), key);
      if (find.IsOk()) {
        return find;
      }
    }
  }
  return {};
}
/**
 * Creates a CSV file using sample observers as input.
 *
 * The CSV file is created in the applications temporary directory and the file name is unique.
 * Note that if the observer list only have one channel, the file will add the samples as first column.
 * The same applies if the first channel not is a master channel.
 * @param list Sample observer list containing samples.
 * @return Full path to the created file or an empty string if the function fails.
 */
 std::string CreateCsvFile(const dbc::SignalObserverList& list) {
  if (list.empty()) {
    LOG_ERROR() << "No observers in the list.";
    return "";
  }

  const auto& app = wxGetApp();
  std::string csv_file;
  try {
    std::filesystem::path temp_file(app.GetMyTempDir());
    const auto unique  = boost::filesystem::unique_path();
    temp_file.append(unique.string());
    temp_file.replace_extension(".csv");
    csv_file = temp_file.generic_string();
  } catch (const std::exception& error) {
    LOG_ERROR() << "Failed to create the CSV file. Error: " << error.what();
  }

  util::plot::CsvWriter csv(csv_file);
  csv.AddColumnHeader("Time","s");
  const auto& observer = list[0];
  if (!observer) {
      return csv_file;
  }
  const auto& signal = observer->GetSignal();
  csv.AddColumnHeader(signal.Name(),signal.Unit());
  csv.AddRow();

  // Add the samples
  uint64_t base_time = 0;
  for (size_t sample = 0; sample < observer->NofSamples(); ++sample) {
    const auto index = observer->SampleToIndex(sample);
    uint64_t sample_time = 0;
    std::string value;
    const bool valid  = signal.EnumList().empty() ?
               observer->EngValue(index, sample_time, value)
               : observer->ChannelValue(index, sample_time, value);
    if (sample == 0) {
      base_time = sample_time;
    }
    const auto rel_time = sample_time - base_time;
    auto time = static_cast<double>(rel_time);
    time /= 1'000'000'000;

    csv.AddColumnValue(time);
    csv.AddColumnValue(valid ? value : "");
    csv.AddRow();
  }
  return csv_file;
}

std::string CreateGnuPlotFile(const dbc::SignalObserverList& list,
                              const std::string& csv_file,
                              const std::string& title) {
  if (list.empty() || csv_file.empty()) {
    LOG_ERROR() << "No CSV file or observer list is empty.";
    return "";
  }
  const auto& observer = list[0];
  if (!observer) {
    return "";
  }
  const auto& signal = observer->GetSignal();
  std::string gp_file;
  try {
    std::filesystem::path p(csv_file);
    p.replace_extension(".gp");
    gp_file = p.generic_string();
  } catch(const std::exception& error) {
    LOG_ERROR() << "Failed to create gnuplot file. CSV File: " << csv_file;
  }
  std::FILE* file = fopen(gp_file.c_str(), "wt");
  std::ostringstream x_label;
  std::ostringstream y_label;
  x_label << "Time [s]";
  y_label << signal.Name();
  if (!signal.Unit().empty()) {
    y_label << " [" << signal.Unit() << "]";
  }

  if (file != nullptr) {
    fprintf(file, "set terminal wxt noenhanced title \"%s\" size 1200, 1000\n",
            title.c_str());
    fprintf(file, "set datafile separator comma\n");
    fprintf(file, "set key outside autotitle columnheader\n");
    fprintf(file, "set xlabel \"%s\"\n", x_label.str().c_str());
    fprintf(file, "set ylabel \"%s\"\n", y_label.str().c_str());
    fprintf(file, "set autoscale\n");
    fprintf(file, "plot \"%s\" using 1:2 with lines\n",csv_file.c_str());
    fprintf(file, "exit\n");
    fclose(file);
  }
  return gp_file;
}


} // Empty namespace

namespace dbc::viewer {

wxBEGIN_EVENT_TABLE(ChildFrame, wxDocMDIChildFrame) // NOLINT(cert-err58-cpp)
  EVT_TREE_SEL_CHANGED(kIdLeftTree,ChildFrame::OnTreeSelected)
  EVT_LIST_ITEM_ACTIVATED(kIdMessageList, ChildFrame::OnListItemActivated)
  EVT_LIST_ITEM_ACTIVATED(kIdSignalList, ChildFrame::OnListItemActivated)
  EVT_LIST_ITEM_ACTIVATED(kIdNodeList, ChildFrame::OnListItemActivated)
  EVT_LIST_ITEM_ACTIVATED(kIdSignalGroupList, ChildFrame::OnListItemActivated)
  EVT_TREE_ITEM_RIGHT_CLICK(kIdLeftTree, ChildFrame::OnTreeRightClick)
  EVT_UPDATE_UI(kIdShowMessageData, ChildFrame::OnUpdateShowMessageData)
  EVT_MENU(kIdShowMessageData, ChildFrame::OnShowMessageData)
  EVT_UPDATE_UI(kIdShowSignalData, ChildFrame::OnUpdateShowSignalData)
  EVT_MENU(kIdShowSignalData, ChildFrame::OnShowSignalData)
  EVT_UPDATE_UI(kIdPlotSignalData, ChildFrame::OnUpdatePlotSignalData)
  EVT_MENU(kIdPlotSignalData, ChildFrame::OnPlotSignalData)
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
  message_view_->AppendColumn("PGN", wxLIST_FORMAT_LEFT, 75);
  message_view_->AppendColumn("Samples", wxLIST_FORMAT_LEFT, 75);
  message_view_->AppendColumn("Comment", wxLIST_FORMAT_LEFT, 250);
  message_view_->AppendColumn("Bytes", wxLIST_FORMAT_LEFT, 50);
  message_view_->AppendColumn("Node", wxLIST_FORMAT_LEFT, 100);

  message_view_->Hide();

  signal_view_ = new wxListView(splitter_, kIdSignalList,
                                wxDefaultPosition, wxDefaultSize,
                                 wxLC_REPORT | wxLC_SINGLE_SEL);
  signal_view_->AppendColumn("Name", wxLIST_FORMAT_LEFT, 200);
  signal_view_->AppendColumn("Value (Last)", wxLIST_FORMAT_LEFT, 100);
  signal_view_->AppendColumn("Unit", wxLIST_FORMAT_LEFT, 75);
  signal_view_->AppendColumn("Samples", wxLIST_FORMAT_LEFT, 75);
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
  node_view_->AppendColumn("Source", wxLIST_FORMAT_LEFT, 75);
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
  left_->SelectItem(selected);
  RedrawListView();
}

void ChildFrame::OnTreeRightClick(wxTreeEvent& event) {
  OnTreeSelected(event);
  wxMenu menu;
  menu.Append(kIdShowMessageData, "Show Message Data");
  menu.Append(kIdShowSignalData, "Show Signal Data");
  menu.AppendSeparator();
  menu.Append(kIdPlotSignalData, "Plot Signal Data");
  menu.AppendSeparator();
  menu.Append(kIdImportMessageFile, "Import CAN Message File");
  menu.AppendSeparator();
  menu.Append(kIdOpenLogFile, "Open Log File");

  PopupMenu(&menu);
}

void ChildFrame::OnListItemActivated(wxListEvent& event) {
  const auto* doc = GetDoc();
  const auto index = event.GetIndex();
  const auto* file = doc != nullptr ? doc->GetFile() : nullptr;
  const auto* network = file != nullptr ? file->GetNetwork() : nullptr;
  if (index < 0 || network == nullptr) {
    return;
  }

  TreeItemData find_item(ItemTreeType::NetworkItem, 0, "");
  auto* current_window = splitter_->GetWindow2();
  if (current_window == message_view_) {
    // Jump to message
    const auto ident = message_view_->GetItemText(index, 1).ToStdString();
    const auto can_id = std::stoull(ident);
    const auto* message = network->GetMessageByCanId(can_id);
    if (message != nullptr) {
      find_item = TreeItemData(ItemTreeType::MessageItem,
                               message->Ident(), message->Name());
    }
  } else if (current_window == signal_view_) {
    // Jump to signal in tree
    const auto name = signal_view_->GetItemText(index, 0).ToStdString();
    const auto* signal = network->GetSignalByName(name);
    if (signal != nullptr) {
      find_item = TreeItemData(ItemTreeType::SignalItem,
                               signal->MessageId(), signal->Name());
    }
  } else if (current_window == node_view_) {
    // Jump to node in tree
    const auto name = node_view_->GetItemText(index, 0).ToStdString();
    const auto* node = network->GetNode(name);
    if (node != nullptr) {
      find_item = TreeItemData(ItemTreeType::NodeItem,
                               0, node->Name());
    }
  } else if (current_window == group_view_) {
    // Jump to group in tree
    const auto name = group_view_->GetItemText(index, 0).ToStdString();
    const auto* group = network->GetSignalGroupByName(name);
    if (group != nullptr) {
      find_item = TreeItemData(ItemTreeType::SignalGroupItem,
                               group->MessageId(), group->Name());
    }
  }

  const auto find = FindTreeItem(*left_, left_->GetRootItem(), find_item);
  if (!find.IsOk()) {
    return;
  }
  left_->SelectItem(find);
  left_->Expand(find);
  left_->EnsureVisible(find);
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
  AddProperty(*property_view_, line, "Name", network.Name());
  AddProperty(*property_view_, line, "Filename", network.Filename());
  AddProperty(*property_view_, line, "Protocol", network.ProtocolAsString());
  AddProperty(*property_view_, line, "Bus", network.BusAsString());
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
  if (message.IsJ1939()) {
    AddProperty(*property_view_, line, "PGN (J1939)",
                std::to_string(message.Pgn()));
    AddProperty(*property_view_, line, "Priority (J1939)",
                std::to_string(message.Priority()));
    AddProperty(*property_view_, line, "Source (J1939)",
                std::to_string(message.Source()));
  }
  AddProperty(*property_view_, line, "Extended",
              message.IsExtended() ? "Yes" : "No");
  AddProperty(*property_view_, line, "Name", message.Name());
  AddProperty(*property_view_, line, "Comment", message.Comment());
  AddProperty(*property_view_, line, "Bytes",
              std::to_string(message.NofBytes()));
  AddProperty(*property_view_, line, "Samples",
              std::to_string(message.SampleCounter()));

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

  std::string channel_value;
  signal.ChannelValue(channel_value);
  AddProperty(*property_view_, line, "Channel Value",
              signal.SampleCounter() > 0 ? channel_value : std::string());

  std::string eng_value;
  signal.EngValue(eng_value);
  AddProperty(*property_view_, line, "Eng Value",
              signal.SampleCounter() > 0 ? eng_value : std::string());
  AddProperty(*property_view_, line, "Samples",
              std::to_string(signal.SampleCounter()));
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
    message_view_->SetItem(line, 2, network.J1939() ?
                            std::to_string(message.Pgn()) : std::string());
    message_view_->SetItem(line, 3, message.SampleCounter() > 0 ?
                  std::to_string(message.SampleCounter()) : std::string());
    message_view_->SetItem(line, 4,
                           wxString::From8BitData(message.Comment().c_str()));
    message_view_->SetItem(line, 5, std::to_string(message.NofBytes()));
    message_view_->SetItem(line, 6,
                           wxString::From8BitData(message.NodeName().c_str()));
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
    std::string value;
    signal.EngValue(value);
    signal_view_->SetItem(line, 1, signal.SampleCounter() > 0 ?
        wxString::From8BitData(value.c_str()) : std::string());
    signal_view_->SetItem(line, 2,
        wxString::From8BitData(signal.Unit().c_str()));
    signal_view_->SetItem(line, 3, signal.SampleCounter() > 0 ?
        std::to_string(signal.SampleCounter()) : std::string() );
    signal_view_->SetItem(line, 4,
                          wxString::From8BitData(signal.Comment().c_str()));
    signal_view_->SetItem(line, 5, signal.DataTypeAsString());
    signal_view_->SetItem(line, 6, signal.Mux() == MuxType::NotMultiplexed ?
                                    "" : "Yes");
    signal_view_->SetItem(line, 7, std::to_string(signal.BitStart()));
    signal_view_->SetItem(line, 8, std::to_string(signal.BitLength()));
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

    node_view_->SetItem(line, 1, node.Source() < 254 ?
                        std::to_string(static_cast<int>(node.Source()))
                        : std::string() );
    node_view_->SetItem(line, 2,
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

void ChildFrame::OnShowMessageData(wxCommandEvent &event) {
  wxBusyCursor wait;
  auto* doc = GetDoc();
  auto* file = doc != nullptr ? doc->GetFile() : nullptr;
  const auto* network = file != nullptr ? file->GetNetwork() : nullptr;
  if (network == nullptr || left_ == nullptr) {
    return;
  }
  const auto selected = left_->GetSelection();
  if (!selected.IsOk()) {
    return;
  }

  const auto* data = dynamic_cast<TreeItemData*>(left_->GetItemData(selected));
  if (data == nullptr ) {
    return;
  }
  const Message *message = network->GetMessage(data->Ident());
  if (message == nullptr) {
    return;
  }

  std::ostringstream title;
  title << message->CanId();

  if (!message->Name().empty()) {
    title << " - " << message->Name();
  }
  if (!message->Comment().empty()) {
    title << " - " << message->Comment();
  }

  title << "/" << file->Name();

  auto observer_list = std::make_unique<SignalObserverList>();
  const auto& signal_list = message->Signals();
  for (const auto& itr : signal_list) {
    const auto& signal = itr.second;
    auto observer = std::make_unique<SignalObserver>(signal);
    observer_list->push_back(std::move(observer));
  }
  file->ReparseMessageList();

  auto data_frame = new SignalObserverFrame(observer_list, this, wxID_ANY,
                                            title.str());
  data_frame->BaseTime(file->BaseTime());
  data_frame->SetNetwork(network);
  data_frame->Show();
}

void ChildFrame::OnUpdateShowMessageData(wxUpdateUIEvent &event) {
  event.Enable(false);
  const auto* doc = GetDoc();
  const auto* file = doc != nullptr ? doc->GetFile() : nullptr;
  const auto* network = file != nullptr ? file->GetNetwork() : nullptr;
  if (network == nullptr || left_ == nullptr) {
    return;
  }
  const auto selected = left_->GetSelection();
  if (!selected.IsOk()) {
    return;
  }

  const auto* data = dynamic_cast<TreeItemData*>(left_->GetItemData(selected));
  if (data == nullptr ) {
    return;
  }
  const Message *message = nullptr;
  if (data->Type() == ItemTreeType::MessageItem ||
      data->Type() == ItemTreeType::SignalItem ||
      data->Type() == ItemTreeType::SignalGroupItem) {
    message = network->GetMessage(data->Ident());
  }
  if (message == nullptr) {
    return;
  }
  event.Enable(message->SampleCounter() > 0);
}

void ChildFrame::OnShowSignalData(wxCommandEvent &event) {
  wxBusyCursor wait;
  auto* doc = GetDoc();
  auto* file = doc != nullptr ? doc->GetFile() : nullptr;
  const auto* network = file != nullptr ? file->GetNetwork() : nullptr;
  if (network == nullptr || left_ == nullptr) {
    return;
  }
  const auto selected = left_->GetSelection();
  if (!selected.IsOk()) {
    return;
  }

  const auto* data = dynamic_cast<TreeItemData*>(left_->GetItemData(selected));
  if (data == nullptr ) {
    return;
  }
  const Signal *signal = network->GetSignal(data->Ident(), data->Name());
  if (signal == nullptr) {
    return;
  }
  std::ostringstream title;
  title << signal->Name();
  if (!signal->Comment().empty()) {
    title << " - " << signal->Comment();
  }
  title << "/" << file->Name();

  auto observer_list = std::make_unique<SignalObserverList>();
  auto observer = std::make_unique<SignalObserver>(*signal);
  observer_list->push_back(std::move(observer));

  file->ReparseMessageList();

  auto data_frame = new SignalObserverFrame(observer_list, this, wxID_ANY,
                                            title.str());
  data_frame->BaseTime(file->BaseTime());
  data_frame->SetNetwork(network);
  data_frame->Show();
}

void ChildFrame::OnUpdateShowSignalData(wxUpdateUIEvent &event) {

  event.Enable(false);
  const auto* doc = GetDoc();
  const auto* file = doc != nullptr ? doc->GetFile() : nullptr;
  const auto* network = file != nullptr ? file->GetNetwork() : nullptr;
  if (network == nullptr || left_ == nullptr) {
    return;
  }
  const auto selected = left_->GetSelection();
  if (!selected.IsOk()) {
    return;
  }

  const auto* data = dynamic_cast<TreeItemData*>(left_->GetItemData(selected));
  if (data == nullptr ) {
    return;
  }
  const Signal *signal = nullptr;
  if (data->Type() == ItemTreeType::SignalItem) {
    signal = network->GetSignal(data->Ident(), data->Name());
  }
  if (signal == nullptr) {
    return;
  }
  event.Enable(signal->SampleCounter() > 0);
}

void ChildFrame::OnPlotSignalData(wxCommandEvent &event) {
  wxBusyCursor wait;
  auto* doc = GetDoc();
  auto* file = doc != nullptr ? doc->GetFile() : nullptr;
  const auto* network = file != nullptr ? file->GetNetwork() : nullptr;
  if (network == nullptr || left_ == nullptr) {
    return;
  }
  const auto selected = left_->GetSelection();
  if (!selected.IsOk()) {
    return;
  }

  const auto* data = dynamic_cast<TreeItemData*>(left_->GetItemData(selected));
  if (data == nullptr ) {
    return;
  }
  const Signal *signal = network->GetSignal(data->Ident(), data->Name());
  if (signal == nullptr) {
    return;
  }

  std::ostringstream title;
  title << signal->Name();
  if (!signal->Comment().empty()) {
    title << " - " << signal->Comment();
  }
  title << "/" << file->Name();

  if (!title.str().empty()) {
    title << "/";
  }
  auto& app = wxGetApp();
  // Create the observer list
  auto observer_list = std::make_unique<SignalObserverList>();
  auto observer = std::make_unique<SignalObserver>(*signal);
  observer_list->push_back(std::move(observer));
  file->ReparseMessageList();
  const auto* obs = observer_list->front().get();
  if (obs == nullptr || obs->NofValidSamples() < 2) {
    wxMessageBox("There is not enough valid samples to plot");
    return;
  }
  // Produce a CSV file with the data for later use with the gnuplot script
  auto csv_file = CreateCsvFile(*observer_list);
  auto gp_file = CreateGnuPlotFile(*observer_list, csv_file, title.str());
  if (csv_file.empty() || gp_file.empty()) {
    wxMessageBox("Failed to create CSV or GP files.\nMore information in log file.");
    return;
  }
#if (_MSC_VER)
  boost::process::spawn(app.GnuPlot(), "--persist", gp_file, boost::process::windows::hide);
#else
  // TODO: how to hide?
  boost::process::spawn(app.GnuPlot(), "--persist", gp_file);
#endif

}

void ChildFrame::OnUpdatePlotSignalData(wxUpdateUIEvent &event) {

    event.Enable(false);
    const auto* doc = GetDoc();
    const auto* file = doc != nullptr ? doc->GetFile() : nullptr;
    const auto* network = file != nullptr ? file->GetNetwork() : nullptr;
    if (network == nullptr || left_ == nullptr) {
      return;
    }
    const auto selected = left_->GetSelection();
    if (!selected.IsOk()) {
      return;
    }

    const auto* data = dynamic_cast<TreeItemData*>(left_->GetItemData(selected));
    if (data == nullptr ) {
      return;
    }
    const Signal *signal = nullptr;
    if (data->Type() == ItemTreeType::SignalItem) {
      signal = network->GetSignal(data->Ident(), data->Name());
    }
    if (signal == nullptr || signal->BitLength() > sizeof(uint64_t) * 8) {
      // Cannot plot text values but enumerate is OK
      return;
    }
    event.Enable(signal->SampleCounter() > 0);
}

}



