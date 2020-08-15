#ifndef REFRESHPAYLOAD_H
#define REFRESHPAYLOAD_H

#include "authresponse.h"
#include "json/jsonhelper.h"

class RefreshPayload : public JsonHelper {
 public:
  RefreshPayload();
  RefreshPayload(AuthResponse authResp);
  RefreshPayload(const QString &accessToken, const QString &clientToken,
                 const Profile &selectedProfile, bool requestUser = true);

  QString ToJson() const override;

  QString GetAccessToken() const;
  void SetAccessToken(const QString &accessToken);

  QString GetClientToken() const;
  void SetClientToken(const QString &clientToken);

  Profile GetSelectedProfile() const;
  void SetSelectedProfile(const Profile &selectedProfile);

  bool GetRequestUser() const;
  void SetRequestUser(bool requestUser);

 private:
  QString accessToken_;
  QString clientToken_;
  Profile selectedProfile_;
  bool requestUser_ = true;
};

#endif  // REFRESHPAYLOAD_H
