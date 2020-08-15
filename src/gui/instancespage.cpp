#include "instancespage.h"

#include <QDebug>
#include <QQuickItem>
#include <QThreadPool>
#include <QTimer>

#include "fishbot.h"
#include "minecraft/text/translation/languagemap.h"

InstancesPage *InstancesPage::kSelf = nullptr;

void InstancesPage::onGameStart(const char *addr) {
  qDebug() << "Game start:" << addr;
  auto instancePage = kSelf->instancePages().value(addr);
  emit kSelf->addTabPage(instancePage->serverName(), addr, instancePage);
}

void InstancesPage::onChatMsg(const char *addr, const char *jsonMsg) {
  emit kSelf->instancePages().value(addr)->appendChatLine(jsonMsg);
}

void InstancesPage::onDisconnect(const char *addr, const char *reason) {
  qDebug() << "Disconnect:" << addr << reason;
  emit kSelf->closeTab(addr);
}

InstancesPage::InstancesPage(AppState *appState, QObject *parent)
    : QObject(parent), appState_(appState) {
  InstancesPage::kSelf = this;
  CgoRegGameStartCallback(onGameStart);
  CgoRegChatMsgCallback(onChatMsg);
  CgoRegDisconnectCallback(onDisconnect);

  connect(
      appState,
      SIGNAL(joinServer(QString, QString, QString, QString, QString, QString)),
      this,
      SLOT(onJoinServer(QString, QString, QString, QString, QString, QString)));

  connect(this, SIGNAL(addTabPage(QString, QString, NewInstancePage *)), this,
          SLOT(onAddTabPage(QString, QString, NewInstancePage *)),
          Qt::BlockingQueuedConnection);

  QFile file("://zh_cn.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  LanguageMap::fromJson(file.readAll());
  file.close();
}

void InstancesPage::setRootObject(QObject *root) { root_ = root; }

void InstancesPage::onAddTabPage(const QString &name, const QString &addr,
                                 NewInstancePage *instancePage) {
  Q_UNUSED(addr)
  QVariant count;
  QMetaObject::invokeMethod(root_, "addTabPage", Q_RETURN_ARG(QVariant, count),
                            Q_ARG(QVariant, name), Q_ARG(QVariant, addr));
  /*Integrating QML and C++*/
  auto *page =
      root_->findChild<QObject *>("stackLayout")->findChild<QObject *>(addr);
  instancePage->setRootObject(page);
}

void InstancesPage::onCloseTab(const QString &addr) {
  QMetaObject::invokeMethod(root_, "closeTabPage", Q_ARG(QVariant, addr));
  instancePages_[addr]->deleteLater();
  instancePages_.remove(addr);
}

void InstancesPage::onJoinServer(const QString &serverName,
                                 const QString &serverAddr, const QString &name,
                                 const QString &uuid,
                                 const QString &accessToken,
                                 const QString &sessionUrl) {
  auto runnable =
      new McClientRun(serverAddr, name, uuid, accessToken, sessionUrl);
  connect(runnable, &McClientRun::error, this, [=](const QString &reason) {
    qWarning() << reason;
    instancePages_.remove(serverAddr);
  });
  auto instancePage = new NewInstancePage(serverName, serverAddr, this);
  instancePage->setClient(runnable);
  instancePages_.insert(serverAddr, instancePage);

  QThreadPool::globalInstance()->start(runnable);
}

QMap<QString, NewInstancePage *> InstancesPage::instancePages() const {
  return instancePages_;
}
void InstancesPage::setInstancePages(
    const QMap<QString, NewInstancePage *> &instancePages) {
  instancePages_ = instancePages;
}
