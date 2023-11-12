#ifndef APPWIDGET_H
#define APPWIDGET_H

#include <QWidget>
#include<QStyleOption>
#include<QPainter>
#include<QLabel>
#include<QToolButton>
#include<QPushButton>
#include<QMouseEvent>
#include<QDebug>
class AppWidget : public QWidget
{
    Q_OBJECT
public:
    QLabel *paketAdiLabel;
    QLabel *paketResmi;
    QString paketResmiYol;
    QString paketAciklama;
    QToolButton * appsInstallButton;
    QToolButton * appsRemoveButton;
    QLabel * installStatusLabel;
    bool installStatus;
       bool select;
    explicit AppWidget(int w, int h,QWidget *parent = nullptr);

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
