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
    main.cpp \
    commandreceiver.cpp \
    manager.cpp \
    logsender.cpp \
    pseudopicture.cpp

HEADERS += \
    commandreceiver.h \
    icontainer.h \
    container.h \
    manager.h \
    writethread.h \
    readthread.h \
    logsender.h \
    pseudopicture.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
