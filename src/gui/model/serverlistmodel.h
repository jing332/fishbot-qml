#ifndef SERVERLISTMODEL_H
#define SERVERLISTMODEL_H

#include <QAbstractListModel>

class ServerItemData {
 public:
  ServerItemData();
  ServerItemData(const QString &Name, const QString &addr);

  QString name() const;
  void setName(const QString &name);

  QString address() const;
  void setAddress(const QString &host);

  QString favicon() const;
  void setFavicon(const QString &favicon);

  QString Motd() const;
  void setMotd(const QString &Motd);

  QString onlinePlayers() const;
  void setOnlinePlayers(const QString &onlinePlayers);

  QString delay() const;
  void setDelay(const QString &delay);

 private:
  QString name_;
  QString addr_;
  QString favicon_;
  QString motd_;
  QString onlinePlayers_;
  QString delay_;
};

class ServerListModel : public QAbstractListModel {
  Q_OBJECT
 public:
  enum ServerRoles {
    NameRole = Qt::UserRole + 1,
    AddrRole,
    FaviconRole,
    MotdRole,
    OnlinePlayersRole,
    DelayRole
  };

  explicit ServerListModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &index = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  Q_INVOKABLE void insert(int index, const ServerItemData &data);
  Q_INVOKABLE void append(const ServerItemData &data);
  Q_INVOKABLE void remove(int index);

  ServerItemData &at(int index);
  void updateItemData(int index);
  void updateItemDatas(int top, int bottom);

 protected:
  QHash<int, QByteArray> roleNames() const;

 signals:
  void countChanged(int arg);

 private:
  int Count() const;

 private:
  QList<ServerItemData> datas;
};

#endif  // SERVERLISTMODEL_H
