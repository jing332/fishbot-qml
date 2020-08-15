#ifndef JSONHELPER_H
#define JSONHELPER_H

#include <QObject>

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/writer.h"

using namespace rapidjson;

class JsonHelper {
 public:
  JsonHelper();

  static bool GetBool(const Value &v);

  virtual QString ToJson() const;
  virtual void FromJson(const QString &json);
  virtual void FromJson(const Value &v);
};

#endif  // JSONHELPER_H
