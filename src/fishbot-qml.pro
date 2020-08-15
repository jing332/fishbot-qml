QT += qml quick

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += $$PWD/go-mc/cmd/cgoqt/fishbot.a
macx {
    LIBS += -framework Security
}

INCLUDEPATH += $$PWD/include $$PWD/go-mc/cmd/cgoqt

SOURCES += \
        gui/instancespage.cpp \
        gui/model/chatlistmodel.cpp \
        gui/newinstancepage.cpp \
        json/jsonhelper.cpp \
        json/serverstatus.cpp \
        minecraft/text/chatformat.cpp \
        minecraft/text/event/clickaction.cpp \
        minecraft/text/event/hoveraction.cpp \
        minecraft/text/style.cpp \
        minecraft/text/textcomponent.cpp \
        minecraft/text/textcomponentbase.cpp \
        minecraft/text/textcomponentstring.cpp \
        minecraft/text/textcomponenttranslation.cpp \
        minecraft/text/textformatting.cpp \
        main.cpp \
        minecraft/text/translation/languagemap.cpp \
        minecraft/yggdrasil/authpayload.cpp \
        minecraft/yggdrasil/authresponse.cpp \
        minecraft/yggdrasil/refreshpayload.cpp\
        minecraft/yggdrasil/validatepayload.cpp \
        minecraft/yggdrasil/yggdrasil.cpp \
        runnables/httppostrun.cpp \
        runnables/mcclientrun.cpp \
        runnables/pingserverrun.cpp \
        gui/accountspage.cpp \
        gui/appglobal.cpp \
        gui/appstate.cpp \
        gui/model/accountlistmodel.cpp \
        gui/model/authserverlistmodel.cpp \
        gui/model/serverlistmodel.cpp \
        gui/serverspage.cpp \
        gui/qmlmainwindow.cpp \
        gui/quickitem/base64image.cpp \
        gui/quickitem/chattext.cpp

HEADERS += \
        gui/instancespage.h \
        gui/model/chatlistmodel.h \
        gui/newinstancepage.h \
        json/jsonhelper.h \
        json/serverstatus.h \
        minecraft/text/chatcolor.h \
        minecraft/text/chatformat.h \
        minecraft/text/event/clickaction.h \
        minecraft/text/event/clickevent.h \
        minecraft/text/event/hoveraction.h \
        minecraft/text/event/hoverevent.h \
        minecraft/text/style.h \
        minecraft/text/textcomponent.h \
        minecraft/text/textcomponentbase.h \
        minecraft/text/textcomponentstring.h \
        minecraft/text/textcomponenttranslation.h \
        minecraft/text/textformatting.h \
        minecraft/text/translation/languagemap.h \
        minecraft/yggdrasil/accounttype.h \
        minecraft/yggdrasil/authpayload.h \
        minecraft/yggdrasil/authresponse.h \
        minecraft/yggdrasil/refreshpayload.h \
        minecraft/yggdrasil/validatepayload.h \
        minecraft/yggdrasil/yggdrasil.h \
        runnables/httppostrun.h \
        runnables/mcclientrun.h \
        runnables/pingserverrun.h \
        gui/accountspage.h \
        gui/appglobal.h \
        gui/appstate.h \
        gui/model/accountlistmodel.h \
        gui/model/authserverlistmodel.h \
        gui/model/serverlistmodel.h \
        gui/serverspage.h \
        gui/qmlmainwindow.h \
        gui/quickitem/base64image.h \
        gui/quickitem/chattext.h \
        gui/serversmodel.h

RESOURCES += \
        res/fishbot-qml.qrc \
        gui/qml.qrc



# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
