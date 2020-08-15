#ifndef AUTHPAYLOAD_H
#define AUTHPAYLOAD_H

#include "json/jsonhelper.h"

class Agent {
 public:
  Agent();
  QString GetName() const;
  QString SetName(const QString &name);

  int GetVersion() const;
  void SetVersioon(int ver);

 private:
  QString name_ = "Minecraft";
  int version_ = 1;
};

class AuthPayload : public JsonHelper {
 public:
  AuthPayload();
  AuthPayload(const QString &username, const QString &password,
              const QString clientToken, bool requestUser = true);

  QString ToJson() const override;

  Agent GetAgent() const;
  void SetAgent(const Agent &agent);

  QString GetUsername() const;
  void SetUsername(const QString &username);

  QString GetPassword() const;
  void SetPassword(const QString &password);

  QString GetClientToken() const;
  void SetClientToken(const QString &clientToken);

  bool GetRequestUser() const;
  void SetRequestUser(bool requestUser);

 private:
  Agent agent_;
  QString username_;
  QString password_;
  QString clientToken_;
  bool requestUser_;
};

#endif  // AUTHPAYLOAD_H
