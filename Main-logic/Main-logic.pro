QT += core network

CONFIG += c++17 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/build-$${TARGET}-Desktop-Debug
INCLUDEPATH += /usr/include/c++/9
INCLUDEPATH += /usr/include/x86_64-linux-gnu/c++/9
INCLUDEPATH += /usr/include/c++/9/backward
INCLUDEPATH += /usr/lib/gcc/x86_64-linux-gnu/9/include
INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/include/x86_64-linux-gnu
INCLUDEPATH += /usr/include

SOURCES += \
        commandreceiver.cpp \
        logsender.cpp \
        main.cpp \
        manager.cpp \
        pseudopicture.cpp \
        readthread.cpp \
        writethread.cpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    commandreceiver.h \
    container.h \
    icontainer.h \
    logsender.h \
    manager.h \
    pseudopicture.h \
    readthread.h \
    writethread.h
