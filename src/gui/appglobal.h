#ifndef APPGLOBAL_H
#define APPGLOBAL_H

#include <QObject>

class AppGlobal : public QObject {
  Q_OBJECT
  Q_PROPERTY(QObject* appState READ GetAppState WRITE SetAppState NOTIFY
                 AppStateChanged)
  Q_PROPERTY(QObject* mainWindow READ GetMainWindow WRITE SetMainWindow NOTIFY
                 MainWindowChanged)
  Q_PROPERTY(QString activeColor READ GetActiveColor WRITE SetActiveColor NOTIFY
                 ActiveColorChanged)
  Q_PROPERTY(QString backgroundColor READ GetBackgroundColor WRITE
                 SetBackgroundColor NOTIFY BackgroundColorChanged)
  //  Q_PROPERTY(int currentAccountIndex READ currentAccountIndex WRITE
  //                 setCurrentAccountIndex NOTIFY currentAccountIndexChanged)
 public:
  AppGlobal();

  QObject* GetAppState() const;
  void SetAppState(QObject* appState);

  QObject* GetMainWindow() const;
  void SetMainWindow(QObject* mainWindow);

  QString GetActiveColor() const;
  void SetActiveColor(QString color);

  QString GetBackgroundColor() const;
  void SetBackgroundColor(QString color);

  //  int currentAccountIndex() const;
  //  void setCurrentAccountIndex(int currentAccountIndex);

 signals:
  void AppStateChanged();
  void MainWindowChanged();
  void ActiveColorChanged();
  void BackgroundColorChanged();
  //  void currentAccountIndexChanged();

 private:
  QObject* appState_ = nullptr;
  QObject* mainWindow_ = nullptr;

  QString backgroundColor_ = "#303030";  //"#1e1e1e"
  QString activeColor_ = "white";

  //  int currentAccountIndex_ = 0;
};

#endif  // APPGLOBAL_H
