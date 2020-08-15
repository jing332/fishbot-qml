#ifndef NEWINSTANCEPAGE_H
#define NEWINSTANCEPAGE_H

#include <QObject>

#include "model/chatlistmodel.h"
#include "runnables/mcclientrun.h"

class NewInstancePage : public QObject {
  Q_OBJECT
  Q_PROPERTY(ChatListModel *chatsModel READ chatsModel WRITE setChatsModel
                 NOTIFY chatsModelChanged)
 public:
  NewInstancePage();
  explicit NewInstancePage(const QString &serverName, const QString &serverAddr,
                           QObject *parent = nullptr);

  void setRootObject(QObject *obj);

  ChatListModel *chatsModel() const;

  McClientRun *client() const;
  void setClient(McClientRun *client);

  QString serverName() const;
  void setServerName(const QString &serverName);

  QString serverAddress() const;
  void setServerAddress(const QString &serverAddress);

 signals:
  void chatsModelChanged();
  void appendChatLine(const QString &json);

 public slots:
  void onChatsModelChanged();
  void onSendMessage(const QString &msg);
  void onAppendChatLine(const QString &json);

  void setChatsModel(ChatListModel *chatsModel);

 private:
  QObject *root_;
  ChatListModel *chatsModel_;
  McClientRun *client_;

  QString serverName_;
  QString serverAddress_;
};

#endif  // NEWINSTANCEPAGE_H
