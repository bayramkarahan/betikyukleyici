#ifndef FUNCTION_H
#define FUNCTION_H
#include<appwidget.h>
#include<mainwindow.h>
void MainWindow::getIndex()
{
    procesType="getindex";
    proces->start("wget  https://github.com/bayramkarahan/betikyukleyici/raw/master/script/nindex.conf -O /tmp/index.conf");
    proces->waitForFinished(-1);

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
        appsButton->setObjectName("appsButton");

       // appsButton->setStyleSheet("QWidget#appsButton{background-color: #ffffff; border:1px solid black;}");

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
     localDir="/tmp/";
    QStringList list=fileToList("index.conf");
    if(findTextEdit->toPlainText().length()>0)
    {
        list=listGetList(list, findTextEdit->toPlainText(),0);
        // ldrm=1;
    }
    qDebug()<<"liste sayısı: "<<list.count()<<appsListButton.count();
    uygulamaListeHazirla(list);
    uygulamaListele();
}

void MainWindow::kategoriWidgetfindTextEditChanged(QString data)
{
     qDebug()<<"kategori seçildi.."<<data;
     localDir="/tmp/";
    QStringList list=fileToList("index.conf");
     if(data.length()>0&&data!="Tümü")
    {
        list=listGetList(list, data,0);
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
            appsListButton[i]->setStyleSheet("QWidget#appsButton{background-color: #ffffff; border:1px solid Red;}");
            appsListButton[i]->select=true;
            appsListButton[i]->appsInstallButton->setVisible(true);
            appsListButton[i]->appsRemoveButton->setVisible(true);
         }
        else
        {
            appsListButton[i]->setStyleSheet("QWidget#appsButton{background-color: #ffffff; border:0px solid Red;}");
            appsListButton[i]->select=false;
            appsListButton[i]->appsInstallButton->setVisible(false);
            appsListButton[i]->appsRemoveButton->setVisible(false);
         }
        appsListButton[i]->paketAdiLabel->setStyleSheet("QLabel{background-color: #ffffff; border:0px solid Red;}");
        appsListButton[i]->paketResmi->setStyleSheet("QLabel{background-color: #ffffff; border:0px solid Red;}");
        appsListButton[i]->appsInstallButtonLabel->setStyleSheet("QLabel{background-color: #ffffff; border:0px solid Red;}");
        appsListButton[i]->appsRemoveButtonLabel->setStyleSheet("QLabel{background-color: #ffffff; border:0px solid Red;}");
     }
}


void MainWindow::selectKategoriSlot(QString paket)
{
    for(int i=0;i<kategoriListButton.count();i++)
    {
        if(kategoriListButton[i]->paketAdiLabel->text()==paket)
        {
            kategoriListButton[i]->select=true;

            kategoriListButton[i]->setStyleSheet("QWidget#AppWidget{background-color: #ffffff; border:1px solid Red;}");
            kategoriWidgetfindTextEditChanged(paket);
        }
        else
        {
            kategoriListButton[i]->setStyleSheet("QWidget#AppWidget{background-color: #ffffff; border:0px solid Red;}");
            kategoriListButton[i]->select=false;

        }
        kategoriListButton[i]->paketAdiLabel->setStyleSheet("QLabel{background-color: #ffffff; border:0px solid Red;}");
        kategoriListButton[i]->paketResmi->setStyleSheet("QLabel{background-color: #ffffff; border:0px solid Red;}");


    }
}

void MainWindow::kategoriListele()
{
    if (kategoriListButton.count()==0)
    {
        localDir="/tmp/";
        QStringList list=fileToList("index.conf");
       kategoriListButton.clear();
        QStringList groupList;
       for(int i=0;i<list.count();i++)
        {
            bool found=false;
            QString linet1=list[i];  QStringList linet1lst=linet1.split("|");

            if(i==0){
            groupList.append("Tümü|all.svg");
            groupList.append(linet1lst[2]+"|"+linet1lst[3]);
            }

             for(int j=0;j<groupList.count();j++)
            {
                          QString glinet1=groupList[j];  QStringList glinet1lst=glinet1.split("|");
                          if(glinet1lst[0]==linet1lst[2])
                         {
                             found=true;
                             // qDebug()<<"group liste sayısı"<<linet1lst[4]<<groupList[j];
                          }

             }
              if(found==false)
             {

                        //  qDebug()<<"eklendi liste sayısı"<<linet1;
                        groupList.append(linet1lst[2]+"|"+linet1lst[3]);
              }
        }
       //qDebug()<<"group liste sayısı"<<groupList.count();
        for(int i=0;i<groupList.count();i++)
        {
            QString line=groupList[i];
            QStringList lst=line.split("|");

            KategoriWidget * kategoriButton=new KategoriWidget(50,50);
            connect(kategoriButton, SIGNAL(kategoriWidgetClickSignal(QString)),this, SLOT(selectKategoriSlot(QString)));

            //appsButton->setFixedSize(butonGenislik,butonYukseklik);
            kategoriButton->paketAdiLabel->setText(lst[0]);
            kategoriButton->resimyol=lst[1];
            kategoriListButton.append(kategoriButton);

          //  kategoriButton->setStyleSheet("background-color: #ededed;/* border:1px solid black;*/");
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
   // kategoriWidgetListe->setStyleSheet("background-color: #aaaadd");
    kategoriWidgetListe->setAutoFillBackground(false);
    /**************************************************/
    kategorilayout = new QGridLayout(kategoriWidget);
    kategorilayout->setContentsMargins(0, 0, 0,0);
    kategorilayout->setSpacing(0);

  //  kategoriWidgetListe->setLayout(kategorilayout);

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
    int butonGenislik=kategoriWidget->width()/(sutunSayisi);
    int butonYukseklik=kategoriWidget->height();

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
            kategoriListButton[recordNumber-1]->KategoriWidgetResize(butonGenislik*0.9,butonYukseklik*0.9);
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

void   MainWindow::findTextEditChanged()
{
    //  qDebug()<<"tuşa basıldı..";
    QStringList list=fileToList("betikyukleyicilist");
    if(findTextEdit->toPlainText().length()>0)
    {
        list=listGetList(list, findTextEdit->toPlainText(),0);
        // ldrm=1;
    }
    twl->setRowCount(0);
    for(int i=0;i<list.count();i++)
    {
        QString line=list[i];
        QStringList lst=line.split("|");
        twl->setRowCount(twl->rowCount()+1);

        twl->setItem(i, 0, new QTableWidgetItem(lst[0]));//package name
        twl->setItem(i, 1, new QTableWidgetItem(lst[3]));//package name

        QString path="/var/lib/betikyukleyici/"+lst[0];
        QFile file(path);
        //qDebug()<<path<<file.exists();
        if(file.exists())
            twl->setItem(i, 2, new QTableWidgetItem("Yüklü"));//package address
        else
            twl->setItem(i, 2, new QTableWidgetItem("-----"));//package address
    }
    //twl->selectRow(0);

    // paketTableWidgetWindow_cellClicked(0,0);
}
#endif // FUNCTION_H
