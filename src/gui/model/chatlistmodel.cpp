#include "chatlistmodel.h"

ChatListModel::ChatListModel(QObject *parent) : QAbstractListModel(parent) {}

int ChatListModel::rowCount(const QModelIndex &) const { return datas_.size(); }

QVariant ChatListModel::data(const QModelIndex &index, int role) const {
  auto data = datas_.at(index.row());
  switch (role) {
    case FormatedText:
      return data.formatedText();
  }
  return QVariant();
}

QHash<int, QByteArray> ChatListModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[FormatedText] = "formatedText";
  return roles;
}

void ChatListModel::insert(int index, const ChatItemData &data) {
  if (0 > index || index > datas_.size()) return;

  emit beginInsertRows(QModelIndex(), index, index);
  datas_.insert(index, data);
  emit endInsertRows();
}

void ChatListModel::append(const ChatItemData &data) {
  insert(datas_.size(), data);
}

void ChatListModel::remove(int index) {
  if (0 > index || index > datas_.size()) return;

  emit beginRemoveRows(QModelIndex(), index, index);
  datas_.removeAt(index);
  emit endRemoveRows();
}

ChatItemData &ChatListModel::at(int index) { return datas_[index]; }

void ChatListModel::updateItemData(int index) {
  auto modelIndex = createIndex(index, index);
  emit dataChanged(modelIndex, modelIndex);
}

void ChatListModel::updateItemDatas(int top, int bottom) {
  auto topIndex = createIndex(top, top);
  auto bottomIndex = createIndex(bottom, bottom);
  emit dataChanged(topIndex, bottomIndex);
}

ChatItemData::ChatItemData(const QString &text) : formatedText_(text) {}

QString ChatItemData::formatedText() const { return formatedText_; }
void ChatItemData::setFormatedText(const QString &formatedText) {
  formatedText_ = formatedText;
}
