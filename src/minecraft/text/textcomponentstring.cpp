#include "textcomponentstring.h"

#include <QDebug>

TextComponentString::TextComponentString() {}

TextComponentString::TextComponentString(const QString& msg) { text = msg; }

bool TextComponentString::IsStringText() {
  if (!text.isEmpty() && GetSiblings().isEmpty()) return true;
  return false;
}

bool TextComponentString::IsStringType() { return true; }

QString TextComponentString::GetText() { return text; }

QString TextComponentString::GetUnformattedComponentText() { return text; }
