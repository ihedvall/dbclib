/*
* Copyright 2022 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "dbc/dbcfile.h"
#include <filesystem>
#include <fstream>
#include <ranges>
#include <algorithm>
#include "dbcscanner.h"

using namespace std::filesystem;

namespace dbc {

std::string DbcFile::Name() const {
  try {
    const path filename(filename_);
    return filename.stem().string();
  } catch (const std::exception& err) {
    last_error_ = err.what();
  }
  return {};
}
bool DbcFile::ParseFile() {
  int ret;
  try {
    const path filename(filename_);
    if (!exists(filename)) {
      std::ostringstream error;
      error << "The file doesn't exist. File: " << filename_;
      return false;
    }

    std::ifstream temp(filename_);
    DbcScanner scanner(temp);
    DbcParser parser(scanner);
    ret = parser.parse();
    last_error_ = scanner.LastError();
    temp.close();
    network_.reset(scanner.ReleaseNetwork());
    network_->Filename(filename_);
  } catch (const std::exception& err) {
    std::ostringstream error;
    error << "Internal error. Error: " << err.what() << ". File: " << filename_;
    last_error_ = error.str();
    ret = -1;
  }
  // Set the J1939 Flag
  if (network_) {
    const auto& message_list = network_->Messages();
    const bool j1939 = std::ranges::any_of(
        message_list, [&](const auto& mess) { return mess.second.IsJ1939(); });
    network_->J1939(j1939);
  }
  return ret == 0;
}

void DbcFile::SetMessageSize(size_t nof_messages) {
  message_list_.clear();
  base_time_ = 0;
  if (nof_messages > 0) {
    message_list_.resize(nof_messages);
  }
}

void DbcFile::AddMessage(size_t index, const DbcMessage& message) {
  if (index < message_list_.size()) {
    message_list_[index] = message;
  }
  if (base_time_ == 0) {
    base_time_ = message.Time();
  }
}

bool DbcFile::ParseNMEA2000(const DbcMessage& message) {
  bool parse = false;
  if (!network_) {
    return parse;
  }
  auto* mess = network_->GetMessageByPgn(message.Pgn());
  if (mess == nullptr) {
    return parse;
  }
  if (mess->Source() <= 253 && mess->Source() != message.Source()) {
    return parse;
  }

  // Fix the message to node relation
  const auto& sender_list = mess->Senders();
  if (sender_list.size() == 1 && message.Source() <= 253) {
    auto* node = network_->GetNode(sender_list[0]);
    if (node != nullptr && node->Source() != message.Source()) {
      node->Source(message.Source());
    }
  }

  // Check if fast package message
  if (mess->NofBytes() > 8) {
    const auto& bytes = message.Data();
    const auto pack_id = !bytes.empty() ? bytes[0] >> 5 : 0;
    const uint8_t seq_no = !bytes.empty() ? bytes[0] & 0x1F : 0;
    const size_t offset = seq_no > 0 ? 1 : 2;
    const size_t data_index = seq_no > 0 ? 6 + ((seq_no - 1) * 7) : 0;
    if (seq_no == 0) {
      mess->ResetSequenceNumber();
    }
    if (seq_no == mess->NextSequenceNumber()) {
      const auto last = mess->UpdateData(message.Data(), offset, data_index);
      if (last) {
        mess->ParseMessage(message.Time(), message.CanId());
        mess->StepSampleCounter();
        parse = true;
      }
    }
  } else {
    mess->UpdateData(message.Data(),0, 0);
    mess->ParseMessage(message.Time(), message.CanId());
    mess->StepSampleCounter();
    parse = true;
  }
  return parse;
}

bool DbcFile::ParseJ1939(const DbcMessage& message) {
  bool parse = false;
  if (!network_) {
    return parse;
  }
  auto* mess = network_->GetMessageByPgn(message.Pgn());
  if (mess == nullptr) {
    return parse;
  }
  if (mess->Source() <= 253 && mess->Source() != message.Source()) {
    return parse;
  }

  // Fix the message to node relation
  const auto& sender_list = mess->Senders();
  if (sender_list.size() == 1 && message.Source() <= 253) {
    auto* node = network_->GetNode(sender_list[0]);
    if (node != nullptr && node->Source() != message.Source()) {
      node->Source(message.Source());
    }
  }

  mess->UpdateData(message.Data(),0, 0);
  mess->ParseMessage(message.Time(), message.CanId());
  mess->StepSampleCounter();
  parse = true;
  return parse;
}

bool DbcFile::ParseStandardCAN(const DbcMessage& message) {
  bool parse = false;
  if (!network_) {
    return false;
  }
  auto* mess = network_->GetMessageByCanId(message.CanId());
  if (mess != nullptr) {
    mess->UpdateData(message.Data());
    mess->ParseMessage(message.Time(), message.CanId());
    mess->StepSampleCounter();
    parse = true;
  }
  return parse;
}

void DbcFile::ResetSampleCounter() const {
  if (!network_) {
    return;
  }
  const auto& message_list = network_->Messages();
  for (const auto& mess : message_list) {
    mess.second.ResetSampleCounter();
  }
}

bool DbcFile::ParseMessage(const DbcMessage& message) {
  if (!network_) {
    return false;
  }
  const auto protocol = network_->Protocol();
  bool parse = false;
  switch (protocol) {
    case ProtocolType::NMEA2000:
      parse = ParseNMEA2000(message);
      break;

    case ProtocolType::J1939:
      parse = ParseJ1939(message);
      break;

    default:
      parse = ParseStandardCAN(message);
      break;
  }
  return parse;
}

void DbcFile::ReparseMessageList() {
  ResetSampleCounter();
  for (const auto& message : message_list_) {
    ParseMessage(message);
  }
}

}  // namespace dbc