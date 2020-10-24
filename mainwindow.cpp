#include "mainwindow.h"
#include <DMainWindow>
#include <DTitlebar>
#include <QtWidgets/QVBoxLayout>


DWIDGET_USE_NAMESPACE

MainWindow::MainWindow(QString szTitle,
                       QString szUrl,
                       int nWidth,
                       int nHeight,
                       QWidget *parent)
    : DMainWindow(parent)
{
    w = new Widget(szUrl);

    //resize(w->size());
    setFixedSize(nWidth, nHeight);
    titlebar()->setTitle(szTitle);

    setCentralWidget(w);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);

    titlebar()->setIcon(QIcon(":/images/logo.svg"));

}

MainWindow::~MainWindow()
{

}
