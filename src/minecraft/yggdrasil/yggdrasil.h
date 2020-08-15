#ifndef YGGDRASIL_H
#define YGGDRASIL_H

#include <QRunnable>
#include <QUuid>

#include "authresponse.h"
#include "refreshpayload.h"
#include "validatepayload.h"

class Yggdrasil : public QObject {
  Q_OBJECT
 public:
  /*账户类型(正版, 外置, 离线)*/
  enum AccountType { YggdrasilType = 0x0, AuthlibInjectorType, OfflineType };

  Yggdrasil();
  ~Yggdrasil();
  /*使用邮箱与密码认证账户*/
  void Authenticate(
      const QString &username, const QString &password,
      const QString &clientToken = QUuid::createUuid().toString(QUuid::Id128));
  /*检查账户Token是否有效*/
  void Validate(ValidatePayload payload);
  /*刷新账户/选择账户角色*/
  void Refresh(RefreshPayload payload);
  /*设置外置认证服务器地址*/
  void SetBaseURL(const QString &url = QString());

  static QString FormatProfileURL(const QString &uuid);
  static QString FormatProfileURL(const QString &authURL, const QString &uuid);

  /*Mojang认证服务器地址*/
  static const QString kMojangAuthURL;
  /*Mojang会话服务器地址*/
  static const QString kMojangSessionURL;

 private:
  QString baseURL_;
  QString authServer_;
  QString authURL_;
  QString refreshURL_;
  QString validateURL_;
  QString sessionServer_;

 signals:
  void authFinished(AuthResponse, QString requestError = "");
  void validateFinished(bool);
  void refreshFinished(AuthResponse);
};

#endif  // YGGDRASIL_H
