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
void MainWindow::uygulamaListeHazirla(QStringList list)
{
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
}

void MainWindow::uygulamaListele()
{

    qDeleteAll(appsWidgetListe->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    if (appsListButton.count()==0) return;
    int appsSayisi=appsListButton.count();
    int sutunSayisi=8;
    int satir=appsSayisi/sutunSayisi;
    int mod=appsSayisi%sutunSayisi;
    if (mod!=0) satir++;
    int sutun=sutunSayisi;
    int sn=0;
    int butonGenislik=appsWidget->width()/(sutunSayisi*1.1);
    int butonYukseklik=appsWidget->height()/3;

    for(int i=1;i<=satir;i++)
    {
         for(int j=1;j<=sutunSayisi;j++)
         {
            int recordNumber;
            if (mod!=0&&satir==i)
                         recordNumber=(i-1)*sutunSayisi+j;
            else
                         recordNumber=(i-1)*sutunSayisi+j;
       //  appsListButton.append(appsButton);
            appsListButton[recordNumber-1]->AppWidgetResize(butonGenislik*0.9,butonYukseklik*0.9);
            appsListButton[recordNumber-1]->setAutoFillBackground(false);
            appslayout->addWidget(appsListButton[recordNumber-1], i,j,1,1);

            sn++;
            if (appsSayisi==sn) break;
         }
    }
    if (appsWidget->height()>satir*butonYukseklik)
    appsWidgetListe->setFixedSize(appsWidget->width()*0.99,appsWidget->height()*1.1);
         else
    appsWidgetListe->setFixedSize(appsWidget->width()*0.99,satir*butonYukseklik);

    //wapps->show();
    appsListButton[0]->selectSlot();
      // return   appsListe;

}

void MainWindow::appWidgetfindTextEditChanged()
{
    //  qDebug()<<"tuşa basıldı..";
     localDir="/usr/share/betikyukleyici/";
    QStringList list=fileToList("betikyukleyicilist");
    if(findTextEdit->toPlainText().length()>0)
    {
        list=listGetList(list, findTextEdit->toPlainText(),0);
        // ldrm=1;
    }
    qDebug()<<"liste sayısı: "<<list.count()<<appsListButton.count();
    uygulamaListeHazirla(list);
    uygulamaListele();
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

void MainWindow::kategoriListele()
{
    if (kategoriListButton.count()==0)
    {
        localDir="/usr/share/betikyukleyici/";
        QStringList list=fileToList("betikyukleyicilist");
       kategoriListButton.clear();
        for(int i=0;i<list.count();i++)
        {
            QString line=list[i];
            QStringList lst=line.split("|");

            KategoriWidget * kategoriButton=new KategoriWidget(50,50);
      //      connect(appsButton, SIGNAL(appWidgetClickSignal(QString)),this, SLOT(selectPackageSlot(QString)));

            //appsButton->setFixedSize(butonGenislik,butonYukseklik);
            kategoriButton->paketAdiLabel->setText(lst[0]);
            kategoriListButton.append(kategoriButton);

            kategoriButton->setStyleSheet("background-color: #ededed;/* border:1px solid black;*/");
            QString path="/var/lib/betikyukleyici/"+lst[0];
            QFile file(path);
            //qDebug()<<path<<file.exists();
            //     if(file.exists())
            //       appsButton->setStyleSheet("background-color: #cacaca;/* border:1px solid black;*/");
            // else
            //            appsButton->setStyleSheet("background-color: #99dd99;/* border:1px solid black;*/");
        }
    }
    qDebug()<<"apps list"<<kategoriListButton.count();
    kategoriWidgetListe=new QWidget(kategoriWidget);
    kategoriWidgetListe->setObjectName("appsListewidget");
    kategoriWidgetListe->setStyleSheet("background-color: #aaaadd");
    kategoriWidgetListe->setAutoFillBackground(false);
    /**************************************************/
    kategorilayout = new QGridLayout();
    kategorilayout->setContentsMargins(0, 0, 0,0);
    kategorilayout->setSpacing(3);
    kategoriWidgetListe->setLayout(kategorilayout);

/*******************************************************************/
    qDeleteAll(kategoriWidgetListe->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    if (appsListButton.count()==0) return;
    int kategoriSayisi=kategoriListButton.count();
    int sutunSayisi=8;
    int satir=kategoriSayisi/sutunSayisi;
    int mod=kategoriSayisi%sutunSayisi;
    if (mod!=0) satir++;
    int sutun=sutunSayisi;
    int sn=0;
    int butonGenislik=kategoriWidget->width()/(sutunSayisi*1.1);
    int butonYukseklik=kategoriWidget->height()/3;

    for(int i=1;i<=satir;i++)
    {
        for(int j=1;j<=sutunSayisi;j++)
        {
            int recordNumber;
            if (mod!=0&&satir==i)
                         recordNumber=(i-1)*sutunSayisi+j;
            else
                         recordNumber=(i-1)*sutunSayisi+j;
            //  appsListButton.append(appsButton);
            kategoriListButton[recordNumber-1]->AppWidgetResize(butonGenislik*0.9,butonYukseklik*0.9);
            kategoriListButton[recordNumber-1]->setAutoFillBackground(false);
            kategorilayout->addWidget(kategoriListButton[recordNumber-1], i,j,1,1);

            sn++;
            if (kategoriSayisi==sn) break;
        }
    }
    if (kategoriWidget->height()>satir*butonYukseklik)
        kategoriWidgetListe->setFixedSize(kategoriWidget->width()*0.99,kategoriWidget->height()*1.1);
    else
        kategoriWidgetListe->setFixedSize(kategoriWidget->width()*0.99,satir*butonYukseklik);

    //wapps->show();
  //  kategoriListButton[0]->selectSlot();
        // return   appsListe;
}
#endif // FUNTION_H
