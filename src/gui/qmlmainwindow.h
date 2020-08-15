#ifndef QMLMAINWINDOW_H
#define QMLMAINWINDOW_H

#include <qquickview.h>

#include <QGuiApplication>
#include <QMap>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "accountspage.h"
#include "appstate.h"
#include "instancespage.h"
#include "serverspage.h"

class QmlMainWindow : public QObject {
  Q_OBJECT
 public:
  QmlMainWindow();

  void setRootObject(QObject *root);

 private slots:

 private:
  QObject *root_;
  AppState *appState_;

  ServersPage *serverPage_;
  AccountsPage *accountsPage_;
  InstancesPage *instancesPage_;
};

#endif  // QMLMAINWINDOW_H
