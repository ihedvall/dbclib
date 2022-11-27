/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <memory>
#include <wx/listctrl.h>
#include <dbc/signalobserver.h>
#include <dbc/network.h>

namespace dbc::viewer {

class SignalObserverListView : public wxListView {
 public:
  explicit SignalObserverListView(wxWindow *parent,
                                  wxWindowID win_id = wxID_ANY,
                                  const wxPoint &pos = wxDefaultPosition,
                                  const wxSize &size = wxDefaultSize,
         long style = wxLC_REPORT | wxLC_VIRTUAL | wxLC_HRULES | wxLC_VRULES);
  ~SignalObserverListView() override;

  void ObserverList(std::unique_ptr<SignalObserverList>& list);
  [[nodiscard]] size_t NofSamples() const {return sample_time_list_.size();}
  void BaseTime(uint64_t ns1970) {base_time_ = ns1970;}
  void SetNetwork(const Network* network) {network_ = network;}
 protected:
  [[nodiscard]] wxString OnGetItemText(long item, long column) const override;

 private:
  std::unique_ptr<SignalObserverList> observer_list_;
  std::vector<std::pair<uint64_t,uint32_t>> sample_time_list_; ///< Sample # to timestamp list
  uint64_t base_time_ = 0;
  const Network* network_ = nullptr;
};

} //namespace mdf::viewer




