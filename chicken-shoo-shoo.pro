QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        audiorecorder.cpp \
        avatar.cpp \
        camera.cpp \
        chicken.cpp \
        drawable.cpp \
        game.cpp \
        inputhandler.cpp \
        level.cpp \
        levelloader.cpp \
        main.cpp \
        rectangle.cpp \
        spikes.cpp \
        tile.cpp \
        timehandler.cpp \
        utils.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/SFML/bin/ -lsfml-system-2 -lsfml-audio-2 -lsfml-graphics-2 -lsfml-network-2 -lsfml-window-2
win32: INCLUDEPATH += $$PWD/SFML/include
win32: DEPENDPATH += $$PWD/SFML/lib

unix: LIBS += -L$$PWD/SFML-2.5.1-macOS-clang/lib/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
unix: INCLUDEPATH += $$PWD/SFML-2.5.1-macos-clang/include
unix: DEPENDPATH += $$PWD/SFML-2.5.1-macos-clang/include

HEADERS += \
    ResourcePath.hpp \
    audiorecorder.h \
    avatar.h \
    camera.h \
    chicken.h \
    drawable.h \
    game.h \
    inputhandler.h \
    level.h \
    levelloader.h \
    rectangle.h \
    spikes.h \
    tile.h \
    timehandler.h \
    utils.h
