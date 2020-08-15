#include "style.h"

#include "minecraft/text/textcomponentstring.h"

Style::Style() { d_ = new StyleData(); }
Style::Style(const Style &style) : d_(style.d_) {}

bool Style::IsEmpty() {
  return d_->insertion_.isEmpty() && !d_->bold_ && !d_->italic_ &&
         !d_->strikethrough_ && !d_->underlined_ && !d_->obfuscated_ &&
         d_->color_ == NONE && d_->clickEvent_.IsEmpty() &&
         d_->hoverEvent_.IsEmpty();
}

bool Style::HasHoverEvent() { return !d_->hoverEvent_.IsEmpty(); }
HoverEvent Style::GetHoverEvent() { return d_->hoverEvent_; }
void Style::SetHoverEvent(HoverEvent hoverEnvet) {
  d_->hoverEvent_ = hoverEnvet;
}

bool Style::HasClickEvent() { return !d_->clickEvent_.IsEmpty(); }
ClickEvent Style::GetClickEvent() { return d_->clickEvent_; }
void Style::SetClickEvent(ClickEvent clickEvent) {
  d_->clickEvent_ = clickEvent;
}

QString Style::GetInsertion() const { return d_->insertion_; }
void Style::SetInsertion(const QString &s) { d_->insertion_ = s; }

bool Style::HasColor() {
  if (d_->color_ == NONE) return false;
  return true;
}
ChatColor Style::GetColor() const { return d_->color_; }
void Style::SetColor(ChatColor color) { d_->color_ = color; }

bool Style::IsBold() { return d_->bold_; }
void Style::SetBold(bool b) { d_->bold_ = b; }

bool Style::IsItalic() { return d_->italic_; }
void Style::SetItalic(bool b) { d_->italic_ = b; }

bool Style::IsUnderlined() { return d_->underlined_; }
void Style::SetUnderlined(bool b) { d_->underlined_ = b; }

bool Style::IsStrikethrough() { return d_->strikethrough_; }
void Style::SetStrikethrough(bool b) { d_->strikethrough_ = b; }

bool Style::IsObfuscated() { return d_->obfuscated_; }
void Style::SetObfuscated(bool b) { d_->obfuscated_ = b; }

Style *Style::GetParentStyle() const { return d_->parentStyle_; }
void Style::SetParentStyle(Style *style) { d_->parentStyle_ = style; }

QString Style::GetFormatingCode() {
  if (IsEmpty()) {
    return d_->parentStyle_ ? d_->parentStyle_->GetFormatingCode() : "";
  } else {
    QString format;
    if (HasColor())
      format.append(
          QStringLiteral("§").append(ChatColorUtils::getCode(d_->color_)));

    if (IsBold()) format.append("§l");
    if (IsItalic()) format.append("§o");
    if (IsUnderlined()) format.append("§n");
    if (IsObfuscated()) format.append("§k");
    if (IsStrikethrough()) format.append("§m");

    return format;
  }
}

void Style::FromJson(const Value &v) {
  if (v.IsObject()) {
    if (v.HasMember("bold")) SetBold(JsonHelper::GetBool(v["bold"]));
    if (v.HasMember("italic")) SetItalic(JsonHelper::GetBool(v["italic"]));
    if (v.HasMember("underlined"))
      SetUnderlined(JsonHelper::GetBool(v["underlined"]));

    if (v.HasMember("strikethrough"))
      SetStrikethrough(JsonHelper::GetBool(v["strikethrough"]));

    if (v.HasMember("obfuscated"))
      SetObfuscated(JsonHelper::GetBool(v["obfuscated"]));

    if (v.HasMember("color") && v["color"].IsString())
      SetColor(ChatColorUtils::byName(v["color"].GetString()));

    if (v.HasMember("insertion") && v["insertion"].IsString())
      SetInsertion(v["insertion"].GetString());

    if (v.HasMember("clickEvent")) {
      auto &obj = v["clickEvent"];
      if (obj.HasMember("action") && obj["action"].IsString()) {
        ClickAction action =
            ClickActionUtils::ByName(obj["action"].GetString());
        QString value = obj.HasMember("value") && obj["value"].IsString()
                            ? obj["value"].GetString()
                            : "";

        if (!value.isEmpty() && action != CLICK_NONE)
          SetClickEvent(ClickEvent(action, value));
      }
    }

    if (v.HasMember("hoverEvent")) {
      auto &obj = v["hoverEvent"];
      if (obj.HasMember("action")) {
        HoverAction action =
            HoverActionUtils::byName(obj["action"].GetString());

        if (obj.HasMember("value")) {
          if (obj["value"].IsObject() || obj["value"].IsArray()) {
            TextComponent *value =
                TextComponent::NewTextFromJsonValue(obj["value"]);
            if (action != HOVER_NONE && value)
              SetHoverEvent(HoverEvent(action, value));

          } else if (obj["value"].IsString())
            SetHoverEvent(HoverEvent(
                action, new TextComponentString(obj["value"].GetString())));
        }
      }
    }
  }
}

StyleData::StyleData() {}
StyleData::StyleData(const StyleData &data)
    : QSharedData(data),
      parentStyle_(data.parentStyle_),
      color_(data.color_),
      bold_(data.bold_),
      italic_(data.italic_),
      underlined_(data.underlined_),
      strikethrough_(data.strikethrough_),
      obfuscated_(data.obfuscated_),
      clickEvent_(data.clickEvent_),
      hoverEvent_(data.hoverEvent_),
      insertion_(data.insertion_) {}

StyleData::~StyleData() {}
