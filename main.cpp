/*
 *
 * 如果你想学习更多有关知识，可以访问以下网址：
 * DTK相关文档地址：https://linuxdeepin.github.io/dtk
 * Deepin项目地址：https://github.com/linuxdeepin
 * 社区项目投递地址：https://gitee.com/deepin-opensource
*/
#include "mainwindow.h"
#include <DApplication>
#include <DWidgetUtil>
#include <DAboutDialog>
#include <DMainWindow>

#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QTranslator>

#include <QFileInfo>
#include <QSettings>

#include "globaldefine.h"
#include "httpd.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    DAboutDialog dialog;
    a.loadTranslator();
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setApplicationName(DEFAULT_TITLE);
    a.setProductName(DEFAULT_TITLE);
    a.setAboutDialog(&dialog);

    //Title
    dialog.setWindowTitle(DEFAULT_TITLE);
    //descrition
    dialog.setProductName(QString("<span>%1</span>").arg(DEFAULT_TITLE));
    //Icons
    dialog.setProductIcon(QIcon(":/images/logo.svg"));
    //Organization logo
    dialog.setCompanyLogo(QPixmap(":/images/Logo-Racoon.png"));
    //about
    QString szDefaultDesc = QString("<span style=' font-size:8pt; font-weight:600;'>Deepin en Español </span>"
                                    "<a href='https://deepinenespañol.org'>https://deepinenespañol.org</a><br/>"
                                    "<span style=' font-size:8pt; font-weight:600;'>Deepin Latin Code - developers</span>");

    dialog.setDescription(szDefaultDesc);
    //Version
    dialog.setVersion(DApplication::buildVersion(QString("%1 %2").arg(QObject::tr("Version")).arg("1.0")));
    //Website name
    dialog.setWebsiteName("deepinenespañol.org");
    //Website link
    dialog.setWebsiteLink("https://deepinenespañol.org");

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

    QCommandLineOption optIcon(QStringList() << "i" << "ico",
                               QObject::tr("The ICON of Application."),
                               "ico",
                               DEFAULT_ICON);
    parser.addOption(optIcon);

    QCommandLineOption optDesc(QStringList() << "d" << "desc",
                               QObject::tr("The Description of Application."),
                               "desc",
                               DEFAULT_DESC);
    parser.addOption(optDesc);

    QCommandLineOption optCfgFile(QStringList() << "c" << "cfg",
                                  QObject::tr("The Configuration file of Application."),
                                  "cfg",
                                  DEFAULT_CFG);
    parser.addOption(optCfgFile);

    QCommandLineOption optRootPath(QStringList() << "r" << "root",
                                   QObject::tr("The root path of the program web service."),
                                   "root",
                                   DEFAULT_ROOT);
    parser.addOption(optRootPath);


    QCommandLineOption optPort(QStringList() << "P" << "port",
                               QObject::tr("The port number of the program web service."),
                               "port",
                               DEFAULT_PORT);
    parser.addOption(optPort);

#if SSL_SERVER
    QCommandLineOption optSSLPort(QStringList() << "s" << "sslport",
                                  QObject::tr("The ssl port number of the program web service."),
                                  "sslport",
                                  DEFAULT_PORT);
    parser.addOption(optSSLPort);
#endif

    parser.process(a);

    QString szTitle = DEFAULT_TITLE;
    QString szUrl = DEFAULT_URL;
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    QString szIcon = DEFAULT_ICON;
    QString szDesc = DEFAULT_DESC;
    QString szRootPath = DEFAULT_ROOT;
    quint16 u16Port = DEFAULT_PORT;
#if SSL_SERVER
    quint16 u16sslPort = 0;
