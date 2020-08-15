#ifndef INSTANCESPAGE_H
#define INSTANCESPAGE_H

#include <QObject>

#include "appstate.h"
#include "model/accountlistmodel.h"
#include "newinstancepage.h"
#include "runnables/mcclientrun.h"

class InstancesPage : public QObject {
  Q_OBJECT
 public:
  explicit InstancesPage(AppState *appState, QObject *parent = nullptr);

  void setRootObject(QObject *root);

  QMap<QString, NewInstancePage *> instancePages() const;
  void setInstancePages(const QMap<QString, NewInstancePage *> &instancePages);

  QMap<QString, QString> serverNames() const;
  void setServerNames(const QMap<QString, QString> &serverNames);

 private:
  static void onChatMsg(const char *addr, const char *jsonMsg);
  static void onDisconnect(const char *addr, const char *reason);
  static void onGameStart(const char *addr);

 signals:
  void addTabPage(const QString &name, const QString &addr,
                  NewInstancePage *instancePage = nullptr);
  void closeTab(const QString &addr);

 public slots:
  void onAddTabPage(const QString &name, const QString &addr,
                    NewInstancePage *instancePage = new NewInstancePage());
  void onCloseTab(const QString &addr);
  void onJoinServer(const QString &serverName, const QString &serverAddr,
                    const QString &name, const QString &uuid,
                    const QString &accessToken, const QString &sessionUrl);

 private:
  /*self is used in the callback function*/
  static InstancesPage *kSelf;

  AppState *appState_;
  QObject *root_;
  /*Key is the server address*/
  QMap<QString, NewInstancePage *> instancePages_;
};

#endif  // INSTANCESPAGE_H
