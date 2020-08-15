#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QSharedData>

#include "chatcolor.h"
#include "event/clickevent.h"
#include "event/hoverevent.h"
#include "json/jsonhelper.h"

using namespace rapidjson;

class Style;

class StyleData : public QSharedData {
 public:
  StyleData();
  StyleData(const StyleData &data);
  ~StyleData();

  Style *parentStyle_ = nullptr;
  ChatColor color_ = NONE;
  bool bold_ = false;
  bool italic_ = false;
  bool underlined_ = false;
  bool strikethrough_ = false;
  bool obfuscated_ = false;
  ClickEvent clickEvent_;
  HoverEvent hoverEvent_;
  QString insertion_;
};

class Style : public JsonHelper {
 public:
  Style();
  Style(const Style &style);

  bool IsEmpty();

  bool HasHoverEvent();
  HoverEvent GetHoverEvent();
  void SetHoverEvent(HoverEvent hoverEnvet);

  bool HasClickEvent();
  ClickEvent GetClickEvent();
  void SetClickEvent(ClickEvent clickEvent);

  QString GetInsertion() const;
  void SetInsertion(const QString &s);

  bool HasColor();
  ChatColor GetColor() const;
  void SetColor(ChatColor color_);

  bool IsBold();
  void SetBold(bool b = true);

  bool IsItalic();
  void SetItalic(bool b = true);

  bool IsUnderlined();
  void SetUnderlined(bool b = true);

  bool IsStrikethrough();
  void SetStrikethrough(bool b = true);

  bool IsObfuscated();
  void SetObfuscated(bool b = true);

  Style *GetParentStyle() const;
  void SetParentStyle(Style *style);

  QString GetFormatingCode();

  void FromJson(const Value &v) override;
  //  static Style FromJson(const Value &v);
  //  void FromJson(const Value &json) override;

 private:
  QSharedDataPointer<StyleData> d_;
};

#endif  // STYLE_H
