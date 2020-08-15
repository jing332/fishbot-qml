#include "base64image.h"

#include <QPainter>

Base64Image::Base64Image() {}

void Base64Image::paint(QPainter *painter) {
  if (!pixmap_.isNull()) {
    QRectF target(0.0, 0.0, size().width(), size().height());
    QRectF source(0.0, 0.0, pixmap_.width(), pixmap_.height());
    painter->drawPixmap(target, pixmap_, source);
  }
}

QString Base64Image::GetBase64() const { return base64_; }

void Base64Image::SetBase64(const QString &base64) {
  base64_ = base64;
  if (base64.isEmpty()) {
    SetSource(QStringLiteral("://background/unknown_server.png"));
  } else {
    pixmap_.loadFromData(QByteArray::fromBase64(base64_.toLatin1()));
    update();
  }
}

QString Base64Image::GetSource() const { return source_; }

void Base64Image::SetSource(const QString &src) {
  source_ = src;
  pixmap_.load(src);
  update();
}
