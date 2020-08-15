#ifndef PINGSERVERRUN_H
#define PINGSERVERRUN_H

#include <QObject>
#include <QRunnable>

#include "json/serverstatus.h"

class PingServerRun : public QObject, public QRunnable {
  Q_OBJECT
 public:
  PingServerRun(int index, const QString &addr);

 protected:
  void run() override;

 signals:
  void finished(int index, ServerStatus status, int delay,
                const QString &err = QString());

 private:
  int index_;
  QString addr_;
};

#endif  // PINGSERVERRUN_H
