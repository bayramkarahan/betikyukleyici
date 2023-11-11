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
    paketResmi->setFixedSize(QSize(w*0.55,h*0.55));

    appsInstallButtonLabel=new QLabel(this);
    appsInstallButtonLabel->setFixedSize(QSize(w*0.5,h*0.5));
    appsInstallButtonLabel->setPixmap( QPixmap( ":/icons/betikyukleyici.svg" ) );
   appsInstallButtonLabel->setScaledContents( true );

    appsRemoveButtonLabel=new QLabel(this);
    appsRemoveButtonLabel->setFixedSize(QSize(w*0.5,h*0.5));
    appsRemoveButtonLabel->setPixmap( QPixmap( ":/icons/remove.svg" ) );
    appsRemoveButtonLabel->setScaledContents( true );

   // paketResmi->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    appsInstallButton= new QToolButton(this);
    appsInstallButton->setFixedSize(QSize(w*0.4,h*0.4));
    appsInstallButton->setIconSize(QSize(w*0.3,h*0.3));
    appsInstallButton->setStyleSheet("Text-align:center");
    appsInstallButton->setIcon(QIcon(":/icons/betikyukleyici.svg"));
    appsInstallButton->setAutoRaise(true);
   // appsInstallButton->setStyleSheet("background-color: #dadada; border:1px solid black;");
    appsInstallButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //appsInstallButton->setText("Betik"+QString::number(i)+". kodu");
   appsInstallButton->setVisible(false);
    connect(appsInstallButton, &QToolButton::clicked, [=]() {
        emit installSignal(paketAdiLabel->text());
         });

    appsRemoveButton= new QToolButton(this);
    appsRemoveButton->setFixedSize(QSize(w*0.4,h*0.4));
    appsRemoveButton->setIconSize(QSize(w*0.3,h*0.3));
    appsRemoveButton->setStyleSheet("Text-align:center");
    appsRemoveButton->setIcon(QIcon(":/icons/remove.svg"));
    appsRemoveButton->setAutoRaise(true);
    appsRemoveButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    appsRemoveButton->setVisible(false);
    //appsRemoveButton->setText("Betik"+QString::number(i)+". kodu");
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
   mainlayout->addWidget(appsInstallButtonLabel,4,1,1,1,Qt::AlignLeft);
   mainlayout->addWidget(appsRemoveButtonLabel,4,2,1,1,Qt::AlignRight);




//setLayout(mainlayout);

}

void AppWidget::AppWidgetResize(int w, int h)
{
   this->setFixedSize(w,h);

   appsInstallButton->setFixedSize(QSize(w*0.4,h*0.4));
   appsInstallButton->setIconSize(QSize(w*0.3,h*0.3));

   appsRemoveButton->setFixedSize(QSize(w*0.4,h*0.4));
   appsRemoveButton->setIconSize(QSize(w*0.3,h*0.3));
   paketAdiLabel->setFixedWidth(w*0.9);

}

void AppWidget::selectSlot()
{
   QPalette palet;

   qDebug()<<"tıklandıı";
   select=true;
   emit appWidgetClickSignal(paketAdiLabel->text());//nesneler arası data transferi***
   /*
      if(select){
        /*  palet.setColor(QPalette::Window, QColor(0,200,200,100));
          setPalette(palet);
          setAutoFillBackground(true);
*/
   //  setStyleSheet("background-color: #ff9999;");

   /*   }
      else{

         setStyleSheet("background-color: #dadada;");

    }*/
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
