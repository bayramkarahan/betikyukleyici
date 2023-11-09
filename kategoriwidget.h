#ifndef KATEGORIWIDGET_H
#define KATEGORIWIDGET_H

#include <QWidget>
#include<QStyleOption>
#include<QPainter>
#include<QLabel>
#include<QToolButton>
#include<QMouseEvent>
#include<QDebug>

class KategoriWidget: public QWidget
{
    Q_OBJECT
public:

        explicit KategoriWidget(int w, int h,QWidget *parent = nullptr);
    QLabel *paketAdiLabel;
    QLabel *paketResmi;
    QString resimyol;
       bool select;
public slots:
    void KategoriWidgetResize(int w, int h);
    void selectSlot();


protected slots:
    void paintEvent(QPaintEvent *pe) override;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:
    void kategoriWidgetClickSignal(QString paket);

};

#endif // KATEGORIWIDGET_H
