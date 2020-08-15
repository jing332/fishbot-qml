#include "textformatting.h"

#include <QColor>
#include <QDebug>
#include <QStringBuilder>

QHash<QString, QString> TextFormatting::langHash = QHash<QString, QString>();

TextFormatting::TextFormatting() {}

QChar TextFormatting::codeByName(QString &name) {
  for (TextColor color : colors) {
    if (color.name.compare(name) == 0) {
      return color.code;
    }
  }
  return '0';
}

QString TextFormatting::colorByCode(QChar &code) {
  for (TextColor color : colors) {
    if (color.code == code) {
      return color.name;
    }
  }
  return "black";
}

TextColor TextFormatting::colorByName(QString &name) {
  for (TextColor color : colors) {
    if (color.name.compare(name) == 0) return color;
  }
  return colors.at(0);
}

TextColor TextFormatting::colorByCode(QChar code) {
  for (TextColor color : colors) {
    if (color.code == code) return color;
  }

  return colors.at(0);
}

void TextFormatting::drawText(QPainter *painter, const QString &text, int x,
                              int y, int lineWidth) {
  QFont font(painter->font());
  auto fontMetrics = painter->fontMetrics();
  QPen pen(Qt::white);

  int currentX = x;
  int currentY = y;
  int fontHeight = fontMetrics.height() + fontMetrics.descent();

  for (int i = 0; i < text.length(); i++) {
    QChar c = text.at(i);
    if (QStringLiteral("§").at(0) == c && text.length() > i + 1) {
      int index = QStringLiteral("0123456789abcdefklmnor")
                      .indexOf(text.at(i + 1)); /*获取§后面的样式代码的索引*/

      if (index < 16) {
        pen.setColor(colorByCode(text.at(i + 1)).hex);
      } else if (index == 16) {  // k 随机
        // TODO
      } else if (index == 17) {  // l 粗体
        font.setBold(true);
      } else if (index == 18) {  // m 删除线
        font.setOverline(true);
      } else if (index == 19) {  // n 下划线
        font.setUnderline(true);
      } else if (index == 20) {  // o 斜体
        font.setItalic(true);
      } else if (index == 21) {  // r 重置
        font.setBold(false);
        font.setOverline(false);
        font.setUnderline(false);
        font.setItalic(false);
        pen.setColor(Qt::white);
      }
      i++;
    } else {
      //换行
      if ('\n' == c) {
        currentX = x;  //重置x
        currentY += fontHeight;
        continue;
      } else if (lineWidth != 0 && (currentX - x) > lineWidth) {  //自动换行
        currentX = x;
        currentY += fontHeight;
      }

      painter->setFont(font);
      painter->setPen(pen);

      painter->drawText(currentX, currentY, c);
      currentX += fontMetrics.horizontalAdvance(c);
    }
  }
}
