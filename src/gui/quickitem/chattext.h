#ifndef CHATTEXT_H
#define CHATTEXT_H

#include <QQuickPaintedItem>

class ChatText : public QQuickPaintedItem {
  Q_OBJECT
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
 public:
  ChatText();

  void paint(QPainter *painter) override;

  QString text() const;
  void setText(const QString &text);

 signals:
  void textChanged();

 private:
  QString text_;
};

#endif  // CHATTEXT_H
