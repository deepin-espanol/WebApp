#include "widget.h"
#include "ui_widget.h"

#include <QWebEngineView>
#include "webenginepage.h"

Widget::Widget(QString szUrl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
    , m_webEngineView(nullptr)
    , m_szUrl(szUrl)
{
    ui->setupUi(this);

    m_webEngineView = new QWebEngineView(this);
    m_webEngineView->setObjectName(QStringLiteral("webEngineView"));
    m_webEngineView->setEnabled(true);
    m_webEngineView->setAutoFillBackground(false);
    m_webEngineView->setProperty("url", QVariant(QUrl(QStringLiteral(""))));
    m_webEngineView->setProperty("zoomFactor", QVariant(1));

    ui->verticalLayout->addWidget(m_webEngineView);

    WebEnginePage *page = new WebEnginePage();
    m_webEngineView->setPage(page);

    if (!m_szUrl.isEmpty())
    {
        m_webEngineView->setUrl(QUrl(m_szUrl));
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::goBack()
{
    if (m_webEngineView)
    {
        m_webEngineView->triggerPageAction(QWebEnginePage::Back);
    }
}

void Widget::goForward()
{
    if (m_webEngineView)
    {
        m_webEngineView->triggerPageAction(QWebEnginePage::Forward);
    }
}

void Widget::refresh()
{
    if (m_webEngineView)
    {
        m_webEngineView->triggerPageAction(QWebEnginePage::Reload);
    }
}
