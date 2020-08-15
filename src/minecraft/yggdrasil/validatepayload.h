#ifndef VALIDATEPAYLOAD_H
#define VALIDATEPAYLOAD_H

#include "json/jsonhelper.h"

class ValidatePayload : public JsonHelper {
 public:
  ValidatePayload();
  ValidatePayload(const QString &accessToken, const QString &clientToken);

  QString ToJson() const override;

 private:
  QString accessToken_;
  QString clientToken_;
};

#endif  // VALIDATEPAYLOAD_H
