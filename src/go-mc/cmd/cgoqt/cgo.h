#ifndef CGO_H
#define CGO_H

#include <stdlib.h>
#include <string.h>

typedef void (*GameStartCallback)(const char* addr);
static inline void GameStartEvent(GameStartCallback cb, const char* addr) {
  cb(addr);
}

typedef void (*ChatMsgCallback)(const char* addr, const char* jsonMsg);
static inline void ChatMsgEvent(ChatMsgCallback cb, const char* addr,
                                const char* jsonMsg) {
  cb(addr, jsonMsg);
}

typedef void (*DeathCallback)(const char* addr);
static inline void DeathEvent(DeathCallback cb, const char* addr) { cb(addr); }

typedef void (*DisconnectCallback)(const char* addr, const char* reason);
static inline void DisconnectEvent(DisconnectCallback cb, const char* addr,
                                   const char* reason) {
  cb(addr, reason);
}

typedef struct {
  char* json;
  char* error;
  int delay;
} MCServerStatus;

typedef struct {
  char* error;
  char* body;
  int bodyLenth;
  char* status;
  int statusCode;
} HttpResponse;

static inline MCServerStatus* NewMCServerStatus(char* json, int delay) {
  MCServerStatus* p = (MCServerStatus*)malloc(sizeof(MCServerStatus));
  memset(p, 0, sizeof(MCServerStatus));
  p->json = json;
  p->error = NULL;
  p->delay = delay;
  return p;
}

static inline MCServerStatus* NewMCServerStatusErr(char* err) {
  MCServerStatus* p = (MCServerStatus*)malloc(sizeof(MCServerStatus));
  memset(p, 0, sizeof(MCServerStatus));
  p->error = err;
  p->json = NULL;
  p->delay = 0;
  return p;
}

static inline HttpResponse* NewHttpResponse(void* body, int bodyLenth,
                                            char* status, int statusCode) {
  HttpResponse* p = (HttpResponse*)malloc(sizeof(HttpResponse));
  memset(p, 0, sizeof(HttpResponse));
  p->body = (char*)body;
  p->bodyLenth = bodyLenth;
  p->statusCode = statusCode;
  p->status = status;
  p->error = NULL;
  return p;
}

static inline HttpResponse* NewResponseError(char* error) {
  HttpResponse* p = (HttpResponse*)malloc(sizeof(HttpResponse));
  memset(p, 0, sizeof(HttpResponse));
  p->error = error;
  return p;
}

#endif  // CGO_H
