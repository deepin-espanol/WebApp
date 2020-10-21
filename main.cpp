#include "mainwindow.h"
#include <DApplication>
#include <DWidgetUtil>
#include <DAboutDialog>
#include <DMainWindow>


DWIDGET_USE_NAMESPACE
int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    DAboutDialog dialog;
    a.loadTranslator();
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setApplicationName("WepApp");
    a.setProductName("WepApp");
    a.setAboutDialog(&dialog);

    //Title
    dialog.setWindowTitle("WepApp");
    //descrition
    dialog.setProductName("<span>Template for WepApp</span>");
    //Icons
    dialog.setProductIcon(QIcon(":/images/logo.svg"));
    //Organization logo
    dialog.setCompanyLogo(QPixmap(":/images/Logo-Racoon.png"));
    //about
    dialog.setDescription(
            "<span style=' font-size:8pt; font-weight:600;'>Deepin en Español </span>"
            "<a href='https://deepinenespañol.org'>https://deepinenespañol.org</a><br/>"
            "<span style=' font-size:8pt; font-weight:600;'>Deepin Latin Code - developers</span>");
   dialog.setVersion(DApplication::buildVersion("Version 0.1"));
   dialog.setWebsiteName("deepinenespañol.org");
   dialog.setWebsiteLink("https://deepinenespañol.org");

   MainWindow w;
   w.show();

   Dtk::Widget::moveToCenter(&w);
   return a.exec();
}
