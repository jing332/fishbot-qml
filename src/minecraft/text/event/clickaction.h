#ifndef CLICKACTION_H
#define CLICKACTION_H

#include <QObject>

enum ClickAction {
  CLICK_NONE,
  RUN_COMMAND,
  SUGGEST_COMMAND,
  OPEN_URL,
  OPEN_FILE
};
class ClickActionUtils {
  static const QStringList names;

 public:
  static ClickAction ByName(const QString &name);
};

#endif  // CLICKACTION_H
