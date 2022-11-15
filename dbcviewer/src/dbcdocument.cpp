/*
 * Copyright 2021 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#include <sstream>

#include <filesystem>
#include <boost/process.hpp>
#if (_MSC_VER)
#include <boost/process/windows.hpp>
#endif
#include <boost/filesystem.hpp>

#include <wx/msgdlg.h>

#include "util/logstream.h"
#include "util/csvwriter.h"
#include "dbcdocument.h"
#include "windowid.h"
#include "dbcviewer.h"
#include "channelobserverframe.h"

using namespace util::log;
using namespace dbc;
namespace {
/**
 * Creates a CSV file using sample observers as input.
 *
 * The CSV file is created in the applications temporary directory and the file name is unique.
 * Note that if the observer list only have one channel, the file will add the samples as first column.
 * The same applies if the first channel not is a master channel.
 * @param list Sample observer list containing samples.
 * @return Full path to the created file or an empty string if the function fails.
 */
 /*
std::string CreateCsvFile(const dbc::ChannelObserverList& list) {
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

  const bool master = list.size() > 1 && list[0]->IsMaster();

  // Add the header first
  if (!master) {
    // First column is sample number
    csv.AddColumnHeader("Sample", "");
  }
  for (const auto& channel : list) {
     csv.AddColumnHeader(channel->Name(),channel->Unit());
  }
  csv.AddRow();
  // Add the samples
  for (size_t sample = 0; sample < list[0]->NofSamples(); ++sample) {
    // Add the sample number first
    if (!master) {
      // First column is sample number
      csv.AddColumnValue(sample);
    }
    for (const auto& channel : list) {
      std::string value;
      const bool valid  = channel->GetEngValue(sample, value); // Note that we may lose some digits here
      csv.AddColumnValue(valid ? value : "");
    }
    csv.AddRow();
  }

 return csv_file;
}

std::string CreateGnuPlotFile(const mdf::ChannelObserverList& list, const std::string& csv_file, const std::string& title) {
  if (list.empty() || csv_file.empty()) {
    LOG_ERROR() << "No CSV file or observer list is empty.";
    return "";
  }

  std::string gp_file;
  try {
    std::filesystem::path p(csv_file);
    p.replace_extension(".gp");
    gp_file = p.generic_string();
  } catch(const std::exception& error) {
    LOG_ERROR() << "Failed to create gnuplot file. CSV File: " << csv_file;
  }
  const bool master = list.size() > 1 && list[0]->IsMaster();
  std::FILE* file = fopen(gp_file.c_str(), "wt");
  std::ostringstream x_label;
  std::ostringstream y_label;
  if (!master) {
    x_label << "Sample";
    y_label << list[0]->Name();
    if (!list[0]->Unit().empty()) {
      y_label << " [" << list[0]->Unit() << "]";
    }
  } else {
    x_label << list[0]->Name();
    if (!list[0]->Unit().empty()) {
      x_label << " [" << list[0]->Unit() << "]";
    }

    y_label << list[1]->Name();
    if (!list[1]->Unit().empty()) {
      y_label << " [" << list[1]->Unit() << "]";
    }
  }

  if (file != nullptr) {
    fprintf(file, "set terminal wxt noenhanced title \"%s\" size 1200, 1000\n", title.c_str());
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
*/
} // end namespace

