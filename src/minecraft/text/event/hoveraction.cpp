#include "hoveraction.h"

const QStringList HoverActionUtils::names = {"", "show_text", "show_item",
                                             "show_achievement", "show_entity"};

HoverAction HoverActionUtils::byName(const QString &name) {
  QString str = name.toLower();
  for (int i = 0; i < names.size(); i++) {
    if (str == names.at(i)) return HoverAction(i);
  }

  return HOVER_NONE;
}
