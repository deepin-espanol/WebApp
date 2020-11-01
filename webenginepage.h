#ifndef WEBENGINEPAGE_H
#define WEBENGINEPAGE_H

#include <QWebEnginePage>
#include <QObject>

class WebEnginePage : public QWebEnginePage
{
public:
    WebEnginePage(QObject *parent = Q_NULLPTR);

protected:
    QWebEnginePage *createWindow(WebWindowType type) override;

public slots:
    void onUrlChanged(const QUrl);

};

#endif // WEBENGINEPAGE_H
