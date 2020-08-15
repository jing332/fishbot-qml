#include "chatformat.h"

const QStringList ChatFormatUtils::kNames = {
    "bold", "underlined", "strikethrough", "italic", "obfuscated"};

ChatFormat ChatFormatUtils::ByName(const QString &name) {
  QString str = name.toLower();
  for (int i = 0; i < kNames.size(); i++) {
    if (str == kNames.at(i)) return ChatFormat(i);
  }

  return ChatFormat(-1);
}

static const char codes[] = {'l', 'n', 'm', 'o', 'k'};
QChar ChatFormatUtils::GetCode(ChatFormat format) { return codes[format]; }
