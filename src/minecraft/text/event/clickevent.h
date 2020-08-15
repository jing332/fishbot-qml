#ifndef CLICKEVENT_H
#define CLICKEVENT_H

#include "clickaction.h"

class ClickEvent {
 public:
  ClickEvent(){};
  ClickEvent(ClickAction action, const QString &value)
      : action_(action), value_(value){};

  ClickAction GetAction() { return action_; }
  QString GetValue() { return value_; }
  bool IsEmpty() { return value_.isEmpty(); }

 private:
  ClickAction action_;
  QString value_;
};

#endif  // CLICKEVENT_H
