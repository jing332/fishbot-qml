#ifndef TEXTCOMPONENTTRANSLATION_H
#define TEXTCOMPONENTTRANSLATION_H

#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "textcomponentstring.h"

class TextComponentTranslation : public TextComponentBase {
 public:
  TextComponentTranslation(
      const QString &translationKey,
      QList<TextComponent *> args = QList<TextComponent *>());

  TextComponent *GetComponentByArgIndex(int index);
  QString GetUnformattedComponentText() override;
  QList<TextComponent *> GetList() override;

  void FromFormat(const QString &format);

 private:
  QString key_;
  QList<TextComponent *> formatArgs_;
  QList<TextComponent *> children_;
  const static QRegularExpression kRegExp;
};

#endif  // TEXTCOMPONENTTRANSLATION_H
