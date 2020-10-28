#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QString szUrl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
    , m_szUrl(szUrl)
{
    ui->setupUi(this);

    if (!m_szUrl.isEmpty())
    {
        ui->webEngineView->setUrl(m_szUrl);
    }
}

Widget::~Widget()
{
    delete ui;
}
