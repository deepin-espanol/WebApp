#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui
{
    class Widget;
}

class QWebEngineView;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QString szUrl = QString(), QWidget *parent = 0);
    ~Widget();

    void goBack();
    void goForward();
    void refresh();

private:
    Ui::Widget     *ui;
    QWebEngineView *m_webEngineView;
    QString         m_szUrl;
};

#endif // WIDGET_H
