#ifndef ICONIMAGEPROVIDER_H
#define ICONIMAGEPROVIDER_H

#include <QPixmap>
#include <QQuickPaintedItem>

class Base64Image : public QQuickPaintedItem {
  Q_OBJECT
  Q_PROPERTY(QString base64 READ GetBase64 WRITE SetBase64 NOTIFY Base64Changed)
  Q_PROPERTY(QString source READ GetSource WRITE SetSource NOTIFY SourceChanged)

 public:
  Base64Image();
  void paint(QPainter *painter) override;

  QString GetBase64() const;
  void SetBase64(const QString &base64);

  QString GetSource() const;
  void SetSource(const QString &src);

 signals:
  void Base64Changed();
  void SourceChanged();

 private:
  QString base64_;
  QString source_;
  QPixmap pixmap_;
};

#endif  // ICONIMAGEPROVIDER_H
