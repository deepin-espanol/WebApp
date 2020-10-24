#include "mainwindow.h"
#include <DApplication>
#include <DWidgetUtil>
#include <DAboutDialog>
#include <DMainWindow>

#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QMessageBox>

#include "globaldefine.h"
#include <QTranslator>

DWIDGET_USE_NAMESPACE
int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    DAboutDialog dialog;
    a.loadTranslator();
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setApplicationName(QObject::tr("WebApp"));
    a.setProductName(QObject::tr("WebApp"));
    a.setAboutDialog(&dialog);

    QCommandLineParser parser;

    parser.setApplicationDescription(QObject::tr("Description: %1").arg(DEFAULT_TITLE));
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption optParser(QStringList() << "p" << "parser",
                                 QObject::tr("Enable CommandLineParser. Default is false."));
    parser.addOption(optParser);

    QCommandLineOption optTitle(QStringList() << "t" << "title",
                                QObject::tr("The Title of Application. Default is %1.").arg(DEFAULT_TITLE),
                                "title",
                                DEFAULT_TITLE);
    parser.addOption(optTitle);

    QCommandLineOption optUrl(QStringList() << "u" << "url",
                              QObject::tr("The target URL. Default is Blank."),
                              "url",
                              DEFAULT_URL);
    parser.addOption(optUrl);

    QCommandLineOption optWidth(QStringList() << "w" << "width",
                                QObject::tr("The Width of Application. Default is %1.").arg(DEFAULT_WIDTH),
                                "width",
                                QString::number(DEFAULT_WIDTH));
    parser.addOption(optWidth);

    QCommandLineOption optHeight(QStringList() << "H" << "height",
                                 QObject::tr("The Height of Application. Default is %1").arg(DEFAULT_HEIGHT),
                                 "height",
                                 QString::number(DEFAULT_HEIGHT));
    parser.addOption(optHeight);

    parser.process(a);

    //Title
    dialog.setWindowTitle("WebApp");
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

    QString szTitle = parser.value(optTitle);
    QString szUrl = parser.value(optUrl);
    int width = parser.value(optWidth).toInt();
    int height = parser.value(optHeight).toInt();

    if (!parser.isSet(optParser))
    {
        // 按照固定顺序来
        if (argc != 5)
        {
            QMessageBox::information(nullptr, QObject::tr("Usage:"),
                                     QObject::tr("The first usage: \n"
                                                 "%1 %2\n"
                                                 "The second usage:\n"
                                                 "%1 %3")
                                     .arg(argv[0])
                                     .arg(QObject::tr("Title URL Width Height"))
                                     .arg(QObject::tr("-h to view parameter list.")));
            return 0;
        }

        szTitle = argv[1];
        szUrl = argv[2];
        width = QString(argv[3]).toInt();
        height = QString(argv[4]).toInt();
    }

    MainWindow w(szTitle, szUrl, width, height);
    w.show();

    Dtk::Widget::moveToCenter(&w);
    return a.exec();
}
