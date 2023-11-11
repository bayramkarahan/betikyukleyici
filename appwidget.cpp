#include "appwidget.h"
#include<QToolButton>
#include<QGridLayout>
#include<QLabel>

AppWidget::AppWidget(int w, int h, QWidget *parent)
    : QWidget{parent}
{
    setObjectName("AppWidget");
    this->setFixedSize(w,h);
    paketAdiLabel=new QLabel(this);
  //  setAutoFillBackground(false);
    paketAdiLabel->setObjectName("paketAdiLabel");
   // paketAdiLabel->setStyleSheet("QLabel#paketAdiLabel{ background-color:#ffffff; }");
    paketAdiLabel->setFixedWidth(w*0.9);
    paketAdiLabel->setAlignment(Qt::AlignCenter);
    QFont f;
    f.setPointSize(w*0.17);
    paketAdiLabel->setFont(f);
  //  paketAdiLabel->setStyleSheet("color: #ac0000;");
    paketResmi=new QLabel(this);
    paketResmi->setPixmap( QPixmap( ":/icons/betikyukleyici.svg" ) );
    paketResmi->setScaledContents( true );
    //paketResmi->setFixedSize(QSize(w*0.55,h*0.55));

      QFont ff;
    ff.setPointSize(w*0.14);
    appsInstallButton= new QToolButton(this);
    appsInstallButton->setFixedSize(QSize(w*0.2,h*0.2));
    appsInstallButton->setIconSize(QSize(w*0.25,h*0.25));
    appsInstallButton->setStyleSheet("Text-align:center");
    appsInstallButton->setIcon(QIcon(":/icons/betikyukleyici.svg"));
     appsInstallButton->setObjectName("appsInstallButton");
   // appsInstallButton->setAutoRaise(true);
   // appsInstallButton->setStyleSheet("background-color: #dadada; border:1px solid black;");
    appsInstallButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    appsInstallButton->setText("Yükle");
   appsInstallButton->setVisible(false);
    appsInstallButton->setFont(ff);
    connect(appsInstallButton, &QToolButton::clicked, [=]() {
        emit installSignal(paketAdiLabel->text());
         });

    appsRemoveButton= new QToolButton(this);
    appsRemoveButton->setFixedSize(QSize(w*0.30,h*0.3));
    appsRemoveButton->setIconSize(QSize(w*0.25,h*0.25));
    appsRemoveButton->setStyleSheet("Text-align:center");
    appsRemoveButton->setIcon(QIcon(":/icons/remove.svg"));
    appsRemoveButton->setAutoRaise(true);
    appsRemoveButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
     appsRemoveButton->setObjectName("appsRemoveButton");
    appsRemoveButton->setVisible(false);
    appsRemoveButton->setText("Kaldır");
    appsRemoveButton->setFont(ff);
   // appsRemoveButton->setStyleSheet("background-color: #dadada; border:1px solid black;");
    connect(appsRemoveButton, &QToolButton::clicked, [=]() {
        emit removeSignal(paketAdiLabel->text());

    });

   QGridLayout *mainlayout = new QGridLayout(this);
   mainlayout->setAlignment(Qt::AlignCenter);
   // mainlayout->setRowStretch(2,1);
   // mainlayout->setColumnStretch(2,1);
   mainlayout->setContentsMargins(0,0,5,0);
   mainlayout->setMargin(0);
   mainlayout->setSpacing(0);

   mainlayout->addWidget(paketAdiLabel,1,1,1,2,Qt::AlignCenter);
   mainlayout->addWidget(paketResmi,2,1,2,2,Qt::AlignCenter);
   mainlayout->addWidget(appsInstallButton,4,1,1,1,Qt::AlignLeft);
   mainlayout->addWidget(appsRemoveButton,4,2,1,1,Qt::AlignRight);
  // mainlayout->addWidget(appsInstallButtonLabel,4,1,1,1,Qt::AlignLeft);
  // mainlayout->addWidget(appsRemoveButtonLabel,4,2,1,1,Qt::AlignRight);




//setLayout(mainlayout);

}

void AppWidget::AppWidgetResize(int w, int h)
{
   this->setFixedSize(w,h);
   paketResmi->setPixmap( QPixmap( "/tmp/betikyukleyiciappsicons/"+paketResmiYol) );
  paketResmi->setFixedSize(h*0.45,h*0.45);

   appsInstallButton->setFixedSize(QSize(w*0.45,h*0.35));
   appsInstallButton->setIconSize(QSize(w*0.25,h*0.25));

   appsRemoveButton->setFixedSize(QSize(w*0.45,h*0.35));
   appsRemoveButton->setIconSize(QSize(w*0.25,h*0.25));
   paketAdiLabel->setFixedWidth(w*0.9);

}

void AppWidget::selectSlot()
{
   QPalette palet;
   //qDebug()<<"tıklandıı";
   select=true;
   emit appWidgetClickSignal(paketAdiLabel->text());//nesneler arası data transferi***
}
void AppWidget::paintEvent(QPaintEvent *pe)
{
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void AppWidget::mousePressEvent(QMouseEvent *event)
{
  selectSlot();

}
