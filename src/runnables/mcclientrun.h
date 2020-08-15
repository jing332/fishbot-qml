#ifndef MCCLIENTRUN_H
#define MCCLIENTRUN_H

#include <QObject>
#include <QRunnable>

class McClientRun : public QObject, public QRunnable {
  Q_OBJECT
 public:
  McClientRun(const QString &addr, const QString &name,
              const QString &uuid = QString(),
              const QString &accessToken = QString(),
              const QString &sessionUrl = QString());

  void sendMsg(const QString &msg);

 protected:
  void run() override;

 signals:
  void error(const QString &reason);

 private:
  QString addr_;
  QString name_;
  QString uuid_;
  QString accessToken_;
  QString sessionUrl_;
};

#endif  // MCCLIENTRUN_H
