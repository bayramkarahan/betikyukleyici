#ifndef APPWIDGET_H
#define APPWIDGET_H

#include <QWidget>
#include<QStyleOption>
#include<QPainter>
#include<QLabel>
#include<QToolButton>
#include<QMouseEvent>
#include<QDebug>
class AppWidget : public QWidget
{
    Q_OBJECT
public:
    QLabel *paketAdiLabel;
    QLabel *paketResmi;
    QToolButton * appsInstallButton;
    QToolButton * appsRemoveButton;
    QLabel * appsInstallButtonLabel;
    QLabel * appsRemoveButtonLabel;
    explicit AppWidget(int w, int h,QWidget *parent = nullptr);
    bool select;
public slots:
    void AppWidgetResize(int w, int h);
    void selectSlot();


protected slots:
    void paintEvent(QPaintEvent *pe) override;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:
void installSignal(QString paket);
void removeSignal(QString paket);
void appWidgetClickSignal(QString paket);

private:

};

#endif // APPWIDGET_H
