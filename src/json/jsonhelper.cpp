#include "jsonhelper.h"

#include <sstream>
using namespace std;

JsonHelper::JsonHelper() {}

bool JsonHelper::GetBool(const Value &value) {
  bool b = false;
  if (value.IsString()) {
    istringstream(value.GetString()) >> boolalpha >> b;
  } else if (value.IsBool())
    b = value.GetBool();

  return b;
}

QString JsonHelper::ToJson() const { return ""; }

void JsonHelper::FromJson(const QString &json) { Q_UNUSED(json) }

void JsonHelper::FromJson(const Value &v) { Q_UNUSED(v) }
