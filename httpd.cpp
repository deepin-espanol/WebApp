#include "httpd.h"
#include "httplib.h"

#include <QtConcurrent>

#include <QDebug>

using namespace httplib;

#if SSL_SERVER
HttpD::HttpD(QString szRootPath, quint16 u16Port, quint16 u16sslPort, QObject *parent)
#else
HttpD::HttpD(QString szRootPath, quint16 u16Port, QObject *parent)
#endif
    : QObject(parent)
    , m_szRootPath(szRootPath)
#if SSL_SERVER
    , m_httpsServer(new SSLServer(g_szClientCert.toStdString().c_str(), g_szClientCertKey.toStdString().c_str()))
    , m_u16HttpsServerBindPort(u16sslPort)
#endif
    , m_httpServer(new Server())
    , m_u16HttpServerBindPort(u16Port)
{
#if SSL_SERVER
    m_httpsServer->set_idle_interval(0, 500 * 1000);
    m_httpsServer->set_read_timeout(1);
    m_httpsServer->set_write_timeout(1);
#endif

    m_httpServer->set_idle_interval(0, 500 * 1000);
    m_httpServer->set_read_timeout(1);
    m_httpServer->set_write_timeout(1);

#if SSL_SERVER
    auto ret = m_httpsServer->set_mount_point("/", m_szRootPath.toStdString().c_str());
    if (!ret)
    {
        qInfo("HTTP Server Mount root directory Fail!");
    }
    m_httpsServer->set_error_handler([](const Request &, Response & res)
    {
        auto fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
        char buf[BUFSIZ];
        snprintf(buf, sizeof(buf), fmt, res.status);
        res.set_content(buf, "text/html");
    });
#endif

    auto ret = m_httpServer->set_mount_point("/", m_szRootPath.toStdString().c_str());
    if (!ret)
    {
        qInfo("HTTP Server Mount root directory Fail!");
    }
    m_httpServer->set_error_handler([](const Request &, Response & res)
    {
        auto fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
        char buf[BUFSIZ];
        snprintf(buf, sizeof(buf), fmt, res.status);
        res.set_content(buf, "text/html");
    });
}

void HttpD::start()
{
#if SSL_SERVER
    QtConcurrent::run([&]
    {
        if (m_u16HttpsServerBindPort > 0)
        {
            CommonTools::outputLog(QString("HTTPS Server Startup with [%1] listen to %2 ...")
                                   .arg(m_szRootPath)
                                   .arg(m_u16HttpServerBindPort);
                                   m_httpsServer->listen("0.0.0.0", m_u16HttpsServerBindPort);
        }
    });
#endif
    QtConcurrent::run([&]
    {
        if (m_u16HttpServerBindPort > 0)
        {
            qInfo() << QString("HTTP Server Startup with [%1] listen to %2 ...")
                    .arg(m_szRootPath)
                    .arg(m_u16HttpServerBindPort);
            m_httpServer->listen("0.0.0.0", m_u16HttpServerBindPort);
        }
    });
}

void HttpD::stop()
{
#if SSL_SERVER
    m_httpsServer->stop();
#endif
    m_httpServer->stop();
}
