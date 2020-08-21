/*
 * Copyright (C) lichuang
 */

#pragma once

#include "base/define.h"
#include "base/entity.h"
#include "base/status.h"
#include "base/message_type.h"
#include "base/typedef.h"

namespace libraft {

extern MessageId newMsgId();

struct IMessage {
public:
  IMessage(MessageType typ, bool isResponse = false) 
    : id_(0),
      type_(typ),
      isResponse_(isResponse) {
    // response message id is the src message id
    if (!isResponse) {
      id_ = newMsgId();
    }
  }

  virtual ~IMessage() {}
  
  void setDstEntiity(const EntityRef& ref) {
    dstRef_ = ref;
  }

  void setSrcEntiity(const EntityRef& ref) {
    srcRef_ = ref;
  }

  void responseFor(IMessage *msg) {
    isResponse_ = true;
    srcRef_ = msg->dstRef_;
    dstRef_ = msg->srcRef_;
    id_ = msg->id_;
  }

  MessageId id_;
  EntityRef srcRef_;
  EntityRef dstRef_;
  Status error_;
  MessageType type_;
  bool isResponse_;
};

};