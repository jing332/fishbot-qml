#include "httppostrun.h"

HttpPostRun::HttpPostRun(const QUrl &url, const QString &body)
    : url_(url), body_(body) {}

void HttpPostRun::run() {
  auto resp =
      CgoHttpPost(const_cast<char *>(url_.toString().toStdString().c_str()),
                  const_cast<char *>(body_.toStdString().c_str()));
  emit Finished(resp);
}
