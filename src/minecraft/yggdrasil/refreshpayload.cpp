#include "refreshpayload.h"

RefreshPayload::RefreshPayload(AuthResponse authResp)
    : accessToken_(authResp.accessToken()),
      clientToken_(authResp.clientToken()),
      selectedProfile_(authResp.selectedProfile()) {}

RefreshPayload::RefreshPayload(const QString &accessToken,
                               const QString &clientToken,
                               const Profile &selectedProfile, bool requestUser)
    : accessToken_(accessToken),
      clientToken_(clientToken),
      selectedProfile_(selectedProfile),
      requestUser_(requestUser) {}

QString RefreshPayload::ToJson() const {
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  writer.StartObject();
  writer.Key("accessToken");
  writer.String(accessToken_.toUtf8());

  writer.Key("clientToken");
  writer.String(clientToken_.toUtf8());

  writer.Key("selectedProfile");
  writer.StartObject();
  writer.Key("id");
  writer.String(selectedProfile_.id().toUtf8());

  writer.Key("name");
  writer.String(selectedProfile_.name().toUtf8());
  writer.EndObject();

  writer.Key("requestUser");
  writer.Bool(requestUser_);
  writer.EndObject();

  return buffer.GetString();
}

QString RefreshPayload::GetAccessToken() const { return accessToken_; }
void RefreshPayload::SetAccessToken(const QString &accessToken) {
  accessToken_ = accessToken;
}

QString RefreshPayload::GetClientToken() const { return clientToken_; }
void RefreshPayload::SetClientToken(const QString &clientToken) {
  clientToken_ = clientToken;
}

Profile RefreshPayload::GetSelectedProfile() const { return selectedProfile_; }
void RefreshPayload::SetSelectedProfile(const Profile &selectedProfile) {
  selectedProfile_ = selectedProfile;
}

bool RefreshPayload::GetRequestUser() const { return requestUser_; }
void RefreshPayload::SetRequestUser(bool requestUser) {
  requestUser_ = requestUser;
}
