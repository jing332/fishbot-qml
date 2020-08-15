#include "pingserverrun.h"

#include "fishbot.h"

PingServerRun::PingServerRun(int index, const QString &addr)
    : index_(index), addr_(addr) {}

void PingServerRun::run() {
  auto result = CgoPingServer(const_cast<char *>(addr_.toStdString().c_str()));
  if (result->error) {
    emit finished(index_, ServerStatus(), 0, result->error);
    delete result->error;
  } else {
    ServerStatus status;
    status.FromJson(result->json);
    emit finished(index_, status, result->delay);
    delete result->json;
  }

  delete result;
}
