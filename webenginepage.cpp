#include "webenginepage.h"

#include <QWebEngineSettings>

WebEnginePage::WebEnginePage(QObject *parent) : QWebEnginePage(parent)
{

}

QWebEnginePage *WebEnginePage::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type)
    WebEnginePage *page = new WebEnginePage();
    connect(page, &QWebEnginePage::urlChanged, this, &WebEnginePage::onUrlChanged);
    return page;
}

void WebEnginePage::onUrlChanged(const QUrl url)
{
    setUrl(url);
    sender()->deleteLater();
}
