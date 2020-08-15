#include "newinstancepage.h"

#include <QDebug>

#include "minecraft/text/textcomponentstring.h"

NewInstancePage::NewInstancePage() {}

NewInstancePage::NewInstancePage(const QString &serverName,
                                 const QString &serverAddr, QObject *parent)
    : QObject(parent),
      chatsModel_(new ChatListModel(this)),
      serverName_(serverName),
      serverAddress_(serverAddr) {
  connect(this, SIGNAL(chatsModelChanged()), this, SLOT(onChatsModelChanged()));

  connect(this, SIGNAL(appendChatLine(QString)), this,
          SLOT(onAppendChatLine(QString)), Qt::BlockingQueuedConnection);
}

void NewInstancePage::setRootObject(QObject *root) {
  root_ = root;

  connect(root_, SIGNAL(sendMessage(QString)), this,
          SLOT(onSendMessage(QString)));

  chatsModel_->append(ChatItemData("Minecraft!!!"));

  emit onChatsModelChanged();
}

void NewInstancePage::onChatsModelChanged() {
  root_->setProperty("chatsModel", QVariant::fromValue(chatsModel_));
}

void NewInstancePage::onSendMessage(const QString &msg) {
  qInfo() << "Send message:" << msg;
  client()->sendMsg(msg);
}

void NewInstancePage::onAppendChatLine(const QString &json) {
  qDebug() << json;
  chatsModel_->append(ChatItemData(
      TextComponent::NewTextFromJsonString(json)->GetFormattedText()));
}

ChatListModel *NewInstancePage::chatsModel() const { return chatsModel_; }
void NewInstancePage::setChatsModel(ChatListModel *chatsModel) {
  chatsModel_ = chatsModel;
  emit onChatsModelChanged();
}

QString NewInstancePage::serverAddress() const { return serverAddress_; }

void NewInstancePage::setServerAddress(const QString &serverAddress) {
  serverAddress_ = serverAddress;
}

QString NewInstancePage::serverName() const { return serverName_; }

void NewInstancePage::setServerName(const QString &serverName) {
  serverName_ = serverName;
}

McClientRun *NewInstancePage::client() const { return client_; }
void NewInstancePage::setClient(McClientRun *client) { client_ = client; }
