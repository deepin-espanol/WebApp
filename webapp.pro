QT += core widgets gui webengine webenginewidgets svg concurrent

greaterThan(QT_MAJOR_VERSION, 6): QT += widgets

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget

SOURCES += main.cpp\
        httpd.cpp \
        mainwindow.cpp \
        webenginepage.cpp \
        widget.cpp

HEADERS  += mainwindow.h \
         globaldefine.h \
         httpd.h \
         httplib.h \
         webenginepage.h \
         widget.h

FORMS += widget.ui

RESOURCES += imgs.qrc

TRANSLATIONS += translations/WebApp_zh_CN.ts \
    translations/WebApp_es_ES.ts


