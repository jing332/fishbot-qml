#ifndef ACCOUNTSPAGE_H
#define ACCOUNTSPAGE_H

#include <QObject>

#include "appstate.h"
#include "model/accountlistmodel.h"

class AccountsPage : public QObject {
  Q_OBJECT
  Q_PROPERTY(AccountListModel *modelData READ modelData WRITE setModelData
                 NOTIFY modelDataChanged)
  Q_PROPERTY(int currentAccount READ currentAccount WRITE setCurrentAccount
                 NOTIFY currentAccountChanged)
 public:
  AccountsPage(AppState *appState, QObject *parent = nullptr);

  void setRootObject(QObject *root);

  AccountListModel *modelData() const;
  void setModelData(AccountListModel *accountsModel);

  int currentAccount() const;
  void setCurrentAccount(int index);

 signals:
  void modelDataChanged();
  void currentAccountChanged();

  void addAccountFinished(const QString &error = QString());

 private slots:
  void onModelDataChanged();
  void onCurrentAccountChanged();
  void onSetCurrentAccount(int index);
  void onAddAccount(const QString &username, const QString &password);

 private:
  QObject *root_;
  AppState *appState_;
  AccountListModel *accountsModel_;
};

#endif  // ACCOUNTSPAGE_H
