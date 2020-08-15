#include "chattext.h"

#include <QPainter>

#include "minecraft/text/textformatting.h"

ChatText::ChatText() {}

void ChatText::paint(QPainter *painter) {
  TextFormatting::drawText(painter, text_, 1, 10, width() - 10);
}

QString ChatText::text() const { return text_; }

void ChatText::setText(const QString &text) {
  text_ = text;
  update();
}
