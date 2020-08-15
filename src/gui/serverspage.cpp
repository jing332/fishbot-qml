#include "serverspage.h"

#include <QDebug>
#include <QThreadPool>

#include "runnables/pingserverrun.h"

ServersPage::ServersPage(AppState *appState, QObject *parent)
    : QObject(parent),
      appState_(appState),
      serversModel_(appState_->serversModel()) {
  connect(this, SIGNAL(modelDataChanged()), this, SLOT(onModelDataChanged()));

  connect(appState_, SIGNAL(addServer(QString, QString)), this,
          SLOT(onAddServer(QString, QString)));
  connect(appState_, SIGNAL(editServer(int, QString, QString)), this,
          SLOT(onEditServer(int, QString, QString)));

  serversModel_->append(
      ServerItemData("Miaoscraft", "play.miaoscraft.cn:25565"));
  serversModel_->append(ServerItemData("MC233", "mc233.cn:25565"));
  serversModel_->append(ServerItemData("Wincraft", "mc.windcraft.cn:25565"));
  serversModel_->append(ServerItemData("localhost", "localhost:25565"));
}

ServersPage::~ServersPage() {}

void ServersPage::setRootObject(QObject *root) {
  root_ = root;
  root->disconnect();
  /*连接QML信号*/
  connect(root_, SIGNAL(refreshServerStatus(int)), this,
          SLOT(onRefreshServerStatus(int)));
  connect(root_, SIGNAL(refreshAllServerStatus()), this,
          SLOT(onRefreshAllServerStatus()));
  connect(root_, SIGNAL(addServer(QString, QString)), this,
          SLOT(onAddServer(QString, QString)));
  connect(root_, SIGNAL(editServer(int, QString, QString)), this,
          SLOT(onEditServer(int, QString, QString)));
  connect(root_, SIGNAL(serverDoubleClicked(int)), this,
          SLOT(onServerDoubleClicked(int)));

  onModelDataChanged();
  onRefreshAllServerStatus();
}

ServerListModel *ServersPage::serversModel() const { return serversModel_; }

void ServersPage::setServersModel(ServerListModel *serversModel) {
  serversModel_ = serversModel;
  emit modelDataChanged();
}

void ServersPage::onModelDataChanged() {
  root_->setProperty("modelData", QVariant::fromValue(serversModel_));
}

void ServersPage::onRefreshServerStatus(int index) {
  serversModel_->at(index).setMotd("");
  serversModel_->at(index).setFavicon("");
  serversModel_->at(index).setDelay("");
  serversModel_->at(index).setOnlinePlayers("");
  serversModel_->updateItemData(index);

  auto run = new PingServerRun(index, serversModel_->at(index).address());
  connect(run, &PingServerRun::finished,
          [&](int index, ServerStatus status, int delay, const QString &error) {
            if (error.isEmpty()) {
              auto &itemData = serversModel_->at(index);

              itemData.setFavicon(status.GetFavicon());
              auto motd = status.GetDecription().GetFormattedText();
              itemData.setMotd(motd);

              QString delayTextColor;
              if (100 > delay) {
                delayTextColor = "green";
              } else if (200 > delay) {
                delayTextColor = "yellow";
              } else if (300 > delay) {
                delayTextColor = "red";
              } else {
                delayTextColor = "darkred";
              }
              itemData.setDelay(QStringLiteral("<font color='%1'>%2ms</font>")
                                    .arg(delayTextColor)
                                    .arg(delay));
              itemData.setOnlinePlayers(QStringLiteral("%1/%2")
                                            .arg(status.GetPlayers().online)
                                            .arg(status.GetPlayers().max));
              serversModel_->updateItemData(index);
            }
          });
  QThreadPool::globalInstance()->start(run);
}

void ServersPage::onRefreshAllServerStatus() {
  for (int i = 0; i < serversModel_->rowCount(); i++) {
    onRefreshServerStatus(i);
  }
}

void ServersPage::onAddServer(QString name, QString addr) {
  auto data = ServerItemData(name, addr);
  serversModel_->append(data);
  onRefreshServerStatus(serversModel_->rowCount() - 1);
}

void ServersPage::onEditServer(int index, QString name, QString addr) {
  serversModel_->at(index).setName(name);
  serversModel_->at(index).setAddress(addr);
  serversModel_->updateItemData(index);
  onRefreshServerStatus(index);
}

void ServersPage::onServerDoubleClicked(int index) {
  qDebug() << "onDoubleClicked" << index;
  auto server = serversModel_->at(index);
  auto account = appState_->accountsModel()->at(appState_->currentAccount());
  auto profile = account.accountInfo().selectedProfile();
  emit appState_->joinServer(server.name(), server.address(), profile.name(),
                             profile.id(), account.accountInfo().accessToken());
}
