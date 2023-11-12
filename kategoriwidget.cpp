#include "kategoriwidget.h"
#include<QToolButton>
#include<QGridLayout>
#include<QLabel>

KategoriWidget::KategoriWidget(int w, int h, QWidget *parent)
    : QWidget{parent}
{
    setObjectName("AppWidget");
    this->setFixedSize(w,h);
    paketAdiLabel=new QLabel(this);
    // setAutoFillBackground(true);
    paketAdiLabel->setObjectName("paketAdiLabel");
    //paketAdiLabel->setStyleSheet("QLabel#paketAdiLabel{ color : blue; }");
    paketAdiLabel->setFixedWidth(w*0.9);
    paketAdiLabel->setAlignment(Qt::AlignCenter);
    QFont f;
    f.setPointSize(w*0.17);
    paketAdiLabel->setFont(f);
    //paketAdiLabel->setStyleSheet("color: #ac0000;");
    paketResmi=new QLabel(this);
    paketResmi->setPixmap( QPixmap( ":/icons/betikyukleyici.svg" ) );
    paketResmi->setScaledContents( true );
    paketResmi->setFixedSize(QSize(w*0.55,h*0.45));

     QGridLayout *mainlayout = new QGridLayout(this);
    mainlayout->setAlignment(Qt::AlignCenter);
    // mainlayout->setRowStretch(2,1);
    // mainlayout->setColumnStretch(2,1);
    mainlayout->setContentsMargins(0,0,5,0);
    mainlayout->setMargin(0);
    mainlayout->setSpacing(0);

    mainlayout->addWidget(paketAdiLabel,1,1,1,2,Qt::AlignCenter);
    mainlayout->addWidget(paketResmi,2,1,2,2,Qt::AlignCenter);




    //setLayout(mainlayout);

}

void KategoriWidget::KategoriWidgetResize(int w, int h)
{
    this->setFixedSize(w,h);
    paketResmi->setPixmap( QPixmap( ":/icons/"+resimyol) );
    paketResmi->setFixedSize(h*0.7,h*0.65);
    paketAdiLabel->setFixedWidth(w*0.9);paketAdiLabel->setFixedHeight(h*0.3);

}

void KategoriWidget::selectSlot()
{
    QPalette palet;

    //qDebug()<<"tıklandıı";
    select=true;
    emit kategoriWidgetClickSignal(paketAdiLabel->text());//nesneler arası data transferi***
}
void KategoriWidget::paintEvent(QPaintEvent *pe)
{
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void KategoriWidget::mousePressEvent(QMouseEvent *event)
{
    selectSlot();

}
