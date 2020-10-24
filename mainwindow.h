#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include "widget.h"

#include "globaldefine.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString szTitle = DEFAULT_TITLE,
               QString szUrl = DEFAULT_URL,
               int nWidth = DEFAULT_WIDTH,
               int nHeight = DEFAULT_HEIGHT,
               QWidget *parent = 0);
    ~MainWindow();

private:
    Widget *w;
};

#endif // MAINWINDOW_H
