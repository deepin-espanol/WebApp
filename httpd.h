#ifndef HTTPSD_H
#define HTTPSD_H

#include <QObject>

#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
#define SSL_SERVER 1
#else
#define SSL_SERVER 0
#endif

namespace httplib
{
    class Server;
#if SSL_SERVER
    class SSLServer;
#endif
}

class HttpD : public QObject
{
    Q_OBJECT
public:
#if SSL_SERVER
    explicit HttpD(QString szRootPath, quint16 u16Port, quint16 u16sslPort, QObject *parent = nullptr);
#else
    explicit HttpD(QString szRootPath, quint16 u16Port, QObject *parent = nullptr);
#endif

public slots:
    void start();
    void stop();

private:
    QString                 m_szRootPath;
#if SSL_SERVER
    httplib::SSLServer     *m_httpsServer;
    quint16                 m_u16HttpsServerBindPort;
#endif
    httplib::Server        *m_httpServer;
    quint16                 m_u16HttpServerBindPort;

};

#endif // HTTPSD_H
