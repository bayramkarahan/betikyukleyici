#ifndef APPWIDGET_H
#define APPWIDGET_H

#include <QWidget>
#include<QStyleOption>
#include<QPainter>
#include<QLabel>
class AppWidget : public QWidget
{
    Q_OBJECT
public:
    QLabel *paketAdiLabel;
    explicit AppWidget(int w, int h,QWidget *parent = nullptr);
protected slots:
    void paintEvent(QPaintEvent *pe) override;

signals:
void installSignal(QString paket);
void removeSignal(QString paket);
private:

};

#endif // APPWIDGET_H
