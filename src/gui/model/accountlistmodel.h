#ifndef ACCOUNTLISTMODEL_H
#define ACCOUNTLISTMODEL_H

#include <QAbstractListModel>

#include "authserverlistmodel.h"
#include "minecraft/yggdrasil/yggdrasil.h"

class AccountItemData {
 public:
  AccountItemData();
  AccountItemData(AuthResponse authResp, bool select = false);
  AccountItemData(const QString &displayName, bool select = false);

  bool isSelected() const;
  void setIsSelected(bool isSelected);

  Yggdrasil::AccountType type() const;
  void setType(const Yggdrasil::AccountType &type);

  AuthResponse accountInfo() const;
  void setAccountInfo(const AuthResponse &accountInfo);

  //  AuthServerItemData authServer() const;
  //  void setAuthServer(const AuthServerItemData &authServer);

 private:
  bool isSelected_;
  Yggdrasil::AccountType type_;
  //  AuthServerItemData authServer_;
  AuthResponse accountInfo_;
};

class AccountListModel : public QAbstractListModel {
  Q_OBJECT
 public:
  enum AccountRoles {
    IsSelectedRole = Qt::UserRole + 1,
    UserNameRole,
    DisplayNameRole,
    TypeRole
  };

  AccountListModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &index = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  Q_INVOKABLE void insert(int index, const AccountItemData &data);
  Q_INVOKABLE void append(const AccountItemData &data);
  Q_INVOKABLE void remove(int index);

  AccountItemData &at(int index);
  void updateItemData(int index);
  void updateItemDatas(int top, int bottom);

 protected:
  QHash<int, QByteArray> roleNames() const;

 signals:
  void countChanged(int arg);

 private:
  QList<AccountItemData> datas_;
};

#endif  // ACCOUNTLISTMODEL_H
