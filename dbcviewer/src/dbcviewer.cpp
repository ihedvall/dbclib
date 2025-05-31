/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#include <filesystem>
#define BOOST_LOCALE_HIDE_AUTO_PTR
#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include <boost/locale.hpp>

#include <wx/wx.h>
#include <wx/docview.h>
#include <wx/config.h>
#include <wx/utils.h>

#include "util/logconfig.h"
#include "util/logstream.h"

#include "dbcviewer.h"
#include "mainframe.h"
#include "dbcdocument.h"
#include "dbcview.h"
#include "windowid.h"

using namespace util::log;

wxIMPLEMENT_APP(dbc::viewer::DbcViewer);

namespace {
  boost::asio::io_context kIoContext;
}

namespace dbc::viewer {

wxBEGIN_EVENT_TABLE(DbcViewer, wxApp)
  EVT_UPDATE_UI(kIdOpenLogFile,DbcViewer::OnUpdateOpenLogFile)
  EVT_MENU(kIdOpenLogFile, DbcViewer::OnOpenLogFile)
  EVT_UPDATE_UI(kIdGnuPlotDownloadPage,DbcViewer::OnUpdateGnuPlotDownloadPage)
  EVT_MENU(kIdGnuPlotDownloadPage, DbcViewer::OnGnuPlotDownloadPage)
wxEND_EVENT_TABLE()

bool DbcViewer::OnInit() {
  if (!wxApp::OnInit()) {
    return false;
  }

  // Setup correct localization when formatting date and times
  boost::locale::generator gen;
  std::locale::global(gen(""));

    // Setup system basic configuration
  SetVendorDisplayName("DbcLib");
  SetVendorName("DbcLib");
  SetAppName("DbcViewer");
  SetAppDisplayName("DBC File Viewer");

  // Set up the log file.
  // The log file will be in %TEMP%/report_server/mdf_viewer.log
  auto& log_config = LogConfig::Instance();
  log_config.Type(LogType::LogToFile);
  log_config.SubDir("dbclib/log");
  log_config.BaseName("dbcviewer");
  log_config.CreateDefaultLogger();
  LOG_INFO() << "Log File created. Path: " << log_config.GetLogFile();

  notepad_ = util::log::FindNotepad();

  // Find the path to the 'gnuplot.exe'
  try {
    auto gp = boost::process::environment::find_executable("gnuplot");
    gnuplot_ = gp.string();
    LOG_INFO() << "GnuPlot found. Path: " << gnuplot_;
  } catch(const std::exception& ) {
    gnuplot_.clear();
  }
  if (gnuplot_.empty()) {
    LOG_INFO() << "GnuPlot was not found.";
  }

  // Create a temporary directory for this application
  try {
    auto temp_dir = std::filesystem::temp_directory_path();
    auto unique = boost::filesystem::unique_path("DbcViewer%%%%");
    temp_dir.append(unique.string());
    std::filesystem::remove_all(temp_dir);
    std::filesystem::create_directories(temp_dir);
    my_temp_dir_ = temp_dir.string();
    LOG_INFO() << "Created a temporary directory. Path: " << my_temp_dir_;
  } catch (const std::exception& error) {
    LOG_ERROR() << "Error when creating temporary directory. Error:" << error.what();
  }


  auto* app_config = wxConfig::Get();
  wxPoint start_pos;
  app_config->Read("/MainWin/X",&start_pos.x, wxDefaultPosition.x);
  app_config->Read("/MainWin/Y",&start_pos.y, wxDefaultPosition.x);
  wxSize start_size;
  app_config->Read("/MainWin/XWidth",&start_size.x, 1200);
  app_config->Read("/MainWin/YWidth",&start_size.y, 800);
  bool maximized = false;
  app_config->Read("/MainWin/Max",&maximized, maximized);

  auto* doc_manager = new wxDocManager;
  new wxDocTemplate(doc_manager, "DBC File","*.dbc","",
                                         "dbc","DbcViewer","DBC Viewer",
                                         wxCLASSINFO(DbcDocument), wxCLASSINFO(DbcView));
  auto* frame = new MainFrame(GetAppDisplayName(), start_pos, start_size, maximized);

  frame->Show(true);

  return true;
}

int DbcViewer::OnExit() {
  LOG_INFO() << "Closing application";
  auto* app_config = wxConfig::Get();
  auto* doc_manager = wxDocManager::GetDocumentManager();
  doc_manager->FileHistorySave(*app_config);
  delete doc_manager;
  LOG_INFO() << "Saved file history.";

  try {
    std::filesystem::remove_all(my_temp_dir_);
    LOG_INFO() << "Removed temporary directory. Path: " << my_temp_dir_;
  } catch (const std::exception& error) {
    LOG_ERROR() << "Failed to remove temporary directory. Path: " << my_temp_dir_;
  }

  auto& log_config = LogConfig::Instance();
  log_config.DeleteLogChain();
  return wxApp::OnExit();
}

void DbcViewer::OnOpenLogFile(wxCommandEvent& ) {
  auto& log_config = LogConfig::Instance();
  std::string logfile = log_config.GetLogFile();
  OpenFile(logfile);

}

void DbcViewer::OnUpdateOpenLogFile(wxUpdateUIEvent &event) {
  if (notepad_.empty()) {
    event.Enable(false);
    return;
  }

  auto& log_config = LogConfig::Instance();
  std::string logfile = log_config.GetLogFile();
  try {
    std::filesystem::path p(logfile);
    const bool exist = std::filesystem::exists(p);
    event.Enable(exist);
  } catch (const std::exception&) {
    event.Enable(false);
  }
}

void DbcViewer::OnGnuPlotDownloadPage(wxCommandEvent& event) {
  wxLaunchDefaultBrowser("http://www.gnuplot.info/",
                         wxBROWSER_NEW_WINDOW);
}

void DbcViewer::OnUpdateGnuPlotDownloadPage(wxUpdateUIEvent &event) {
   event.Enable( true /* gnuplot_.empty() */ );
}

void DbcViewer::OpenFile(const std::string& filename) const {
  if (!notepad_.empty()) {
    boost::process::process proc(kIoContext, notepad_, {filename});
    proc.detach();
  }
}

} // end namespace dbc::viewer


