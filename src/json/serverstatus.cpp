#include "serverstatus.h"

#include <QRegularExpression>

ServerStatus::ServerStatus() {}

TextComponentString ServerStatus::GetDecription() const { return description_; }
void ServerStatus::SetDescription(TextComponentString description) {
  description_ = description;
}

QString ServerStatus::GetFavicon() const { return favicon_; }
void ServerStatus::SetFavicon(const QString &favicon) {
  /*去除前缀: data:image/png;base64,*/
  favicon_ = favicon.split(",")[1];
}

Players ServerStatus::GetPlayers() const { return players_; }
void ServerStatus::SetPlayers(Players players) { players_ = players; }

Version ServerStatus::GetVersion() const { return version_; }
void ServerStatus::SetVersion(Version version) { version_ = version; }

void ServerStatus::FromJson(const QString &json) {
  Document doc;
  doc.Parse(json.toUtf8());

  if (doc.IsObject()) {
    auto obj = doc.GetObject();
    if (obj.HasMember("description")) {
      description_ = *static_cast<TextComponentString *>(
          TextComponent::NewTextFromJsonValue(obj["description"]));
    }

    if (obj.HasMember("favicon") && obj["favicon"].IsString()) {
      SetFavicon(obj["favicon"].GetString());
    }

    if (obj.HasMember("players")) {
      auto &pObj = obj["players"];
      if (pObj.HasMember("max") && pObj["max"].IsInt()) {
        players_.max = pObj["max"].GetInt();
      }
      if (pObj.HasMember("online") && pObj["online"].IsInt()) {
        players_.online = pObj["online"].GetInt();
      }
      if (pObj.HasMember("sample") && pObj["sample"].IsArray()) {
        auto list = pObj["sample"].GetArray();
        for (SizeType i = 0; i < list.Size(); i++) {
          auto &v = list[i];
          Sample sample;
          if (v.HasMember("id") && v["id"].IsString()) {
            sample.id = v["id"].GetString();
          }
          if (v.HasMember("name") && v["name"].IsString()) {
            sample.name = v["name"].GetString();
          }
          players_.sample.append(sample);
        }
      }
    }

    if (obj.HasMember("version") && obj["version"].IsObject()) {
      auto &v = obj["version"];
      Version ver;
      if (v.HasMember("name") && v["name"].IsString()) {
        ver.name = v["name"].GetString();
      }
      if (v.HasMember("protocol") && v["protocol"].IsInt()) {
        ver.protocol = v["protocol"].GetInt();
      }
      version_ = ver;
    }
  }
}
