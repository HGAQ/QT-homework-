QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attentions.cpp \
    block.cpp \
    bullet.cpp \
    choice.cpp \
    game.cpp \
    guide1.cpp \
    main.cpp \
    arkmidnight.cpp \
    monster.cpp \
    nextwave.cpp

HEADERS += \
    arkmidnight.h \
    attentions.h \
    block.h \
    bullet.h \
    choice.h \
    game.h \
    guide1.h \
    monster.h \
    nextwave.h

FORMS += \
    arkmidnight.ui \
    game.ui \
    guide1.ui \
    nextwave.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
