/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "protocoldialog.h"
#include "windowid.h"
#include <sstream>
namespace {


const wxString kProtocolList[] = {L"Standard CAN",
                                  L"J1939",
                                  L"NMEA 2000",
};

const wxString kBusList[] = {L"CAN"};

}

namespace dbc::viewer {

ProtocolDialog::ProtocolDialog(wxWindow *parent)
: wxDialog(parent, kIdSelectProtocol, L"Select Protocol and Bus",
               wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE) {

  auto* ok_button = new wxButton(this, wxID_OK,
                                 wxGetStockLabel(wxID_OK));
  auto* cancel_button = new wxButton(this, wxID_CANCEL,
                                     wxGetStockLabel(wxID_CANCEL));
  protocol_ = new wxChoice(this, wxID_ANY, wxDefaultPosition,
                                wxDefaultSize,3,kProtocolList);
  protocol_->SetSelection(0);

  bus_ = new wxChoice(this, wxID_ANY, wxDefaultPosition,
                           wxDefaultSize,1,kBusList);
  bus_->SetSelection(0);

  std::ostringstream ask;
  ask << "The DBC file doesn't contain any protocol type." << std::endl;
  ask << "Cannot parse the messages in logger file." << std::endl;
  ask << "Select the protocol type and optional the bus type." << std::endl;

  auto* info_label = new wxStaticText(this, wxID_ANY,
                                      wxString(ask.str()), wxDefaultPosition,
                                      wxDefaultSize);
  auto font = info_label->GetFont();
  font.MakeBold();
  info_label->SetFont(font);

  auto* protocol_label = new wxStaticText(this, wxID_ANY, L"Protocol Type:");
  auto* bus_label = new wxStaticText(this, wxID_ANY, L"Bus Type:");

  int label_width = 50;
  label_width = std::max(label_width, protocol_label->GetBestSize().GetX());
  label_width = std::max(label_width, bus_label->GetBestSize().GetX());

  auto* info_sizer = new wxBoxSizer(wxHORIZONTAL);
  info_sizer->Add(info_label, 0, wxALIGN_LEFT | wxALL, 10);

  auto* protocol_sizer = new wxBoxSizer(wxHORIZONTAL);
  protocol_label->SetMinSize({label_width, -1});
  protocol_sizer->Add(protocol_label, 0, wxALIGN_CENTER_VERTICAL, 5);
  protocol_sizer->Add(protocol_, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);

  auto* bus_sizer = new wxBoxSizer(wxHORIZONTAL);
  bus_label->SetMinSize({label_width, -1});
  bus_sizer->Add(bus_label, 0, wxALIGN_CENTER_VERTICAL, 5);
  bus_sizer->Add(bus_, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);

  auto* system_sizer = new wxStdDialogButtonSizer();
  system_sizer->AddButton(ok_button);
  system_sizer->AddButton(cancel_button);
  system_sizer->Realize();

  auto* main_sizer = new wxBoxSizer(wxVERTICAL);
  main_sizer->Add(info_sizer, 0, wxALIGN_LEFT | wxALL | wxEXPAND, 4);
  main_sizer->Add(protocol_sizer, 0, wxALIGN_LEFT | wxALL | wxEXPAND, 4);
  main_sizer->Add(bus_sizer, 0, wxALIGN_LEFT | wxALL | wxEXPAND, 4);
  main_sizer->Add(system_sizer, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM | wxLEFT | wxRIGHT, 10);

  SetSizerAndFit(main_sizer);
  ok_button->SetDefault();
}

void ProtocolDialog::Protocol(ProtocolType type) {
  if (protocol_ == nullptr) {
    return;
  }
  const auto selection = static_cast<int>(type);
  protocol_->SetSelection(selection);
}

ProtocolType ProtocolDialog::Protocol() const {
  if (protocol_ == nullptr) {
    return ProtocolType::StandardCAN;
  }
  return static_cast<ProtocolType>(protocol_->GetSelection());
}

void ProtocolDialog::Bus(BusType type) {
  if (bus_ == nullptr) {
    return;
  }
  const auto selection = static_cast<int>(type);
  bus_->SetSelection(selection);
}

BusType ProtocolDialog::Bus() const {
  if (bus_ == nullptr) {
    return BusType::CAN;
  }
  return static_cast<BusType>(bus_->GetSelection());
}

}  // namespace dbc::viewer