#ifndef SERVERSTATUS_H
#define SERVERSTATUS_H

#include "jsonhelper.h"
#include "minecraft/text/textcomponentstring.h"
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"

using namespace rapidjson;

typedef struct {
  QString name;
  int protocol;
} Version;

typedef struct {
  QString name;
  QString id;
} Sample;

typedef struct {
  int max = 0;
  int online = 0;
  QList<Sample> sample;
} Players;

class ServerStatus : public JsonHelper {
 public:
  ServerStatus();

  TextComponentString GetDecription() const;
  QString GetFavicon() const;
  Players GetPlayers() const;
  Version GetVersion() const;

  void SetDescription(TextComponentString description);
  void SetFavicon(const QString &favicon);
  void SetPlayers(Players players);
  void SetVersion(Version version);

  void FromJson(const QString &json) override;

 private:
  TextComponentString description_;
  QString favicon_;
  Players players_;
  Version version_;
};
Q_DECLARE_METATYPE(ServerStatus);

#endif  // SERVERSTATUS_H
