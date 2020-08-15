#include "clickaction.h"

const QStringList ClickActionUtils::names = {
    "", "run_command", "suggest_command", "open_url", "open_file"};

ClickAction ClickActionUtils::ByName(const QString &name) {
  QString str = name.toLower();
  for (int i = 0; i < names.size(); i++) {
    if (str == names.at(i)) return ClickAction(i);
  }

  return CLICK_NONE;
}
