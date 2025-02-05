QT       += core gui charts widgets

TEMPLATE = app
TARGET = ChartApp

CONFIG += c++17

SOURCES += \
    main.cpp \
    chartwindow.cpp

HEADERS += \
    chartwindow.h

FORMS += \
    chartwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

