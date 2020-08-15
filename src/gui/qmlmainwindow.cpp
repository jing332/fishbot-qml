#include "qmlmainwindow.h"

#include <QQmlComponent>
#include <QThreadPool>

#include "minecraft/text/textcomponentstring.h"
#include "minecraft/yggdrasil/yggdrasil.h"
#include "quickitem/base64image.h"
#include "quickitem/chattext.h"
#include "runnables/pingserverrun.h"

QmlMainWindow::QmlMainWindow()
    : appState_(new AppState(this)),
      serverPage_(new ServersPage(appState_, this)),
      accountsPage_(new AccountsPage(appState_, this)),
      instancesPage_(new InstancesPage(appState_, this)) {}

void QmlMainWindow::setRootObject(QObject *root) {
  root_ = root;

  auto stackLayout = root_->findChild<QObject *>("stackLayout");
  serverPage_->setRootObject(stackLayout->findChild<QObject *>("serversPage"));
  accountsPage_->setRootObject(
      stackLayout->findChild<QObject *>("accountsPage"));
  instancesPage_->setRootObject(
      stackLayout->findChild<QObject *>("instancesPage"));
}
