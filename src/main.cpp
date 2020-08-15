#include <QDateTime>
#include <QFont>
#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QTimer>

#include "gui/qmlmainwindow.h"
#include "gui/quickitem/base64image.h"
#include "gui/quickitem/chattext.h"
#include "gui/serverspage.h"
#include "minecraft/text/textcomponentstring.h"
#include "minecraft/yggdrasil/yggdrasil.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);
  app.setFont(QFont("Microsoft YaHei", 9));

  qmlRegisterType<ChatText>("com.jing.fishbot", 1, 0, "ChatText");
  qmlRegisterType<Base64Image>("com.jing.fishbot", 1, 0, "Base64Image");
  qRegisterMetaType<AuthResponse>("AuthResponse");

  QQuickView *view = new QQuickView;
  view->setSource(QUrl("qrc:/qml/main.qml"));
  view->setResizeMode(QQuickView::SizeRootObjectToView);
  view->setMinimumSize(QSize(640, 480));

  QmlMainWindow window;
  window.setRootObject(view->rootObject());

  QObject::connect(view->engine(), SIGNAL(quit()), view, SLOT(close()));
  view->setTitle("Minecraft FishBot GUI");
  view->show();

  return app.exec();
}
