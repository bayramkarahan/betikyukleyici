#ifndef FUNTION_H
#define FUNTION_H
#include<appwidget.h>
#include<mainwindow.h>
void MainWindow::getIndex()
{
    procesType="getindex";
    proces->start("wget  https://raw.githubusercontent.com/bayramkarahan/betikyukleyici/master/script/index.conf -O /usr/share/betikyukleyici/betikyukleyicilist");
    proces->waitForFinished(-1);

     localDir="/usr/share/betikyukleyici/";
    QStringList list=fileToList("betikyukleyicilist");
    for(int i=0;i<list.count();i++)
    {
        QString line=list[i];
        QStringList lst=line.split("|");

        AppWidget * appsButton=new AppWidget(50,50);
        connect(appsButton, SIGNAL(installSignal(QString)),this, SLOT(installSlot(QString)));
        connect(appsButton, SIGNAL(removeSignal(QString)),this, SLOT(removeSlot(QString)));
        connect(appsButton, SIGNAL(appWidgetClickSignal(QString)),this, SLOT(selectPackageSlot(QString)));

        //appsButton->setFixedSize(butonGenislik,butonYukseklik);
          appsButton->paketAdiLabel->setText(lst[0]);
        appsListButton.append(appsButton);

        appsButton->setStyleSheet("background-color: #ededed;/* border:1px solid black;*/");
      QString path="/var/lib/betikyukleyici/"+lst[0];
        QFile file(path);
        //qDebug()<<path<<file.exists();
   //     if(file.exists())
     //       appsButton->setStyleSheet("background-color: #cacaca;/* border:1px solid black;*/");
 // else
//            appsButton->setStyleSheet("background-color: #99dd99;/* border:1px solid black;*/");
    }

  /*  if(list.count()<1)
    {
        statusLabel->setText("İnternet Bağlantısı Yok veya Paket Listesi Yok");
        int font=boy*2;
        statusLabel->setStyleSheet("color: #ac0000;Text-align:center;font-size:"+QString::number(font)+"px");
    }*/
}

void   MainWindow::appWidgetfindTextEditChanged()
{
    //  qDebug()<<"tuşa basıldı..";
     localDir="/usr/share/betikyukleyici/";
    QStringList list=fileToList("betikyukleyicilist");
    if(findTextEdit->toPlainText().length()>0)
    {
        list=listGetList(list, findTextEdit->toPlainText(),0);
        // ldrm=1;
    }
    appsListButton.clear();
    for(int i=0;i<list.count();i++)
    {
        QString line=list[i];
        QStringList lst=line.split("|");

        AppWidget * appsButton=new AppWidget(50,50);
        connect(appsButton, SIGNAL(installSignal(QString)),this, SLOT(installSlot(QString)));
        connect(appsButton, SIGNAL(removeSignal(QString)),this, SLOT(removeSlot(QString)));
        connect(appsButton, SIGNAL(appWidgetClickSignal(QString)),this, SLOT(selectPackageSlot(QString)));

        //appsButton->setFixedSize(butonGenislik,butonYukseklik);
        appsButton->paketAdiLabel->setText(lst[0]);
        appsListButton.append(appsButton);

        appsButton->setStyleSheet("background-color: #ededed;/* border:1px solid black;*/");
        QString path="/var/lib/betikyukleyici/"+lst[0];
        QFile file(path);
        //qDebug()<<path<<file.exists();
        //     if(file.exists())
        //       appsButton->setStyleSheet("background-color: #cacaca;/* border:1px solid black;*/");
        // else
        //            appsButton->setStyleSheet("background-color: #99dd99;/* border:1px solid black;*/");
    }
    qDebug()<<"liste sayısı: "<<list.count()<<appsListButton.count();
}

void MainWindow::selectPackageSlot(QString paket)
{
    for(int i=0;i<appsListButton.count();i++)
    {
        if(appsListButton[i]->paketAdiLabel->text()==paket)
        {
            appsListButton[i]->setStyleSheet("QWidget#AppWidget{background-color: #ededed; border:3px solid Red;}");
            appsListButton[i]->select=true;
            appsListButton[i]->appsInstallButton->setVisible(true);
            appsListButton[i]->appsRemoveButton->setVisible(true);
            appsListButton[i]->appsInstallButton->setAutoRaise(false);
            appsListButton[i]->appsRemoveButton->setAutoRaise(false);
            appsListButton[i]->paketAdiLabel->setStyleSheet("QLabel{background-color: #ededed; border:0px solid Red;}");
            appsListButton[i]->appsInstallButtonLabel->setStyleSheet("QLabel{background-color: #ededed; border:0px solid Red;}");
            appsListButton[i]->appsRemoveButtonLabel->setStyleSheet("QLabel{background-color: #ededed; border:0px solid Red;}");
            appsListButton[i]->paketResmi->setStyleSheet("QLabel{background-color: #ededed; border:0px solid Red;}");


        }
        else
        {
            appsListButton[i]->setStyleSheet("QWidget#AppWidget{background-color: #ededed; border:0px solid Red;}");
            appsListButton[i]->select=false;
            appsListButton[i]->appsInstallButton->setVisible(false);
            appsListButton[i]->appsRemoveButton->setVisible(false);
            appsListButton[i]->paketAdiLabel->setStyleSheet("QLabel{background-color: #ededed; border:0px solid Red;}");
            //appsListButton[i]->appsRemoveButton->setAutoRaise(true);
           // appsListButton[i]->appsInstallButton->setAutoRaise(true);

        }
        appsListButton[i]->paketAdiLabel->setStyleSheet("QLabel{background-color: #ededed; border:0px solid Red;}");
        appsListButton[i]->appsInstallButtonLabel->setStyleSheet("QLabel{background-color: #ededed; border:0px solid Red;}");
        appsListButton[i]->appsRemoveButtonLabel->setStyleSheet("QLabel{background-color: #ededed; border:0px solid Red;}");
        appsListButton[i]->paketResmi->setStyleSheet("QLabel{background-color: #ededed; border:0px solid Red;}");


    }
}
#endif // FUNTION_H