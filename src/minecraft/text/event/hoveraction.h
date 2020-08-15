#ifndef HOVERACTION_H
#define HOVERACTION_H

#include <QObject>

enum HoverAction {
  HOVER_NONE,
  SHOW_TEXT,
  SHOW_ITEM,
  SHOW_ACHIEVEMENT,
  SHOW_ENTITY
};

class HoverActionUtils {
  const static QStringList names;

 public:
  static HoverAction byName(const QString &name);
};

#endif  // HOVERACTION_H
