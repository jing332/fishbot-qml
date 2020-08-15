#ifndef CHATCOLOR_H
#define CHATCOLOR_H

#include <QObject>

enum ChatColor {
  BLACK = 0,
  DARK_BLUE,
  DARK_GREEN,
  DARK_AQUA,
  DARK_RED,
  DARK_PURPLE,
  GOLD,
  GRAY,
  DARK_GRAY,
  BLUE,
  GREEN,
  AQUA,
  RED,
  LIGHT_PURPLE,
  YELLOW,
  WHITE,
  RESET,
  NONE
};

const static QStringList names = {
    "black",       "dark_blue", "dark_green", "dark_aqua",    "dark_red",
    "dark_purple", "gold",      "gray",       "dark_gray",    "blue",
    "green",       "aqua",      "red",        "light_purple", "yellow",
    "white",       "reset",     "none"};

const static char codes[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
                             '9', 'a', 'b', 'c', 'd', 'e', 'f', 'r'};

class ChatColorUtils {
 public:
  static ChatColor byName(const QString &name) {
    QString str = name.toLower();
    for (int i = 0; i < names.size(); i++) {
      if (str == names.at(i)) return ChatColor(i);
    }

    return ChatColor(NONE);
  }
  static QChar getCode(ChatColor color) {
    if (color < 17) {
      return codes[color];
    }
    return ' ';
  }
};
#endif  // CHATCOLOR_H
