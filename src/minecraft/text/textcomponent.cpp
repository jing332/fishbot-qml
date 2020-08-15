#include "textcomponent.h"

#include <rapidjson/error/en.h>

#include <QDebug>

#include "textcomponentstring.h"
#include "textcomponenttranslation.h"

TextComponent::TextComponent() {}
TextComponent::~TextComponent() {}

bool TextComponent::IsStringText() { return false; }
bool TextComponent::IsStringType() { return false; }

void TextComponent::SetStyle(Style) {}
Style &TextComponent::GetStyle() {}

TextComponent *TextComponent::AppendText(const QString &) {
  Q_ASSERT("type error");
  return nullptr;
}
TextComponent *TextComponent::AppendSibling(TextComponent *) {
  Q_ASSERT("type error");
  return nullptr;
}

QList<TextComponent *> TextComponent::GetSiblings() const {
  Q_ASSERT("type error");
  return QList<TextComponent *>();
}

QList<TextComponent *> TextComponent::GetList() {
  QList<TextComponent *> list;
  list.append(this);
  list.append(GetSiblings());
  return list;
}

QString TextComponent::GetUnformattedText() {
  Q_ASSERT("type error");
  return "";
}

QString TextComponent::GetUnformattedComponentText() {
  Q_ASSERT("type error");
  return "";
}

QString TextComponent::GetFormattedText() {
  Q_ASSERT("type error");
  return "";
}

TextComponent *TextComponent::FromJson(const Value &v) {
  if (v.IsString()) {
    return new TextComponentString(v.GetString());
  } else if (!v.IsObject()) {
    if (v.IsArray()) {
      TextComponent *text = nullptr;
      for (SizeType i = 0; i < v.Size(); i++) {
        TextComponent *text2 = this->FromJson(v[i]);
        if (!text)
          text = text2;
        else
          text->AppendSibling(text2);
      }
      return text;
    } else
      qWarning() << "Don't know how to turn" << &v << "into a Component";
  } else {  // IsObject
    TextComponent *text = nullptr;
    if (v.HasMember("text")) {
      text = new TextComponentString(v["text"].GetString());
    } else if (v.HasMember("translate")) {
      QList<TextComponent *> args;
      if (v.HasMember("with")) {
        auto &array = v["with"];
        for (SizeType i = 0; i < array.Size(); i++) {
          args.append(this->FromJson(array[i]));
        }
      }
      text = new TextComponentTranslation(v["translate"].GetString(), args);
    }

    if (v.HasMember("extra")) {
      auto &array = v["extra"];
      for (SizeType i = 0; i < array.Size(); i++) {
        text->AppendSibling(this->FromJson(array[i]));
      }
    }

    Style style;
    style.FromJson(v);
    text->SetStyle(style);
    return text;
  }

  return nullptr;
}

TextComponent *TextComponent::FromString(const QString &json) {
  Document doc;
  doc.Parse(json.toStdString().c_str());
  if (doc.HasParseError()) {
    qWarning() << "parse jsonChat fail:"
               << GetParseError_En(doc.GetParseError())
               << ", position:" << doc.GetErrorOffset();
    return nullptr;
  } else {
    return FromJson(doc);
  }
}

TextComponent *TextComponent::NewTextFromJsonString(const QString &json) {
  TextComponent text;
  return text.FromString(json);
}

TextComponent *TextComponent::NewTextFromJsonValue(const Value &v) {
  TextComponent text;
  return text.FromJson(v);
}
