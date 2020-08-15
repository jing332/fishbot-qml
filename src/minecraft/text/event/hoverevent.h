#ifndef HOVEREVENT_H
#define HOVEREVENT_H

#include "hoveraction.h"

class TextComponent;

class HoverEvent {
 private:
  HoverAction action_ = HOVER_NONE;
  TextComponent *value_ = nullptr;

 public:
  HoverEvent(){};
  HoverEvent(HoverAction action, TextComponent *value)
      : action_(action), value_(value) {}

  HoverAction GetAction() { return action_; }
  TextComponent *GetValue() { return value_; }
  bool IsEmpty() { return action_ == HOVER_NONE && !value_; }
};

#endif  // HOVEREVENT_H
