#include "yggdrasil.h"

#include <QEventLoop>
#include <QThreadPool>
#include <QUuid>

#include "authpayload.h"
#include "runnables/httppostrun.h"

const QString Yggdrasil::kMojangAuthURL =
    QStringLiteral("https://authserver.mojang.com");
const QString Yggdrasil::kMojangSessionURL =
    QStringLiteral("https://sessionserver.mojang.com");

Yggdrasil::Yggdrasil() {
  /*设置为Mojang认证服务器*/
  SetBaseURL();
}

Yggdrasil::~Yggdrasil() {}

void Yggdrasil::Authenticate(const QString &username, const QString &password,
                             const QString &clientToken) {
  if (clientToken.isEmpty()) {
    Authenticate(username, password);
  } else {
    AuthPayload payload(username, password, clientToken);
    QString json = payload.ToJson();

    auto *run = new HttpPostRun(authURL_, json);
    connect(run, &HttpPostRun::Finished, [=](HttpResponse *resp) {
      if (resp->error) {
        qWarning("Account verification failed: %s", resp->error);
        emit authFinished(AuthResponse(), QString(resp->error));
        delete resp->error;
      } else {
        AuthResponse authResp;
        authResp.FromJson(QByteArray(resp->body, resp->bodyLenth));

        emit authFinished(authResp);
      }

      delete resp->body;
      delete resp->status;
      delete resp;
    });

    QThreadPool::globalInstance()->start(run);
  }
}

void Yggdrasil::Validate(ValidatePayload payload) {
  QString json = payload.ToJson();

  auto *run = new HttpPostRun(json, Yggdrasil::validateURL_);
  connect(run, &HttpPostRun::Finished, [=](HttpResponse *resp) {
    if (resp->error || QStringLiteral("204 No Content") == resp->status) {
      delete resp->error;
      emit validateFinished(true);
    } else {
      emit validateFinished(false);
    }

    delete resp->body;
    delete resp->status;
    delete resp;
  });
  QThreadPool::globalInstance()->start(run);
}

void Yggdrasil::Refresh(RefreshPayload payload) {
  QString json = payload.ToJson();
  HttpPostRun *run = new HttpPostRun(json, Yggdrasil::refreshURL_);
  connect(run, &HttpPostRun::Finished, [=](HttpResponse *resp) {
    if (resp->error) {
      qWarning("Account refresh failed: %s", resp->error);
      delete resp->error;
    } else {
      AuthResponse authResp;
      authResp.FromJson(resp->body);
      emit refreshFinished(authResp);
    }
    delete resp->body;
    delete resp->status;
    delete resp;
  });
  QThreadPool::globalInstance()->start(run);
}

void Yggdrasil::SetBaseURL(const QString &url) {
  if (url.isEmpty()) {
    authServer_ = kMojangAuthURL;
    sessionServer_ = kMojangSessionURL;
  } else {
    baseURL_ = url;
    authServer_ = baseURL_ + "/authserver";
    sessionServer_ = Yggdrasil::baseURL_ + "/sessionserver";
  }

  authURL_ = authServer_ + "/authenticate";
  refreshURL_ = authServer_ + "/refresh";
  validateURL_ = authServer_ + "/validate";
}

QString Yggdrasil::FormatProfileURL(const QString &uuid) {
  return QString(Yggdrasil::kMojangSessionURL)
      .append(QStringLiteral("/session/minecraft/profile/"))
      .append(uuid);
}

QString Yggdrasil::FormatProfileURL(const QString &authURL,
                                    const QString &uuid) {
  return QString(authURL)
      .append(QStringLiteral("/sessionserver/session/minecraft/profile/"))
      .append(uuid);
}