#endif

    QString szCfgFile = DEFAULT_CFG;
    if (parser.isSet(optCfgFile))
    {
        szCfgFile = parser.value(optCfgFile);
        if (!szCfgFile.isEmpty())
        {
            QFileInfo fi(szCfgFile);
            if (fi.exists())
            {
                QSettings settings(szCfgFile, QSettings::IniFormat);
                szTitle = settings.value("WebApp/Title", DEFAULT_TITLE).toString();
                szUrl = settings.value("WebApp/URL", DEFAULT_TITLE).toString();
                width = settings.value("WebApp/Width", DEFAULT_WIDTH).toUInt();
                height = settings.value("WebApp/Height", DEFAULT_HEIGHT).toUInt();
                szIcon = settings.value("WebApp/Ico", DEFAULT_ICON).toString();
                szDesc = QString("%1<br/><br/>%2")
                         .arg(settings.value("WebApp/Desc", QString()).toString())
                         .arg(szDefaultDesc);
                szRootPath = settings.value("WebApp/RootPath", QString()).toString();
                u16Port = settings.value("WebApp/Port", 0).toUInt();
#if SSL_SERVER
                u16sslPort = settings.value("WebApp/SSLPort", 0).toUInt();
#endif
            }
        }
    }

    // Prioridad en el nivel de línea de comando, anular los ajustes del archivo de configuración
    if (parser.isSet(optTitle))
    {
        szTitle = parser.value(optTitle);
    }
    if (parser.isSet(optUrl))
    {
        szUrl = parser.value(optUrl);
    }
    if (parser.isSet(optWidth))
    {
        width = parser.value(optWidth).toInt();
    }
    if (parser.isSet(optHeight))
    {
        height = parser.value(optHeight).toInt();
    }

    if (parser.isSet(optDesc))
    {
        szDesc = QString("%1<br/><br/>%2").arg(parser.value(optDesc))
                 .arg(szDefaultDesc);
    }

    if (parser.isSet(optRootPath))
    {
        szRootPath = parser.value(optRootPath);
    }

    if (parser.isSet(optPort))
    {
        u16Port = parser.value(optPort).toUInt();
    }

#if SSL_SERVER
    if (parser.isSet(optSSLPort))
    {
        u16sslPort = parser.value(optSSLPort).toUInt();
    }
#endif
    if (!parser.isSet(optParser))
    {
        do
        {
            // La más alta prioridad en una jerarquía de orden fijo
#if SSL_SERVER
            if (argc != 10)
#else
            if (argc != 9)
#endif
            {
                break;
            }

            szTitle = argv[1];
            szUrl = argv[2];
            width = QString(argv[3]).toInt();
            height = QString(argv[4]).toInt();
            szIcon = QString(argv[5]);
            szDesc = QString("%1<br/><br/>%2").arg(QString(argv[6]))
                     .arg(szDefaultDesc);;
            szRootPath = QString(argv[7]);
            u16Port = QString(argv[8]).toUInt();
#if SSL_SERVER
            u16sslPort = QString(argv[9]).toUInt();
#endif
        }
        while (false);
    }

    MainWindow w(szTitle, szUrl, width, height);

#if SSL_SERVER
    if (!szRootPath.isEmpty() && u16Port > 0 && u16sslPort > 0)
    {
        HttpD httpd(szRootPath, u16Port, u16sslPort);
        httpd.start();
    }
#else
    if (!szRootPath.isEmpty() && u16Port > 0)
    {
        static HttpD httpd(szRootPath, u16Port);
        QObject::connect(&w, &MainWindow::sigQuit, &httpd, &HttpD::stop);
        httpd.start();
    }
#endif

    if (parser.isSet(optIcon))
    {
        szIcon = parser.value(optIcon);
    }

    if (!szIcon.isEmpty())
    {
        dialog.setIcon(QIcon(szIcon));
        dialog.setProductIcon(QIcon(szIcon));
        w.setIcon(szIcon);
    }
    if (!szDesc.isEmpty())
    {
        dialog.setDescription(szDesc);
    }

    w.show();

    Dtk::Widget::moveToCenter(&w);
    return a.exec();
}
