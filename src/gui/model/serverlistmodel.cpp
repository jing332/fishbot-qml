#include "serverlistmodel.h"

#include <QDebug>

ServerItemData::ServerItemData() {}

ServerItemData::ServerItemData(const QString &Name, const QString &addr)
    : name_(Name), addr_(addr) {}

QString ServerItemData::name() const { return name_; }
void ServerItemData::setName(const QString &name) { name_ = name; }

QString ServerItemData::address() const { return addr_; }
void ServerItemData::setAddress(const QString &host) { addr_ = host; }

QString ServerItemData::favicon() const { return favicon_; }
void ServerItemData::setFavicon(const QString &favicon) { favicon_ = favicon; }

QString ServerItemData::Motd() const { return motd_; }
void ServerItemData::setMotd(const QString &motd) { motd_ = motd; }

QString ServerItemData::onlinePlayers() const { return onlinePlayers_; }
void ServerItemData::setOnlinePlayers(const QString &onlinePlayers) {
  onlinePlayers_ = onlinePlayers;
}

QString ServerItemData::delay() const { return delay_; }
void ServerItemData::setDelay(const QString &delay) { delay_ = delay; }

ServerListModel::ServerListModel(QObject *parent)
    : QAbstractListModel(parent) {}

int ServerListModel::rowCount(const QModelIndex &index) const {
  Q_UNUSED(index)
  return datas.size();
}

QVariant ServerListModel::data(const QModelIndex &index, int role) const {
  if (0 > index.row() || datas.size() < index.row()) return QVariant();

  auto &data = datas[index.row()];
  switch (role) {
    case NameRole:
      return data.name();
    case AddrRole:
      return data.address();
    case FaviconRole:
      return data.favicon();
    case MotdRole:
      return data.Motd();
    case OnlinePlayersRole:
      return data.onlinePlayers();
    case DelayRole:
      return data.delay();
    default:
      return QVariant();
  }
}

QHash<int, QByteArray> ServerListModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[NameRole] = "name";
  roles[AddrRole] = "addr";
  roles[FaviconRole] = "favicon";
  roles[MotdRole] = "motd";
  roles[OnlinePlayersRole] = "onlinePlayers";
  roles[DelayRole] = "delay";
  return roles;
}

void ServerListModel::insert(int index, const ServerItemData &data) {
  if (0 > index || index > datas.size()) return;

  emit beginInsertRows(QModelIndex(), index, index);
  datas.insert(index, data);
  emit endInsertRows();
  emit countChanged(datas.size());
}

void ServerListModel::append(const ServerItemData &data) {
  insert(Count(), data);
  emit countChanged(datas.size());
}

void ServerListModel::remove(int index) {
  if (0 > index || index > datas.size()) return;

  emit beginRemoveRows(QModelIndex(), index, index);
  datas.removeAt(index);
  emit endRemoveRows();
  emit countChanged(datas.size());
}

// void ServerListModel::append(const QVariantMap map) {
//  qDebug() << "apend" << Qt::endl;
//}

ServerItemData &ServerListModel::at(int index) { return datas[index]; }

void ServerListModel::updateItemData(int index) {
  auto modelIndex = createIndex(index, index);
  emit dataChanged(modelIndex, modelIndex);
}

void ServerListModel::updateItemDatas(int top, int bottom) {
  auto topIndex = createIndex(top, top);
  auto bottomIndex = createIndex(bottom, bottom);
  emit dataChanged(topIndex, bottomIndex);
}

int ServerListModel::Count() const { return rowCount(); }