namespace dbc::viewer {
wxIMPLEMENT_DYNAMIC_CLASS(DbcDocument, wxDocument) // NOLINT

wxBEGIN_EVENT_TABLE(DbcDocument, wxDocument) // NOLINT
  EVT_UPDATE_UI(kIdShowGroupData, DbcDocument::OnUpdateShowGroupData)
  EVT_MENU(kIdShowGroupData, DbcDocument::OnShowGroupData)
  EVT_UPDATE_UI(kIdShowChannelData, DbcDocument::OnUpdateShowChannelData)
  EVT_MENU(kIdShowChannelData, DbcDocument::OnShowChannelData)
  EVT_UPDATE_UI(kIdPlotChannelData, DbcDocument::OnUpdatePlotChannelData)
  EVT_MENU(kIdPlotChannelData, DbcDocument::OnPlotChannelData)
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

void DbcDocument::OnShowGroupData(wxCommandEvent &event) {
  /*
  const auto selected_id = GetSelectedBlockId();
  const auto *selected_block = GetBlock(selected_id);
  if (selected_block == nullptr) {
    return;
  }
  const IDataGroup* dg = nullptr;
  const IChannelGroup* cg = nullptr;
  if (selected_block->BlockType() == "DG") {
    dg = dynamic_cast<const IDataGroup*>(selected_block);
    if (dg != nullptr) {
     auto cg_list = dg->ChannelGroups();
     if (!cg_list.empty()) {
       cg = cg_list[0];
     }
    }
  } else if (selected_block->BlockType() == "CG") {
    cg = dynamic_cast<const IChannelGroup*>(selected_block);
    const auto parent_id = GetParentBlockId();
    const auto *parent_block = GetBlock(parent_id);
    if (parent_block != nullptr) {
      dg = dynamic_cast<const IDataGroup*>(parent_block);
    }
  }
  if (dg == nullptr || cg == nullptr) {
    return;
  }

  auto* view = GetFirstView();
  if (view == nullptr) {
    return;
  }

  auto* parent = view->GetFrame();
  if (parent == nullptr) {
    return;
  }

  std::ostringstream title;
  if (!cg->Name().empty()) {
    title << cg->Name();
  }

  if (!dg->Description().empty()) {
    if (!title.str().empty()) {
      title << "/";
    }
    title << dg->Description();
  }

  if (!title.str().empty()) {
    title << "/";
  }
  title << reader_->ShortName();

  auto observer_list = std::make_unique<mdf::ChannelObserverList>();
  mdf::CreateChannelObserverForChannelGroup(*dg, *cg, *observer_list);
  const bool read = reader_->ReadData(*dg);
  if (!read) {
    wxMessageBox("The read failed.\nMore information in the log file.",
                 "Failed to Read Data Block", wxCENTRE | wxICON_ERROR);
    return;
  }
  auto data_frame = new ChannelObserverFrame(observer_list, parent, wxID_ANY, title.str());
  data_frame->Show();
   */
}

void DbcDocument::OnUpdateShowGroupData(wxUpdateUIEvent &event) {
  event.Enable(false);
  if (!dbc_file_) {
    return;
  }
/*
  const auto selected_id = GetSelectedBlockId();
  const auto selected_block = GetBlock(selected_id);
  if (selected_block == nullptr) {
    return;
  }

  if (selected_block->BlockType() == "DG") {
    const auto* dg = dynamic_cast<const IDataGroup*>(selected_block);
    if (dg == nullptr) {
      return;
    }
    auto cg_list = dg->ChannelGroups();
    event.Enable(cg_list.size() == 1);
  } else if (selected_block->BlockType() == "CG") {
    event.Enable(true);
  }
  */
}

void DbcDocument::OnShowChannelData(wxCommandEvent &event) {
  if (!dbc_file_) {
    return;
  }
/*
  const IChannel* channel = nullptr;
  const auto selected_id = GetSelectedBlockId();
  const auto *selected_block = GetBlock(selected_id);
  if (selected_block != nullptr && selected_block->BlockType() == "CN") {
    channel = dynamic_cast<const IChannel*>(selected_block);
  }
  if (channel == nullptr) {
    return;
  }

  const auto *data_group = mdf_file->FindParentDataGroup(*channel);
  if (data_group == nullptr) {
    return;
  }

  const auto *channel_group = data_group->FindParentChannelGroup(*channel);
  if (channel_group == nullptr) {
    return;
  }

  // Need to show the master channel as well as the data channel
  const auto* x_axis = channel_group->GetXChannel(*channel);
  // Need to show the master channel as well as the data channel

  auto* view = GetFirstView();
  if (view == nullptr) {
    return;
  }

  auto* parent = view->GetFrame();
  if (parent == nullptr) {
    return;
  }

  std::ostringstream title;
  if (!channel->Name().empty()) {
    title << channel->Name();
  }

  if (!channel_group->Name().empty()) {
    if (!title.str().empty()) {
      title << "/";
    }
    title << channel_group->Name();
  }

  if (!data_group->Description().empty()) {
    if (!title.str().empty()) {
      title << "/";
    }
    title << data_group->Description();
  }

  if (!title.str().empty()) {
    title << "/";
  }
  title << reader_->ShortName();

  auto observer_list = std::make_unique<mdf::ChannelObserverList>();
  if (x_axis != nullptr && x_axis->Index() != channel->Index()) {
    observer_list->emplace_back(std::move(mdf::CreateChannelObserver(
        *data_group, *channel_group, *x_axis)));
  }
  observer_list->emplace_back(std::move(mdf::CreateChannelObserver(
      *data_group, *channel_group, *channel)));

  const bool read = reader_->ReadData(*data_group);
  if (!read) {
    wxMessageBox("The read failed.\nMore information in the log file.",
                 "Failed to Read Data Block", wxCENTRE | wxICON_ERROR);
    return;
  }

  auto data_frame = new ChannelObserverFrame(observer_list, parent, wxID_ANY, title.str());
  data_frame->Show();
  */
}

void DbcDocument::OnUpdateShowChannelData(wxUpdateUIEvent &event) {
  event.Enable(false);
  if (!dbc_file_) {
    return;
  }
/*
  const auto selected_id = GetSelectedBlockId();
  const auto selected_block = GetBlock(selected_id);
  if (selected_block == nullptr) {
    return;
  }

  if (selected_block->BlockType() == "CN") {
    event.Enable(true);
  }
  */
}

void DbcDocument::OnPlotChannelData(wxCommandEvent &event) {
  /*
  const IDataGroup* dg = nullptr;
  const IChannelGroup* cg = nullptr;
  const IChannel* cn = nullptr;

  const auto selected_id = GetSelectedBlockId();
  const auto *selected_block = GetBlock(selected_id);
  if (selected_block != nullptr && selected_block->BlockType() == "CN") {
    cn = dynamic_cast<const IChannel*>(selected_block);
  }

  const auto parent_id = GetParentBlockId();
  const auto *parent_block = GetBlock(parent_id);
  if (parent_block != nullptr && parent_block->BlockType() == "CG") {
    cg = dynamic_cast<const IChannelGroup*>(parent_block);
  }

  const auto grand_parent_id = GetGrandParentBlockId();
  const auto *grand_parent_block = GetBlock(grand_parent_id);
  if (grand_parent_block != nullptr && grand_parent_block->BlockType() == "DG") {
    dg = dynamic_cast<const IDataGroup*>(grand_parent_block);
  }
  auto& app = wxGetApp();
  if (dg == nullptr || cg == nullptr || cn == nullptr || app.GnuPlot().empty()) {
    return;
  }
  const auto* x_axis = cg->GetXChannel(*cn); // Need to show the master channel as well as the data channel

  std::ostringstream title;
  if (!cn->Name().empty()) {
    title << cn->Name();
  }

  if (!cg->Name().empty()) {
    if (!title.str().empty()) {
      title << "/";
    }
    title << cg->Name();
  }

  if (!dg->Description().empty()) {
    if (!title.str().empty()) {
      title << "/";
    }
    title << dg->Description();
  }

  if (!title.str().empty()) {
    title << "/";
  }
  title << reader_->ShortName();

  // Create the observer list
  auto observer_list = std::make_unique<mdf::ChannelObserverList>();
  if (x_axis != nullptr) {
    observer_list->emplace_back(std::move(mdf::CreateChannelObserver(*dg, *cg, *x_axis)));
  }
  observer_list->emplace_back(std::move(mdf::CreateChannelObserver(*dg, *cg, *cn)));

  // Read in the values from the MDF file
  const bool read = reader_->ReadData(*dg);
  if (!read) {
    wxMessageBox("The read failed.\nMore information in the log file.",
                 "Failed to Read Data Block", wxCENTRE | wxICON_ERROR);
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
  */
}

void DbcDocument::OnUpdatePlotChannelData(wxUpdateUIEvent &event) {
  event.Enable(false);
  auto& app = wxGetApp();
  if (!dbc_file_ || app.GnuPlot().empty()) {
    return;
  }
/*
  const auto selected_id = GetSelectedBlockId();
  const auto selected_block = GetBlock(selected_id);
  if (selected_block == nullptr) {
    return;
  }

  if (selected_block->BlockType() != "CN") {
    return;
  }
  const auto* cn = dynamic_cast<const IChannel*>(selected_block);
  if (cn == nullptr) {
    return;
  }

  // Note that plotting of strings and absolute times are tricky.
  // The timestamp (CAN Open Date/Time) is possible but labeling the tics is
  // almost impossible.
  if (!cn->IsNumber()) {
    return;
  }
  */
  event.Enable(true);

}

} // namespace dbc::viewer