#include "authserverlistmodel.h"

AuthServerItemData::AuthServerItemData(const QString &name, const QString &url)
    : name_(name), url_(url) {}

QString AuthServerItemData::name() const { return name_; }
void AuthServerItemData::setName(const QString &name) { name_ = name; }

QString AuthServerItemData::url() const { return url_; }
void AuthServerItemData::setUrl(const QString &url) { url_ = url; }

AuthServerListModel::AuthServerListModel(QObject *parent)
    : QAbstractListModel(parent) {}

AuthServerListModel::~AuthServerListModel() {}

int AuthServerListModel::rowCount(const QModelIndex &index) const {
  Q_UNUSED(index)
  return datas.size();
}

QVariant AuthServerListModel::data(const QModelIndex &index, int role) const {
  if (0 > index.row() || datas.size() < index.row()) return QVariant();

  auto &data = datas[index.row()];
  switch (role) {
    case NameRole:
      return data.name();
    case UrlRole:
      return data.url();
    default:
      return QVariant();
  }
}

QHash<int, QByteArray> AuthServerListModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[NameRole] = "name";
  roles[UrlRole] = "url";
  return roles;
}

void AuthServerListModel::insert(int index, const AuthServerItemData &data) {
  if (0 > index || index > datas.size()) return;

  emit beginInsertRows(QModelIndex(), index, index);
  datas.insert(index, data);
  emit endInsertRows();
  emit countChanged(datas.size());
}

void AuthServerListModel::append(const AuthServerItemData &data) {
  insert(Count(), data);
  emit countChanged(datas.size());
}

void AuthServerListModel::remove(int index) {
  if (0 > index || index > datas.size()) return;

  emit beginRemoveRows(QModelIndex(), index, index);
  datas.removeAt(index);
  emit endRemoveRows();
  emit countChanged(datas.size());
}

AuthServerItemData &AuthServerListModel::at(int index) { return datas[index]; }

void AuthServerListModel::updateItemData(int index) {
  auto modelIndex = createIndex(index, index);
  emit dataChanged(modelIndex, modelIndex);
}

void AuthServerListModel::updateItemDatas(int top, int bottom) {
  auto topIndex = createIndex(top, top);
  auto bottomIndex = createIndex(bottom, bottom);
  emit dataChanged(topIndex, bottomIndex);
}

int AuthServerListModel::Count() const { return rowCount(); }
