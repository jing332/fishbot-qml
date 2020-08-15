
#ifndef TEXTFORMATTING_H
#define TEXTFORMATTING_H

#include <QMap>
#include <QObject>
#include <QPainter>

typedef struct {
  QChar code;
  QString name;
  QString hex;
} TextColor;

static QList<QString> colorNames = {
    "black",     "dark_blue",    "dark_green", "dark_aqua",
    "dark_red",  "dark_purple",  "gold",       "gray",
    "dark_gray", "blue",         "green",      "aqua",
    "red",       "light_purple", "yellow",     "white"};

static QList<TextColor> colors{
    {'0', "black", "#000000"},      {'1', "dark_blue", "#0000aa"},
    {'2', "dark_green", "#00aa00"}, {'3', "dark_aqua", "#00aaaa"},
    {'4', "dark_red", "#aa0000"},   {'5', "dark_purple", "#aa00aa"},
    {'6', "gold", "#ffaa00"},       {'7', "gray", "#aaaaaa"},
    {'8', "dark_gray", "#555555"},  {'9', "blue", "#5555ff"},
    {'a', "green", "#55ff55"},      {'b', "aqua", "#55ffff"},
    {'c', "red", "#ff5555"},        {'d', "light_purple", "#ff55ff"},
    {'e', "yellow", "#ffff55"},     {'f', "white", "#ffffff"}};

class TextFormatting {
 public:
  static QHash<QString, QString> langHash;

 public:
  TextFormatting();

  QChar codeByName(QString &name);
  QString colorByCode(QChar &code);

  static TextColor colorByName(QString &name);
  static TextColor colorByCode(QChar code);

  static void drawText(QPainter *painter, const QString &text, int x, int y,
                       int lineWidth = 0);
};

#endif  // TEXTFORMATTING_H
