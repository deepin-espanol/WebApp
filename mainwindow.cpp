#include "mainwindow.h"
#include <DMainWindow>
#include <DTitlebar>
#include <QtWidgets/QVBoxLayout>
#include <DToolButton>

#include <QFileInfo>

DWIDGET_USE_NAMESPACE

MainWindow::MainWindow(QString szTitle,
                       QString szUrl,
                       int nWidth,
                       int nHeight,
                       QWidget *parent)
    : DMainWindow(parent)
    , m_widget(nullptr)
{
    m_widget = new Widget(szUrl);

    setFixedSize(nWidth, nHeight);
    titlebar()->setTitle(szTitle);

    setCentralWidget(m_widget);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);

    titlebar()->setIcon(QIcon(":/images/logo.svg"));

    DToolButton *btnBack = new DToolButton(titlebar());
    btnBack->setIcon(QIcon(":/images/go-previous-24.svg"));
    btnBack->setIconSize(QSize(36, 36));
    DToolButton *btnForward = new DToolButton(titlebar());
    btnForward->setIcon(QIcon(":/images/go-next-24.svg"));
    btnForward->setIconSize(QSize(36, 36));
    DToolButton *btnRefresh = new DToolButton(titlebar());
    btnRefresh->setIcon(QIcon(":/images/view-refresh.svg"));
    btnRefresh->setIconSize(QSize(36, 36));

    connect(btnBack, &DToolButton::clicked, this, [&]()
    {
        if (m_widget)
        {
            m_widget->goBack();
        }
    });
    connect(btnForward, &DToolButton::clicked, this, [&]()
    {
        if (m_widget)
        {
            m_widget->goForward();
        }
    });
    connect(btnRefresh, &DToolButton::clicked, this, [&]()
    {
        if (m_widget)
        {
            m_widget->refresh();
        }
    });

    titlebar()->addWidget(btnBack, Qt::AlignLeft);
    titlebar()->addWidget(btnForward, Qt::AlignLeft);
    titlebar()->addWidget(btnRefresh, Qt::AlignLeft);
}

MainWindow::~MainWindow()
{
    emit sigQuit();
    if (m_widget)
    {
        delete m_widget;
        m_widget = nullptr;
    }
}

void MainWindow::setIcon(QString szIconPath)
{
    QFileInfo fi(szIconPath);
    if (fi.exists())
    {
        titlebar()->setIcon(QIcon(szIconPath));
        qDebug() << szIconPath << "is Set!";
    }
    else
    {
        qDebug() << szIconPath << "is Not Exists!";
    }
}
