#include "authresponse.h"

#include <QDebug>

AuthResponse::AuthResponse() {}

void AuthResponse::FromJson(const QString &json) {
  Document doc;
  doc.Parse(json.toUtf8());
  if (doc.HasParseError()) {
    qInfo("Parse AuthResponse failed: %s, offset: %zu, raw: %s",
          GetParseError_En(doc.GetParseError()), doc.GetErrorOffset(),
          json.toStdString().c_str());
    return;
  }

  if (doc.IsObject()) {
    if (doc.HasMember("error")) {
      Value &v = doc["error"];
      if (v.IsString()) error_ = v.GetString();

      if (doc.HasMember("errorMessage")) {
        Value &v = doc["errorMessage"];
        if (v.IsString()) errorMessage_ = v.GetString();
      }

      if (doc.HasMember("cause")) {
        Value &v = doc["cause"];
        if (v.IsString()) cause_ = v.GetString();
      }

      return;
    }

    if (doc.HasMember("accessToken")) {
      Value &v = doc["accessToken"];
      if (v.IsString()) {
        accessToken_ = v.GetString();
      }
    }

    if (doc.HasMember("clientToken")) {
      Value &v = doc["clientToken"];
      if (v.IsString()) {
        clientToken_ = v.GetString();
      }
    }

    if (doc.HasMember("availableProfiles")) {
      Value &v = doc["availableProfiles"];
      if (v.IsArray()) {
        availableProfiles_.clear();
        for (SizeType i = 0; i < v.Size(); i++) {
          Value &profile = v[i];
          if (profile.IsObject()) {
            Profile p;
            if (profile.HasMember("name") && profile["name"].IsString())
              p.setName(profile["name"].GetString());

            if (profile.HasMember("id") && profile["id"].IsString())
              p.setId(profile["id"].GetString());

            availableProfiles_.append(p);
          }
        }
      }
    }

    if (doc.HasMember("selectedProfile")) {
      Value &v = doc["selectedProfile"];
      if (v.IsObject()) {
        if (v.HasMember("id") && v["id"].IsString())
          selectedProfile_.setId(v["id"].GetString());

        if (v.HasMember("name") && v["name"].IsString())
          selectedProfile_.setName(v["name"].GetString());
      }
    }

    if (doc.HasMember("user")) {
      Value &v = doc["user"];
      if (v.IsObject()) {
        if (v.HasMember("id") && v["id"].IsString())
          user_.id = v["id"].GetString();

        if (v.HasMember("username") && v["username"].IsString())
          user_.username = v["username"].GetString();
      }
    }
  }
}

QString AuthResponse::accessToken() const { return accessToken_; }
void AuthResponse::setAccessToken(const QString &accessToken) {
  accessToken_ = accessToken;
}

QString AuthResponse::clientToken() const { return clientToken_; }
void AuthResponse::setClientToken(const QString &clientToken) {
  clientToken_ = clientToken;
}

QList<Profile> AuthResponse::availableProfiles() const {
  return availableProfiles_;
}
void AuthResponse::setAvailableProfiles(
    const QList<Profile> &availableProfiles) {
  availableProfiles_ = availableProfiles;
}

Profile AuthResponse::selectedProfile() const { return selectedProfile_; }
void AuthResponse::setSelectedProfile(const Profile &selectedProfile) {
  selectedProfile_ = selectedProfile;
}

User AuthResponse::user() const { return user_; }
void AuthResponse::setUser(const User &user) { user_ = user; }

QString AuthResponse::error() const { return error_; }
void AuthResponse::setError(const QString &error) { error_ = error; }

QString AuthResponse::errorMessage() const { return errorMessage_; }
void AuthResponse::setErrorMessage(const QString &errorMessage) {
  errorMessage_ = errorMessage;
}

QString AuthResponse::cause() const { return cause_; }
void AuthResponse::setCause(const QString &cause) { cause_ = cause; }

Profile::Profile() {}
Profile::Profile(const QString &id, const QString &name)
    : id_(id), name_(name) {}

QString Profile::id() const { return id_; }
void Profile::setId(const QString &id) { id_ = id; }

QString Profile::name() const { return name_; }
void Profile::setName(const QString &name) { name_ = name; }
