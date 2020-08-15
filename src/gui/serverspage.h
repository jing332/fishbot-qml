#ifndef SERVERSPAGE_H
#define SERVERSPAGE_H

#include <QObject>

#include "appstate.h"
#include "model/serverlistmodel.h"

class ServersPage : public QObject {
  Q_OBJECT
  Q_PROPERTY(ServerListModel *modelData READ serversModel WRITE setServersModel
                 NOTIFY modelDataChanged)

 public:
  ServersPage(AppState *appState, QObject *parent = nullptr);
  ~ServersPage();

  void setRootObject(QObject *root);

  ServerListModel *serversModel() const;
  void setServersModel(ServerListModel *serversModel);

 signals:
  void modelDataChanged();
  void addServer(QString name, QString addr);
  void editServer(int index, QString name, QString addr);

 private slots:
  void onModelDataChanged();
  void onRefreshServerStatus(int index);
  void onRefreshAllServerStatus();
  void onAddServer(QString name, QString addr);
  void onEditServer(int index, QString name, QString addr);
  void onServerDoubleClicked(int index);

 private:
  QObject *root_;
  AppState *appState_;
  ServerListModel *serversModel_;
};

#endif  // SERVERSPAGE_H
