QT += core widgets gui webengine webenginewidgets svg

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = WebApp
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget

SOURCES += main.cpp\
        mainwindow.cpp \
        widget.cpp

HEADERS  += mainwindow.h \
         globaldefine.h \
         widget.h

FORMS += widget.ui

TRANSLATIONS += \
    WebApp_zh_CN.ts

RESOURCES += IMGs.qrc
