#include "authpayload.h"

Agent::Agent() {}

QString Agent::GetName() const { return name_; }
QString Agent::SetName(const QString &name) { name_ = name; }

int Agent::GetVersion() const { return version_; }
void Agent::SetVersioon(int ver) { version_ = ver; }

AuthPayload::AuthPayload() {}

AuthPayload::AuthPayload(const QString &username, const QString &password,
                         const QString clientToken, bool requestUser)
    : username_(username),
      password_(password),
      clientToken_(clientToken),
      requestUser_(requestUser) {}

QString AuthPayload::ToJson() const {
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  writer.StartObject();
  writer.Key("agent");
  writer.StartObject();

  writer.Key("name");
  writer.String(agent_.GetName().toUtf8());

  writer.Key("version");
  writer.Int(agent_.GetVersion());
  writer.EndObject();

  writer.Key("username");
  writer.String(username_.toUtf8());

  writer.Key("password");
  writer.String(password_.toUtf8());

  writer.Key("clientToken");
  writer.String(clientToken_.toUtf8());

  writer.Key("requestUser");
  writer.Bool(requestUser_);

  writer.EndObject();

  return buffer.GetString();
}

Agent AuthPayload::GetAgent() const { return agent_; }
void AuthPayload::SetAgent(const Agent &agent) { agent_ = agent; }

QString AuthPayload::GetUsername() const { return username_; }
void AuthPayload::SetUsername(const QString &username) { username_ = username; }

QString AuthPayload::GetPassword() const { return password_; }
void AuthPayload::SetPassword(const QString &password) { password_ = password; }

QString AuthPayload::GetClientToken() const { return clientToken_; }
void AuthPayload::SetClientToken(const QString &clientToken) {
  clientToken_ = clientToken;
}

bool AuthPayload::GetRequestUser() const { return requestUser_; }
void AuthPayload::SetRequestUser(bool requestUser) {
  requestUser_ = requestUser;
}
