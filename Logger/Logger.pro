QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += $$PWD/build-$${TARGET}-Desktop-Debug
INCLUDEPATH += /usr/include/c++/9
INCLUDEPATH += /usr/include/x86_64-linux-gnu/c++/9
INCLUDEPATH += /usr/include/c++/9/backward
INCLUDEPATH += /usr/lib/gcc/x86_64-linux-gnu/9/include
INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/include/x86_64-linux-gnu
INCLUDEPATH += /usr/include

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
