QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    homework.cpp \
    main.cpp \
    mainwindow.cpp \
    second_window.cpp \
    student_stats.cpp

HEADERS += \
    homework.h \
    mainwindow.h \
    second_window.h \
    student_stats.h

FORMS += \
    homework.ui \
    mainwindow.ui \
    second_window.ui \
    student_stats.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc
