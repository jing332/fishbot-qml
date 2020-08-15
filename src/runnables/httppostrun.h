#ifndef HTTPPOSTRUN_H
#define HTTPPOSTRUN_H

#include <QObject>
#include <QRunnable>
#include <QUrl>

#include "fishbot.h"

class HttpPostRun : public QObject, public QRunnable {
  Q_OBJECT
 public:
  HttpPostRun(const QUrl &url, const QString &body);

 protected:
  void run() override;

 signals:
  void Finished(HttpResponse *resp);

 private:
  QUrl url_;
  QString body_;
};

#endif  // HTTPPOSTRUN_H
