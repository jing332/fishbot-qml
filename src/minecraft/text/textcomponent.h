#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include <QList>
#include <QObject>

#include "chatcolor.h"
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"
#include "style.h"

using namespace rapidjson;

class TextComponent {
 public:
  TextComponent();
  virtual ~TextComponent();
  virtual bool IsStringText();
  virtual bool IsStringType();

  virtual void SetStyle(Style style);
  virtual Style& GetStyle();

  virtual TextComponent* AppendText(const QString& text);
  virtual TextComponent* AppendSibling(TextComponent* text);
  virtual QList<TextComponent*> GetSiblings() const;
  virtual QList<TextComponent*> GetList();

  //在TextComponentTranslation中函数将返回 {text}
  virtual QString GetUnformattedComponentText();

  //所有TextComponent的文本
  virtual QString GetUnformattedText();
  virtual QString GetFormattedText();

  virtual TextComponent* FromJson(const Value& v);
  virtual TextComponent* FromString(const QString& json);

  static TextComponent* NewTextFromJsonString(const QString& json);
  static TextComponent* NewTextFromJsonValue(const Value& v);
};

#endif  // TEXTCOMPONENT_H
