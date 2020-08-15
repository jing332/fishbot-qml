#include "mcclientrun.h"

#include "fishbot.h"

McClientRun::McClientRun(const QString &addr, const QString &name,
                         const QString &uuid, const QString &accessToken,
                         const QString &sessionUrl)
    : addr_(addr),
      name_(name),
      uuid_(uuid),
      accessToken_(accessToken),
      sessionUrl_(sessionUrl) {}

void McClientRun::sendMsg(const QString &msg) {
  CgoSendMsg(const_cast<char *>(addr_.toStdString().c_str()),
             const_cast<char *>(msg.toStdString().c_str()));
}

void McClientRun::run() {
  const char *err =
      CgoNewClient(const_cast<char *>(addr_.toStdString().c_str()),
                   const_cast<char *>(name_.toStdString().c_str()),
                   const_cast<char *>(uuid_.toStdString().c_str()),
                   const_cast<char *>(accessToken_.toStdString().c_str()),
                   const_cast<char *>(sessionUrl_.toStdString().c_str()));

  if (err) {
    emit error(err);
    delete err;
  }
}
