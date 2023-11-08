#include "appwidget.h"
#include<QToolButton>
#include<QGridLayout>
#include<QLabel>

AppWidget::AppWidget(int w, int h, QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(w,h);
    paketAdiLabel=new QLabel(this);
    paketAdiLabel->setStyleSheet("QLabel { color : blue; }");

    QToolButton * appsInstallButton= new QToolButton(this);
    appsInstallButton->setFixedSize(QSize(w*0.4,h*0.4));
    appsInstallButton->setIconSize(QSize(w*0.3,h*0.3));
    appsInstallButton->setStyleSheet("Text-align:center");
    appsInstallButton->setIcon(QIcon(":/icons/betikyukleyici.svg"));
    //appsInstallButton->setAutoRaise(true);
   // appsInstallButton->setStyleSheet("background-color: #dadada; border:1px solid black;");
    appsInstallButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //appsInstallButton->setText("Betik"+QString::number(i)+". kodu");
    connect(appsInstallButton, &QToolButton::clicked, [=]() {
        emit installSignal(paketAdiLabel->text());
         });

    QToolButton * appsRemoveButton= new QToolButton(this);
    appsRemoveButton->setFixedSize(QSize(w*0.4,h*0.4));
    appsRemoveButton->setIconSize(QSize(w*0.3,h*0.3));
    appsRemoveButton->setStyleSheet("Text-align:center");
    appsRemoveButton->setIcon(QIcon(":/icons/remove.svg"));
   // appsRemoveButton->setAutoRaise(true);
    appsRemoveButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //appsRemoveButton->setText("Betik"+QString::number(i)+". kodu");
   // appsRemoveButton->setStyleSheet("background-color: #dadada; border:1px solid black;");
    connect(appsRemoveButton, &QToolButton::clicked, [=]() {
        emit removeSignal(paketAdiLabel->text());

    });



   QGridLayout *mainlayout = new QGridLayout(this);
    mainlayout->setAlignment(Qt::AlignCenter);
    // mainlayout->setRowStretch(2,1);
    // mainlayout->setColumnStretch(2,1);
    mainlayout->setContentsMargins(0,0,0,5);
    mainlayout->setMargin(0);
    mainlayout->setSpacing(0);
    mainlayout->addWidget(paketAdiLabel,0,1,1,2,Qt::AlignCenter);

    mainlayout->addWidget(appsInstallButton,1,1,1,1,Qt::AlignCenter);
    mainlayout->addWidget(appsRemoveButton,1,2,1,1,Qt::AlignCenter);
//setLayout(mainlayout);

}
void AppWidget::paintEvent(QPaintEvent *pe)
{
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
