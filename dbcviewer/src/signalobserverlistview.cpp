/*
 * Copyright 2022 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#include "signalobserverlistview.h"
#include <set>
#include <util/timestamp.h>

using namespace util::time;

namespace dbc::viewer {

SignalObserverListView::SignalObserverListView(wxWindow *parent,
                                               wxWindowID win_id,
                                               const wxPoint &pos,
                                               const wxSize &size,
                                               long style)
: wxListView(parent,win_id,pos,size,style) {
}

void SignalObserverListView::ObserverList(
    std::unique_ptr<SignalObserverList> & list) {
  observer_list_ = std::move(list);
  // Make a sample to time-stamp list as the signals may have
  // different number of samples.
  sample_time_list_.clear();
  if (!observer_list_ || observer_list_->empty()) {
    return;
  }
  std::map<uint64_t, uint32_t> time_list; // ns1970->Can ID
  for ( const auto& observer : *observer_list_) {
    if (!observer) {
      continue;
    }
    for (size_t sample = 0; sample < observer->NofSamples(); ++sample) {
      const auto index = observer->SampleToIndex(sample);
      time_list.insert({observer->Time(index), observer->CanId(index)});
    }
  }
  for( const auto& itr : time_list) {
    sample_time_list_.emplace_back(itr.first, itr.second);
  }
  if (base_time_ == 0 && !sample_time_list_.empty()) {
    base_time_ = sample_time_list_[0].first;
  }

}

SignalObserverListView::~SignalObserverListView() {
  if (observer_list_) {
    observer_list_->clear();
  }
  observer_list_.reset();
}

wxString SignalObserverListView::OnGetItemText(long item, long column) const {
  // Column 0: Sample, 1: Abs, 2: Rel, 3: Source, 4: First Value in list
  if (item < 0 || column < 0 || sample_time_list_.empty() || !observer_list_) {
    return "?";
  }

  const auto sample = static_cast<size_t>(item);
  if (sample >= sample_time_list_.size() || sample_time_list_.empty()) {
    return "?";
  }
  const auto abs_time = sample_time_list_[sample].first;

  switch (column) {
    case 0:
      return wxString::Format("%llu", sample);

    case 1: {
      std::ostringstream temp;
      temp << util::time::NsToLocalDate(abs_time) << " "
           << NsToLocalTime(abs_time, 1);
      return {temp.str()};
    }

    case 2: {
      const auto rel_time = abs_time - base_time_;
      auto temp = static_cast<double>(rel_time);
      temp /= 1'000'000'000;
      return wxString::Format("%g", temp);
    }

    case 3: {
      const auto source =
          static_cast<int>(sample_time_list_[sample].second & 0xFF);
      const auto* node = network_ != nullptr ?
                               network_->GetNodeBySource(source) : nullptr;
      if (node != nullptr)  {
        return node->Name();
      }
      return source <= 253 ? wxString::Format("%d", source) : wxString();
    }

    default: {
      break;
    }
  }
  const auto value_index = static_cast<size_t>(column - 4) ;
  if (value_index >= observer_list_->size()) {
    return "?";
  }
  const auto& obs = observer_list_->at(value_index);
  if (!obs) {
    return "?";
  }

  const auto sample_index = obs->TimeToIndex(abs_time);
  if (!sample_index.second) {
    return {};
  }
  uint64_t ns1970 = 0;
  std::string value_text;
  obs->EngValue(sample_index.first, ns1970, value_text);
  return wxString::From8BitData(value_text.c_str());
}

} // namespace mdf::viewer