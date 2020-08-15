#ifndef CHATFORMAT_H
#define CHATFORMAT_H
#include <QObject>

enum ChatFormat { BOLD, UNDERLINED, STRIKETHROUGH, ITALIC, OBFUSCATED };
class ChatFormatUtils {
 public:
  static const QStringList kNames;

  static ChatFormat ByName(const QString &name);
  static QChar GetCode(ChatFormat format);
};

#endif  // CHATFORMAT_H
