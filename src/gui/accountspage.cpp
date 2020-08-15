#include "accountspage.h"

#include <QDebug>

AccountsPage::AccountsPage(AppState *appState, QObject *parent)
    : QObject(parent),
      appState_(appState),
      accountsModel_(appState_->accountsModel()) {
  connect(this, SIGNAL(modelDataChanged()), this, SLOT(onModelDataChanged()));
  connect(this, SIGNAL(currentAccountChanged()), this,
          SLOT(onCurrentAccountChanged()));

  connect(appState_, SIGNAL(addAccount(QString, QString)), this,
          SLOT(onAddAccount(QString, QString)));

  accountsModel_->append(AccountItemData("Steve"));
  accountsModel_->append(AccountItemData("Alex"));
}

void AccountsPage::setRootObject(QObject *root) {
  root_ = root;
  root_->disconnect();

  connect(root_, SIGNAL(setCurrentAccount(int)), this,
          SLOT(onSetCurrentAccount(int)));
  connect(root_, SIGNAL(addAccount(QString, QString)), this,
          SLOT(onAddAccount(QString, QString)));
  connect(this, SIGNAL(addAccountFinished(QString)), root_,
          SIGNAL(addAccountFinished(QString)));

  setCurrentAccount(0);
  emit onModelDataChanged();
}

void AccountsPage::onModelDataChanged() {
  root_->setProperty("modelData", QVariant::fromValue(accountsModel_));
}

void AccountsPage::onCurrentAccountChanged() {
  root_->setProperty("currentAccount", currentAccount());
}

void AccountsPage::onSetCurrentAccount(int index) { setCurrentAccount(index); }

void AccountsPage::onAddAccount(const QString &username,
                                const QString &password) {
  if (password.isEmpty()) {
    accountsModel_->append(AccountItemData(username, true));
    setCurrentAccount(accountsModel_->rowCount() - 1);
    emit addAccountFinished();
  } else {
    Yggdrasil *ygg = new Yggdrasil();
    connect(
        ygg, &Yggdrasil::authFinished, this,
        [&](AuthResponse authResp, const QString &requestError) {
          if (requestError.isEmpty()) {
            if (authResp.error().isEmpty()) {
              qInfo() << QStringLiteral("Account authentication succeeded: %1")
                             .arg(authResp.selectedProfile().name());
              accountsModel_->append(AccountItemData(authResp, true));
              setCurrentAccount(accountsModel_->rowCount() - 1);
              emit addAccountFinished();
            } else { /*验证失败*/
              qInfo() << QStringLiteral("Account authenticate failed: %1, %2")
                             .arg(authResp.error(), authResp.errorMessage());
              emit addAccountFinished(authResp.errorMessage());
            }
          } else { /*网络错误*/
            qInfo() << QStringLiteral("Account authenticate failed: %1")
                           .arg(requestError);
            emit addAccountFinished(requestError);
          }
        });

    ygg->Authenticate(username, password);
  }
}

AccountListModel *AccountsPage::modelData() const { return accountsModel_; }
void AccountsPage::setModelData(AccountListModel *accountsModel) {
  accountsModel_ = accountsModel;
  emit onModelDataChanged();
}

int AccountsPage::currentAccount() const { return appState_->currentAccount(); }
void AccountsPage::setCurrentAccount(int index) {
  appState_->setCurrentAccount(index);
  emit currentAccountChanged();
}
