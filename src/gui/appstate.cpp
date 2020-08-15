#include "appstate.h"

AppState::AppState(QObject *parent)
    : QObject(parent),
      serversModel_(new ServerListModel(this)),
      accountsModel_(new AccountListModel(this)),
      currentAccount_(-1),
      authServersModel_(new AuthServerListModel(this)) {}

AppState::~AppState() {}

AccountListModel *AppState::accountsModel() const { return accountsModel_; }
void AppState::setAccountsModel(AccountListModel *accountsModel) {
  accountsModel_ = accountsModel;
}

ServerListModel *AppState::serversModel() const { return serversModel_; }
void AppState::setServersModel(ServerListModel *serversModel) {
  serversModel_ = serversModel;
}

AuthServerListModel *AppState::authServersModel() const {
  return authServersModel_;
}
void AppState::setAuthServersModel(AuthServerListModel *authServersModel) {
  authServersModel_ = authServersModel;
}

int AppState::currentAccount() const { return currentAccount_; }
void AppState::setCurrentAccount(int index) {
  currentAccount_ = index;
  if (index < accountsModel_->rowCount()) {
    for (int i = 0; i < accountsModel_->rowCount(); i++) {
      if (accountsModel_->at(i).isSelected()) {
        accountsModel_->at(i).setIsSelected(false);
        accountsModel_->updateItemData(i);
        break;
      }
    }
    accountsModel_->at(index).setIsSelected(true);
    accountsModel_->updateItemData(index);
  }
}
