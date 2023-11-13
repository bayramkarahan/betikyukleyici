#ifndef FUNCTION_H
#define FUNCTION_H
#include<appwidget.h>
#include<mainwindow.h>
void MainWindow::getIndex()
{
    system("rm -rf /tmp/betikyukleyiciscript");
    system("rm -rf /tmp/betikyukleyiciscript.zip");
    procesType="getindexscript";
    proces->start("wget  "+downloadAddress+"betikyukleyiciscript.zip -O /tmp/betikyukleyiciscript.zip");
    proces->waitForFinished(-1);


}
void MainWindow::uygulamaListeHazirla(QStringList list)
{
    appsListButton.clear();
    for(int i=0;i<list.count();i++)
    {

        QString line=list[i];
        if(line.length()>0)
        {
        QStringList lst=line.split("|");

        AppWidget * appsButton=new AppWidget(50,50);
        connect(appsButton, SIGNAL(installSignal(QString)),this, SLOT(installSlot(QString)));
        connect(appsButton, SIGNAL(removeSignal(QString)),this, SLOT(removeSlot(QString)));
        connect(appsButton, SIGNAL(appWidgetClickSignal(QString)),this, SLOT(selectPackageSlot(QString)));

        //appsButton->setFixedSize(butonGenislik,butonYukseklik);
        appsButton->paketAdiLabel->setText(lst[0]);
        appsButton->paketResmiYol=lst[1];
        appsButton->paketAciklama=lst[4];
        QString path="/var/lib/betikyukleyici/"+lst[0];
        QFile file(path);
        //qDebug()<<path<<file.exists();
        if(file.exists())
            appsButton->installStatus=true;
                else
            appsButton->installStatus=false;

        appsButton->setObjectName("appsButton");
        appsListButton.append(appsButton);


        }
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
            appsListButton[recordNumber-1]->AppWidgetResize(butonGenislik*1,butonYukseklik*0.9);
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
   /// appsListButton[0]->selectSlot();
      // return   appsListe;

}

void MainWindow::appWidgetfindTextEditChanged()
{
    //  qDebug()<<"tuşa basıldı..";
     localDir="/tmp/";
    QStringList list=fileToList("betikyukleyiciscript/betikyukleyiciappsindex.conf");
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
    // qDebug()<<"kategori seçildi.."<<data;
     localDir="/tmp/";
    QStringList list=fileToList("betikyukleyiciscript/betikyukleyiciappsindex.conf");
     if(data.length()>0&&data!="Tümü")
    {
        list=listGetList(list, data,0);
    }

    ///qDebug()<<"liste sayısı: "<<list.count()<<appsListButton.count();
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
           // appsListButton[i]->appsInstallButton->setFlat(false);
            //if(statusLabel)
            statusLabel->setText("Seçili Betik: "+paket+"\tBilgi: "+appsListButton[i]->paketAciklama);
        /***********************************************************************************************/
        /*************************install remove scriptler iniyor***************************************/
            doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Script İndirme Tamamlandı***</p>");
            // procesTypeStatus=3;
            localDir="/tmp/betikyukleyiciscript/";
            QStringList list1=fileToList(paket+"-install.sh");
            installscriptTextEdit->clear();
        int font=boy*2;
        for(int i=0;i<list1.count();i++)
        {
         QString line=list1[i];
        if(line!="")
        {
        // script->insertPlainText(line+"\n");
        installscriptTextEdit->textCursor().insertHtml("<br/><lu style=\"color:black;font-size:"+QString::number(font)+"px;\">"+line+"</lu>");

        }
        }
/*********************************************************************/
        /************************************************************************/
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Script İndirme Tamamlandı***</p>");
        //procesTypeStatus=3;
       localDir="/tmp/betikyukleyiciscript/";
        QStringList list2=fileToList(paket+"-remove.sh");
        removescriptTextEdit->clear();
       // int font=boy*2;
        for(int i=0;i<list2.count();i++)
        {
         QString line=list2[i];
        if(line!="")
        {
         // script->insertPlainText(line+"\n");
        removescriptTextEdit->textCursor().insertHtml("<br/><lu style=\"color:black;font-size:"+QString::number(font)+"px;\">"+line+"</lu>");

      }
      }
             /***********************************************************************************************/

        }
        else
        {
            appsListButton[i]->setStyleSheet("QWidget#appsButton{background-color: #ffffff; border:1px solid #dcdcdc;}");
            appsListButton[i]->select=false;
            appsListButton[i]->appsInstallButton->setVisible(false);
            appsListButton[i]->appsRemoveButton->setVisible(false);
         }
        appsListButton[i]->paketAdiLabel->setStyleSheet("QLabel{background-color: #ffffff; border:0px solid Red;}");
        appsListButton[i]->paketResmi->setStyleSheet("QLabel{background-color: #ffffff; border:0px solid Red;}");
        //appsListButton[i]->appsInstallButton->autoRaise();
       // appsListButton[i]->appsInstallButton->setStyleSheet("QToolButton#appsInstallButton{background-color: #ffffff; :disabled}");
       // appsListButton[i]->appsRemoveButton->setStyleSheet("QToolButton#appsRemoveButton{background-color: #ffffff; border:0px solid Red;}");

        QString ExButtonStyleSheet = "QToolButton#appsInstallButton,QToolButton#appsRemoveButton{background-color: #ffffff; border:0px solid Red;}\
            QToolButton#appsInstallButton:hover,QToolButton#appsRemoveButton:hover{background-color:#efefef;}\
            QToolButton#appsInstallButton:pressed,QToolButton#appsRemoveButton:pressed{background-color:#dcdcdc;}\
            QToolButton#appsInstallButton:disabled,QToolButton#appsRemoveButton:disabled{background-color:grey;}";

         appsListButton[i]->appsInstallButton->setStyleSheet(ExButtonStyleSheet);
         appsListButton[i]->appsRemoveButton->setStyleSheet(ExButtonStyleSheet);
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
        QStringList list=fileToList("betikyukleyiciscript/betikyukleyiciappsindex.conf");
       kategoriListButton.clear();
        QStringList groupList;
       for(int i=0;i<list.count();i++)
        {
            bool found=false;
            QString linet1=list[i];
            if(linet1.length()>0)
            {
            QStringList linet1lst=linet1.split("|");

            if(i==0){
            groupList.append("Tümü|all.svg");
            groupList.append(linet1lst[2]+"|"+linet1lst[3]);
            //qDebug()<<"group eklendi"<<linet1lst[2]+"|"+linet1lst[3];

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

                       // qDebug()<<"group eklendi-"<<linet1lst[2]+"|"+linet1lst[3];
                        groupList.append(linet1lst[2]+"|"+linet1lst[3]);
              }
            }
        }
      // qDebug()<<"group liste sayısı"<<groupList.count();
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
  //  qDebug()<<"kategori list"<<kategoriListButton.count();
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
    if (kategoriListButton.count()==0) return;
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

void MainWindow::installSlot(QString paket)
{
    qDebug()<<"Yüklenecek Paket: "<<paket;
            selectPaketName=paket;
         if(!QFile::exists("/tmp/betikyukleyiciscript/"+paket+"-install.sh"))
         {
             qDebug()<<"paket seçildi..";
             ///paketTableWidgetWindow_cellClicked(selectRowIndex, 0);
         }else
         {
         qDebug()<<"paket seçilmiş install başladı..";
         procesType="install";
         QString komut="chmod a+x /tmp/betikyukleyiciscript/"+paket+"-install.sh";
         system(komut.toStdString().c_str());
        proces->start("/tmp/betikyukleyiciscript/"+paket+"-install.sh");

         }

}
void MainWindow::removeSlot(QString paket)
{
         qDebug()<<"Kaldırılacak Paket: "<<paket;
   selectPaketName=paket;
         if(!QFile::exists("/tmp/betikyukleyiciscript/"+paket+"-remove.sh"))
         {
            qDebug()<<"paket seçildi..";
            //paketTableWidgetWindow_cellClicked(selectRowIndex, 0);
         }else
         {
            procesType="remove";

            QString komut="chmod a+x /tmp/betikyukleyiciscript/"+paket+"-remove.sh";
            system(komut.toStdString().c_str());

            proces->start("/tmp/betikyukleyiciscript/"+paket+"-remove.sh");
         }

}
void MainWindow::runEndPackageSlot(QString paket)
{

         selectPaketName="";
         for(int i=0;i<appsListButton.count();i++)
         {
            if(appsListButton[i]->paketAdiLabel->text()==paket)
            {
            qDebug()<<"işlem yapılan paket"<<paket;
            if(appsListButton[i]->installStatusLabel->isHidden())
            appsListButton[i]->installStatusLabel->hide();
            else
            appsListButton[i]->installStatusLabel->show();

         /*
            if(appsListButton[i]->installStatus==true)
                         appsListButton[i]->installStatusLabel->show();
            else
                         appsListButton[i]->installStatusLabel->hide();
*/
            }
         }

}
#endif // FUNCTION_H
