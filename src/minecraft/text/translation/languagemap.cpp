#include "languagemap.h"

LanguageMap::LanguageMap() {}

void LanguageMap::fromJson(const QString &json) {
  Document doc;
  doc.Parse(json.toStdString().c_str());

  if (!doc.HasParseError()) {
    for (auto &obj : doc.GetObject()) {
      LanguageMap::kLanguageList[obj.name.GetString()] = obj.value.GetString();
    }
  }
}

QHash<QString, QString> LanguageMap::kLanguageList = QHash<QString, QString>();
