#include "textcomponenttranslation.h"

#include <QDebug>

#include "translation/languagemap.h"

const QRegularExpression TextComponentTranslation::kRegExp(
    "%(?:(\\d+)\\$)?([A-Za-z%]|$)");

TextComponentTranslation::TextComponentTranslation(
    const QString &translationKey, QList<TextComponent *> args)
    : key_(translationKey), formatArgs_(args) {
  for (auto &t : formatArgs_) {
    t->GetStyle().SetParentStyle(&GetStyle());
  }

  /*将翻译文本中的占位符替换为参数*/
  this->FromFormat(LanguageMap::kLanguageList[key_]);
}

/*格式化文本中的占位符%*/
void TextComponentTranslation::FromFormat(const QString &format) {
  auto match = kRegExp.match(format);

  int i = -1;
  int end;
  int lastEnd = 0;
  for (; match.hasMatch(); lastEnd = end) {
    int start = match.capturedStart();
    end = match.capturedEnd();

    //非占位符
    if (start > lastEnd) {
      auto textString =
          new TextComponentString(format.mid(lastEnd, start - lastEnd));
      textString->GetStyle().SetParentStyle(&GetStyle());
      this->children_.append(textString);
    }

    /*{A-Za-z}*/
    QString str2 = match.captured(2);
    /*%{A-Za-z}*/
    QString str = format.mid(start, end - start);

    if (str2 == "%" && str == "%%") {
      auto textString = new TextComponentString("%");
      textString->GetStyle().SetParentStyle(&GetStyle());
      this->children_.append(textString);
    } else {
      if (str2 != "s") {
        qWarning() << "Unsupported format:" << str;
        return;
      }

      QString number = match.captured(1); /*number{0: %, 1: \d+, 2: $}*/
      /*int argIndex = */ !number.isEmpty() && number.size() <= 2
          ? QString(number.at(1)).toInt()
          : i++;
      if (i < this->formatArgs_.size())
        this->children_.append(this->GetComponentByArgIndex(i));
    }

    match = kRegExp.match(format, end);
  }

  if (lastEnd < format.size()) {
    auto textString =
        new TextComponentString(format.right(format.size() - lastEnd));
    textString->GetStyle().SetParentStyle(&GetStyle());
    this->children_.append(textString);
  }
}

TextComponent *TextComponentTranslation::GetComponentByArgIndex(int index) {
  auto arg = formatArgs_.at(index);
  if (arg->IsStringText()) {
    arg->GetStyle().SetParentStyle(&GetStyle());
  }

  return arg;
}

QString TextComponentTranslation::GetUnformattedComponentText() {
  QString str;
  for (auto &text : this->children_) {
    str.append(text->GetUnformattedComponentText());
  }
  return str;
}

QList<TextComponent *> TextComponentTranslation::GetList() {
  return this->children_;
}
