#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui
{
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QString szUrl = QString(), QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QString m_szUrl;
};

#endif // WIDGET_H
