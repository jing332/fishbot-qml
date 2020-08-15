#ifndef AUTHSERVERLISTMODEL_H
#define AUTHSERVERLISTMODEL_H

#include <QAbstractListModel>

class AuthServerItemData {
 public:
  AuthServerItemData();
  AuthServerItemData(const QString &name, const QString &url);

  QString name() const;
  void setName(const QString &name);

  QString url() const;
  void setUrl(const QString &url);

 private:
  QString name_;
  QString url_;
};

class AuthServerListModel : public QAbstractListModel {
  Q_OBJECT
 public:
  enum AuthServerRoles { NameRole = Qt::UserRole + 1, UrlRole };

  explicit AuthServerListModel(QObject *parent = nullptr);
  ~AuthServerListModel();

  int rowCount(const QModelIndex &index = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  Q_INVOKABLE void insert(int index, const AuthServerItemData &data);
  Q_INVOKABLE void append(const AuthServerItemData &data);
  Q_INVOKABLE void remove(int index);

  AuthServerItemData &at(int index);
  void updateItemData(int index);
  void updateItemDatas(int top, int bottom);

 protected:
  QHash<int, QByteArray> roleNames() const;

 signals:
  void countChanged(int arg);

 private:
  int Count() const;

 private:
  QList<AuthServerItemData> datas;
};

#endif  // AUTHSERVERLISTMODEL_H
