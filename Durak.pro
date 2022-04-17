QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Client/client.cpp \
    ConnectionWaitScreen/connectionwaitscreen.cpp \
    GameScreen/CardWidget/cardwidget.cpp \
    GameScreen/gamescreen.cpp \
    MenuScreen/menuscreenwidget.cpp \
    Server/Game/game.cpp \
    Server/server.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Card.h \
    Client/client.h \
    ConnectionWaitScreen/connectionwaitscreen.h \
    GameScreen/CardWidget/cardwidget.h \
    GameScreen/gamescreen.h \
    MenuScreen/menuscreenwidget.h \
    Server/Game/game.h \
    Server/server.h \
    mainwindow.h

FORMS += \
    ConnectionWaitScreen/connectionwaitscreen.ui \
    GameScreen/CardWidget/cardwidget.ui \
    GameScreen/gamescreen.ui \
    MenuScreen/menuscreenwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
