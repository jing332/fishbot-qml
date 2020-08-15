#include "textcomponentbase.h"

#include <QDebug>

#include "textcomponentstring.h"

TextComponentBase::TextComponentBase() {}

TextComponent *TextComponentBase::AppendSibling(TextComponent *text) {
  text->GetStyle().SetParentStyle(&GetStyle());
  siblings_.append(text);
  return this;
}

QList<TextComponent *> TextComponentBase::GetSiblings() const {
  return siblings_;
}

TextComponent *TextComponentBase::AppendText(const QString &text) {
  return AppendSibling(new TextComponentString(text));
}

void TextComponentBase::SetStyle(Style style) {
  style_ = style;
  for (auto &text : siblings_) {
    text->GetStyle().SetParentStyle(&GetStyle());
  }
}

Style &TextComponentBase::GetStyle() {
  if (style_.IsEmpty()) {
    for (auto &text : siblings_) {
      text->GetStyle().SetParentStyle(&style_);
    }
  }

  return style_;
}

QString TextComponentBase::GetUnformattedText() {
  QString str;
  for (auto &text : GetList()) {
    str.append(text->GetUnformattedComponentText());
  }

  return str;
}

QString TextComponentBase::GetFormattedText() {
  QString str;
  for (auto &text : GetList()) {
    QString s = text->GetUnformattedComponentText();
    if (!s.isEmpty()) {
      str.append(text->GetStyle().GetFormatingCode());
      str.append(s);
      str.append("§r");
    }
  }

  return str;
}
