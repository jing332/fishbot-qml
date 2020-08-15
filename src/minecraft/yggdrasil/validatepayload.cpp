#include "validatepayload.h"

ValidatePayload::ValidatePayload() {}

ValidatePayload::ValidatePayload(const QString &accessToken,
                                 const QString &clientToken)
    : accessToken_(accessToken), clientToken_(clientToken) {}

QString ValidatePayload::ToJson() const {
  StringBuffer buffer;
  Writer<rapidjson::StringBuffer> writer(buffer);
  writer.StartObject();
  writer.Key("accessToken");
  writer.String(accessToken_.toUtf8());

  writer.Key("clientToken");
  writer.String(clientToken_.toUtf8());
  writer.EndObject();

  return buffer.GetString();
}
