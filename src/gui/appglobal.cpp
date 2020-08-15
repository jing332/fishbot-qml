#include "appglobal.h"

AppGlobal::AppGlobal() {}

QObject *AppGlobal::GetAppState() const { return appState_; }
void AppGlobal::SetAppState(QObject *appState) { appState_ = appState; }

QObject *AppGlobal::GetMainWindow() const { return mainWindow_; }
void AppGlobal::SetMainWindow(QObject *mainWindow) { mainWindow_ = mainWindow; }

QString AppGlobal::GetActiveColor() const { return activeColor_; }
void AppGlobal::SetActiveColor(QString color) { activeColor_ = color; }

QString AppGlobal::GetBackgroundColor() const { return backgroundColor_; }
void AppGlobal::SetBackgroundColor(QString color) { backgroundColor_ = color; }

// int AppGlobal::currentAccountIndex() const { return currentAccountIndex_; }

// void AppGlobal::setCurrentAccountIndex(int currentAccountIndex) {
//  currentAccountIndex_ = currentAccountIndex;
//  emit currentAccountIndexChanged();
//}
