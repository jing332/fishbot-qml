#ifndef LANGUAGEMAP_H
#define LANGUAGEMAP_H

#include <QHash>
#include <QObject>

#include "json/jsonhelper.h"

class LanguageMap {
 public:
  LanguageMap();

  static QHash<QString, QString> kLanguageList;

  static void fromJson(const QString &json);
};

#endif  // LANGUAGEMAP_H
