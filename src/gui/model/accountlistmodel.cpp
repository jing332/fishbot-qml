#include "accountlistmodel.h"

AccountItemData::AccountItemData() {}

AccountItemData::AccountItemData(AuthResponse authResp, bool select)
    : isSelected_(select),
      type_(Yggdrasil::YggdrasilType),
      accountInfo_(authResp) {}

AccountItemData::AccountItemData(const QString &displayName, bool select)
    : isSelected_(select),
      type_(Yggdrasil::OfflineType),
      accountInfo_(AuthResponse()) {
  accountInfo_.setSelectedProfile(Profile("", displayName));
}

bool AccountItemData::isSelected() const { return isSelected_; }
void AccountItemData::setIsSelected(bool isSelected) {
  isSelected_ = isSelected;
}

Yggdrasil::AccountType AccountItemData::type() const { return type_; }
void AccountItemData::setType(const Yggdrasil::AccountType &type) {
  type_ = type;
}

AuthResponse AccountItemData::accountInfo() const { return accountInfo_; }
void AccountItemData::setAccountInfo(const AuthResponse &accountInfo) {
  accountInfo_ = accountInfo;
}

// AuthServerItemData AccountItemData::authServer() const { return authServer_;
// } void AccountItemData::setAuthServer(const AuthServerItemData &authServer) {
//  authServer_ = authServer;
//}

AccountListModel::AccountListModel(QObject *parent)
    : QAbstractListModel(parent) {}

int AccountListModel::rowCount(const QModelIndex &index) const {
  Q_UNUSED(index)
  return datas_.size();
}

QVariant AccountListModel::data(const QModelIndex &index, int role) const {
  if (0 > index.row() || datas_.size() < index.row()) return QVariant();

  auto &data = datas_[index.row()];
  switch (role) {
    case IsSelectedRole:
      return data.isSelected();
    case UserNameRole:
      return data.accountInfo().user().username;
    case DisplayNameRole:
      return data.accountInfo().selectedProfile().name();
    case TypeRole:
      return data.type();
    default:
      return QVariant();
  }
}

QHash<int, QByteArray> AccountListModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[IsSelectedRole] = "isSelected";
  roles[DisplayNameRole] = "displayName";
  roles[UserNameRole] = "username";
  roles[TypeRole] = "type";
  return roles;
}

void AccountListModel::insert(int index, const AccountItemData &data) {
  if (0 > index || index > datas_.size()) return;

  emit beginInsertRows(QModelIndex(), index, index);
  datas_.insert(index, data);
  emit endInsertRows();
  emit countChanged(datas_.size());
}

void AccountListModel::append(const AccountItemData &data) {
  insert(datas_.size(), data);
  emit countChanged(datas_.size());
}

void AccountListModel::remove(int index) {
  if (0 > index || index > datas_.size()) return;

  emit beginRemoveRows(QModelIndex(), index, index);
  datas_.removeAt(index);
  emit endRemoveRows();
  emit countChanged(datas_.size());
}

AccountItemData &AccountListModel::at(int index) { return datas_[index]; }

void AccountListModel::updateItemData(int index) {
  auto modelIndex = createIndex(index, index);
  emit dataChanged(modelIndex, modelIndex);
}

void AccountListModel::updateItemDatas(int top, int bottom) {
  auto topIndex = createIndex(top, top);
  auto bottomIndex = createIndex(bottom, bottom);
  emit dataChanged(topIndex, bottomIndex);
}
