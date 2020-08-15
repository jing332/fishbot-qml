#ifndef APPSTATE_H
#define APPSTATE_H

#include <QObject>

#include "model/accountlistmodel.h"
#include "model/authserverlistmodel.h"
#include "model/serverlistmodel.h"

class AppState : public QObject {
  Q_OBJECT
 public:
  explicit AppState(QObject *parent = nullptr);
  ~AppState();

  AccountListModel *accountsModel() const;
  void setAccountsModel(AccountListModel *accountsModel);

  ServerListModel *serversModel() const;
  void setServersModel(ServerListModel *serversModel);

  AuthServerListModel *authServersModel() const;
  void setAuthServersModel(AuthServerListModel *authServersModel);

  int currentAccount() const;
  void setCurrentAccount(int index);

 signals:
  void addServer(const QString &name, const QString &addr);
  void editServer(int index, const QString &name, const QString &addr);
  void addAccount(const QString &username, const QString &password);

  void joinServer(const QString &serverName, const QString &serverAddr,
                  const QString &name, const QString &uuid,
                  const QString &accessToken,
                  const QString &sessionUrl = Yggdrasil::kMojangSessionURL);

 private:
  ServerListModel *serversModel_;

  AccountListModel *accountsModel_;
  int currentAccount_;

  AuthServerListModel *authServersModel_;
};

#endif  // APPSTATE_H
