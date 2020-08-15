#ifndef CHATLISTMODEL_H
#define CHATLISTMODEL_H

#include <QAbstractListModel>

class ChatItemData {
 public:
  ChatItemData(const QString &text);

  QString formatedText() const;
  void setFormatedText(const QString &formatedText);

 private:
  QString formatedText_;
};

class ChatListModel : public QAbstractListModel {
 public:
  enum ChatRoles { FormatedText = Qt::UserRole };

  ChatListModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &index = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  Q_INVOKABLE void insert(int index, const ChatItemData &data);
  Q_INVOKABLE void append(const ChatItemData &data);
  Q_INVOKABLE void remove(int index);

  ChatItemData &at(int index);
  void updateItemData(int index);
  void updateItemDatas(int top, int bottom);

 protected:
  QHash<int, QByteArray> roleNames() const override;

 signals:
  void countChanged(int arg);

 private:
  QList<ChatItemData> datas_;
};

#endif  // CHATLISTMODEL_H
