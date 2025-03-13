/*
 * Copyright 2021 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#include <sstream>

#include <filesystem>

#include <wx/msgdlg.h>

#include <boost/filesystem.hpp>

#include "childframe.h"
#include "dbcdocument.h"
#include "dbcviewer.h"
#include "mdf/ichannel.h"
#include "mdf/ichannelgroup.h"
#include "mdf/idatagroup.h"
#include "mdf/mdfreader.h"
#include "protocoldialog.h"
#include "signalobserverframe.h"
#include "util/csvwriter.h"
#include "util/logstream.h"
#include "windowid.h"

using namespace util::log;
using namespace dbc;


namespace {
} // end namespace

namespace dbc::viewer {
wxIMPLEMENT_DYNAMIC_CLASS(DbcDocument, wxDocument) // NOLINT

wxBEGIN_EVENT_TABLE(DbcDocument, wxDocument) // NOLINT
  EVT_UPDATE_UI(kIdImportMessageFile, DbcDocument::OnUpdateImportCanMessageFile)
  EVT_MENU(kIdImportMessageFile, DbcDocument::OnImportCanMessageFile)
wxEND_EVENT_TABLE()

bool DbcDocument::OnOpenDocument(const wxString &filename) {
  wxBusyCursor wait;
  dbc_file_ = std::make_unique<DbcFile>();
  dbc_file_->Filename(filename.ToStdString());
  const bool parse = dbc_file_->ParseFile();

  if (!parse) {
    const auto error = dbc_file_->LastError();
    std::ostringstream err;
    err << "Failed to  parse the file. File: " << dbc_file_->Name() << std::endl;
    err << "Error: " << error << std::endl;
    err << "Path: " << dbc_file_->Filename() << std::endl;
    wxMessageBox(wxString(err.str()), wxString("Error Parsing File"),
                 wxOK | wxCENTRE | wxICON_ERROR);
  }
  return parse && wxDocument::OnOpenDocument(filename);
}

void DbcDocument::OnImportCanMessageFile(wxCommandEvent &event) {
  auto* network = dbc_file_ ? dbc_file_->GetNetwork() : nullptr;
  auto* window = wxDynamicCast( GetDocumentWindow(), ChildFrame);
  if (network == nullptr || window == nullptr) {
    return;
  }

  wxFileDialog open_dialog(window,
                           "Open CAN Message File", "",
                           "", "MDF Files (*.mf4)|*.mf4|All Files (*.*)|*.*",
                           wxFD_OPEN | wxFD_FILE_MUST_EXIST);
  if (const auto ret = open_dialog.ShowModal();
      ret != wxID_OK) {
    return;
  }

  if (const auto* protocol_type = network->GetAttribute("ProtocolType");
      protocol_type == nullptr) {
    ProtocolDialog protocol_dialog(wxGetActiveWindow());
    const auto ret_protocol = protocol_dialog.ShowModal();
    if (ret_protocol != wxID_OK) {
      return;
    }
    network->Protocol(protocol_dialog.Protocol());
    network->Bus(protocol_dialog.Bus());
    window->RedrawListView();
  }

  wxBusyCursor wait;

  // Read information about the file
  const auto filename = open_dialog.GetPath().ToStdString();
  mdf::MdfReader reader(filename);
  const auto file_ok = reader.IsOk();
  if (!file_ok) {
    LOG_ERROR() << "The file is not a MDF file. File: "
                << reader.ShortName();
  }
  const auto read_info = reader.ReadEverythingButData();
  if (!read_info) {
    LOG_ERROR() << "Failed to read file information. File: "
                << reader.ShortName();
  }
  const auto* header = reader.GetHeader();
  if (header == nullptr) {
    LOG_ERROR() << "No header block in file. File: "
                << reader.ShortName();
  }
  auto* data_group = header->LastDataGroup();
  if (data_group == nullptr) {
    LOG_ERROR() << "No data in file. File: "
                << reader.ShortName();
  }

  if (!file_ok || !read_info || header == nullptr || data_group == nullptr) {
    wxMessageBox(
        "Failed to read information from the file.\nMore information in the log file.",
        "File Read Error", wxOK | wxCENTRE | wxICON_ERROR);
    return;
  }

  // Search for the master channel name (assuming relative time channel)
  mdf::IChannelGroup *selected_group = nullptr;
  mdf::IChannel *master_channel = nullptr;
  for (mdf::IChannelGroup* mdf_group : data_group->ChannelGroups()) {
    if (mdf_group == nullptr || mdf_group->NofSamples() == 0 ) {
      continue;
    }
    if (selected_group == nullptr ||
               mdf_group->NofSamples() > selected_group->NofSamples()) {
      selected_group = mdf_group;
      master_channel = nullptr;
    } else {
      continue;
    }

    for (mdf::IChannel* mdf_channel : mdf_group->Channels()) {
      if (mdf_channel == nullptr) {
        continue;
      }
      if (mdf_channel->Type() == mdf::ChannelType::Master &&
          mdf_channel->Sync() == mdf::ChannelSyncType::Time) {
        master_channel = mdf_channel;
      }
    }
  }

  const auto base_time = header->StartTime(); // Absolute time reference

  mdf::ChannelObserverPtr rel_time;
  mdf::ChannelObserverPtr can_id;
  mdf::ChannelObserverPtr data_bytes;
  if (selected_group != nullptr && master_channel != nullptr) {
    rel_time = mdf::CreateChannelObserver(*data_group, *selected_group, *master_channel);
    if (auto* can_id_channel = selected_group->GetChannel("CAN_DataFrame.ID");
        can_id_channel != nullptr) {
      can_id = mdf::CreateChannelObserver(*data_group, *selected_group,*can_id_channel);
    }
    if (auto* data_bytes_channel = selected_group->GetChannel("CAN_DataFrame.DataBytes");
        data_bytes_channel != nullptr) {
      data_bytes = mdf::CreateChannelObserver(*data_group, *selected_group,
                                              *data_bytes_channel);
    }
  }

  if (!rel_time) {
    LOG_ERROR() << "Master time channel is missing. File: " << reader.ShortName();
  }
  if (!can_id) {
    LOG_ERROR() << "CAN ID channel 'CAN_DataFrame.ID' is missing. File: "
                << reader.ShortName();
  }
/*
  auto data_length = mdf::CreateChannelObserver(*data_group,
                                                "CAN_DataFrame.DataLength");
  if (!data_length) {
    LOG_ERROR() << "Data length channel 'CAN_DataFrame.DataLength' is missing. File: "
                << reader.ShortName();
  }
*/
  if (!data_bytes) {
    LOG_ERROR() << "Data bytes channel 'CAN_DataFrame.DataBytes' is missing. File: "
                << reader.ShortName();
  }
  if (!rel_time || !can_id || !data_bytes) {
    wxMessageBox(
        "Not a CAN logger file. Missing channels.\nMore information in the log file.",
        "File Read Error", wxOK | wxCENTRE | wxICON_ERROR);
    return;
  }

  const auto read_data = reader.ReadData(*data_group);
  reader.Close();
  data_group->DetachAllSampleObservers();
  const auto nof_messages = data_bytes->NofSamples();
  if (nof_messages == 0) {
    wxMessageBox(
        "No data messages in the file..\nMore information in the log file.",
        "File Read Error", wxOK | wxCENTRE | wxICON_INFORMATION);
    return;
  }
  size_t count_messages = 0;
  dbc_file_->MessageSize(0);
  dbc_file_->MessageSize(nof_messages);
  for (size_t sample = 0; sample < nof_messages; ++sample) {
    uint64_t time = 0;
    const auto time_valid = rel_time->GetChannelValue(sample, time);
    time += base_time;

    uint32_t ident = 0;
    const auto ident_valid = can_id->GetChannelValue(sample, ident);

    std::vector<uint8_t> data;
    const auto data_valid = data_bytes->GetChannelValue(sample, data);

    if (time_valid && ident_valid && data_valid) {
      DbcMessage message(time, ident , data);
      dbc_file_->AddMessage(sample, message);
      const auto parse = dbc_file_->ParseMessage(message);
      if (parse) {
        ++count_messages;
      }
    }
  }

  std::ostringstream result;
  result << "Found " << count_messages << " (" << nof_messages
         << ") matching messages" << std::endl;
  result << "File: " << reader.ShortName();
  wxMessageBox(
      result.str(),
      "File Read Information", wxOK | wxCENTRE | wxICON_INFORMATION);
  auto* child_window = dynamic_cast<ChildFrame*>(GetDocumentWindow());
  if (child_window != nullptr) {
    child_window->RedrawListView();
  }
}

void DbcDocument::OnUpdateImportCanMessageFile(wxUpdateUIEvent &event) {
  if (!dbc_file_) {
    event.Enable(false);
  } else if (dbc_file_->GetNetwork() == nullptr) {
    event.Enable(false);
  }
  event.Enable(true);
}

} // namespace dbc::viewer