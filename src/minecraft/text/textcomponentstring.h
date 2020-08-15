#ifndef TEXTCOMPONENTSTRING_H
#define TEXTCOMPONENTSTRING_H

#include <QObject>

#include "textcomponentbase.h"

class TextComponentString : public TextComponentBase {
  QString text;

 public:
  TextComponentString();
  TextComponentString(const QString &msg);
  bool IsStringText() override;
  bool IsStringType() override;
  QString GetText();
  QString GetUnformattedComponentText() override;
};

#endif  // TEXTCOMPONENTSTRING_H
