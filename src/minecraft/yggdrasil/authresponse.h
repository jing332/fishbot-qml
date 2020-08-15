#ifndef AUTHRESPONSE_H
#define AUTHRESPONSE_H

#include <QMetaType>

#include "json/jsonhelper.h"

class Profile {
 public:
  Profile();
  Profile(const QString &id, const QString &name);

  QString id() const;
  void setId(const QString &id);

  QString name() const;
  void setName(const QString &name);

 private:
  QString id_;
  QString name_;
};

typedef struct {
  QString name;
  QString value;
} Property;

typedef struct {
  QString id;
  QString username;
  QList<Property> Properties;
} User;

class AuthResponse : public JsonHelper {
 public:
  AuthResponse();

  void FromJson(const QString &json) override;

  QString accessToken() const;
  void setAccessToken(const QString &accessToken);

  QString clientToken() const;
  void setClientToken(const QString &clientToken);

  QList<Profile> availableProfiles() const;
  void setAvailableProfiles(const QList<Profile> &availableProfiles);

  Profile selectedProfile() const;
  void setSelectedProfile(const Profile &selectedProfile);

  User user() const;
  void setUser(const User &user);

  QString error() const;
  void setError(const QString &error);

  QString errorMessage() const;
  void setErrorMessage(const QString &errorMessage);

  QString cause() const;
  void setCause(const QString &cause);

 private:
  QString accessToken_;
  QString clientToken_;
  QList<Profile> availableProfiles_;
  Profile selectedProfile_;
  User user_;
  QString type_;

  QString error_;
  QString errorMessage_;
  QString cause_;
};

#endif  // AUTHRESPONSE_H
