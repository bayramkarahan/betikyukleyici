#include "mainwindow.h"
#include<QLabel>
#include<QLineEdit>
#include<QApplication>
#include<QScreen>
#include<QGridLayout>
#include<QToolButton>
#include<stdio.h>
#include<QDebug>
#include<hakkinda.h>
#include<function.h>
#include<process.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
       QSize screenSize = qApp->screens()[0]->size();
    // qDebug()<<"boyut"<<screenSize.height()*0.65<<screenSize.width()*0.5;
    boy=screenSize.height()/153;
    en=boy*1.1;
    //   qDebug()<<"en"<<en;
    int e=en;
    int b=boy;
    int pencereW=en*180;
    int pencereH=boy*125;
    int pencereNW=pencereW*0.99;
     int pencereNH=pencereH;
    this->setFixedSize(pencereW,pencereH);
    int x = (screenSize.width() - this->width())/2;
    int y = (screenSize.height() - this->height()) / 2;
    this->move(x, y);
/*****************************************************************************************/
    QWidget *anaWidget= new QWidget(this);
    anaWidget->setFixedSize(pencereW,pencereH);
    anaWidget->setObjectName("anaWidget");
    anaWidget->setStyleSheet("QWidget#anaWidget{background-color: #ffffff;}");

    aramaWidget=new QWidget(anaWidget);
    aramaWidget->setObjectName("aramaWidget");
    aramaWidget->setStyleSheet("QWidget#aramaWidget{/*background-color: #44ff22;*/border-bottom:2px solid #dcdcdc;}");
    aramaWidget->setFixedSize(pencereNW,pencereNH*0.05);

    kategoriWidget=new QWidget(anaWidget);
    kategoriWidget->setObjectName("kategoriWidget");
    kategoriWidget->setStyleSheet("QWidget#kategoriWidget{/*background-color: #00ffaa;*/border-bottom:2px solid #dcdcdc;}");
    kategoriWidget->setFixedSize(pencereNW,pencereNH*0.10);

    appsWidget=new QWidget(anaWidget);
    appsWidget->setObjectName("appsWidget");
    //appsWidget->setStyleSheet("QWidget#appsWidget{/*background-color: #ffffaa;border-bottom:2px solid #dc0000;*/}");
    appsWidget->setFixedSize(pencereNW,pencereNH*0.55);

    scriptWidget=new QWidget(anaWidget);
    scriptWidget->setStyleSheet("background-color: #ffffff;");
    scriptWidget->setFixedSize(pencereNW,pencereNH*0.25);

    progressbar = new QProgressBar(anaWidget);
    progressbar->setFixedSize(pencereNW,pencereNH*0.04);
    progressbar->setRange(0,100);
    progressbar->setStyleSheet("background-color: #ffffff;");

    auto layout = new QGridLayout(anaWidget);
    layout->setContentsMargins(0,0, 0,0);
   layout->setSpacing(0);

  //this->centralWidget->setLayout (layout);
   // anaWidget->setLayout(layout);
    localDir="/usr/share/betikyukleyici/";
    version="betikyukleyici_1.6.0_amd64.deb";
    system("rm -rf /tmp/version");
    system("rm -rf /tmp/installscript.sh");
    system("rm -rf /tmp/removescript.sh");
    /**************************************************************/
    proces=new QProcess(this);
    proces->setReadChannelMode(QProcess::MergedChannels);
    proces->setReadChannel(QProcess::StandardOutput);

    connect(proces, SIGNAL(readyReadStandardOutput()),this, SLOT(disp()));
    connect(proces, SIGNAL(started()), this, SLOT(procresbegin()));
    connect(proces, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(procresend()));

    proces1=new QProcess(this);
    proces1->setReadChannelMode(QProcess::MergedChannels);
    proces1->setReadChannel(QProcess::StandardOutput);

    connect(proces1, SIGNAL(readyReadStandardOutput()),this, SLOT(disp()));
    connect(proces1, SIGNAL(started()), this, SLOT(procresbegin()));
    connect(proces1, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(procresend()));

    /**************************************************************/


    QTabWidget *tabw=new QTabWidget(scriptWidget);
    tabw->setFixedSize(pencereNW,pencereNH);


    doc=new QTextEdit(tabw);
    doc->setFixedSize(pencereNW,pencereNH);
    doc->setReadOnly(true);

    installscriptTextEdit=new QTextEdit(tabw);
    installscriptTextEdit->setFixedSize(pencereNW,pencereNH);
    installscriptTextEdit->setReadOnly(true);

    removescriptTextEdit=new QTextEdit(tabw);
    removescriptTextEdit->setFixedSize(pencereNW,pencereNH);
    removescriptTextEdit->setReadOnly(true);

  //  doc->setStyleSheet("background-color: #dfdfdf;");
    tabw->addTab(installscriptTextEdit,"Yükleme Betiği");
    tabw->addTab(removescriptTextEdit,"Kaldırma Betiği");

    tabw->addTab(doc,"Süreç");
   // tabw->setTabPosition(QTabWidget::West);
  //  mwidget->setFixedSize(en*120,boy*125);
  // this->setStyleSheet("background-color: #00df00;");

    auto appIcon = QIcon(":/icons/betikyukleyici.svg");
    this->setWindowIcon(appIcon);
  this->setWindowTitle("Betik Yükleyici");

    font=boy*2;
    int fontt=font*1;
    statusLabel=new QLabel(aramaWidget);
    statusLabel->setText("Yüklenebilecek Paketler");
    statusLabel->setStyleSheet("color: #000000;font-size:"+QString::number(font)+"px");

     statusLabel->setFixedSize(aramaWidget->width()*0.42,aramaWidget->height()*0.9);
    //statusLabel->setAlignment(Qt::AlignLeft);


    findTextEditLabel=new QLabel(aramaWidget);
    findTextEditLabel->setText("Paket Ara");
    //findTextEditLabel->setStyleSheet("background-color: #0000ac;");
    findTextEditLabel->setStyleSheet("color: #000000;font-size:"+QString::number(font)+"px");
    findTextEditLabel->setFixedSize(aramaWidget->width()*0.06,aramaWidget->height()*0.9);
  //  findTextEditLabel->setAlignment(Qt::AlignLeft);

    findTextEdit=new QTextEdit(aramaWidget);
    findTextEdit->setFixedSize(aramaWidget->width()*0.30,aramaWidget->height()*0.80);

    findTextEdit->setStyleSheet("color: #000000;font-size:"+QString::number(font)+"px");

 //connect(findTextEdit, SIGNAL(textChanged()), this, SLOT(findTextEditChanged()));
    connect(findTextEdit, SIGNAL(textChanged()), this, SLOT(appWidgetfindTextEditChanged()));

 updateButton= new QToolButton(aramaWidget);
 updateButton->setFixedSize(aramaWidget->width()*0.20,aramaWidget->height()*0.9);
 updateButton->setIconSize(QSize(aramaWidget->width()*0.20,aramaWidget->height()*0.9));
 updateButton->setStyleSheet("Text-align:center");
 updateButton->setIcon(QIcon(":/icons/update.svg"));
 updateButton->setAutoRaise(true);
 updateButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
 updateButton->setStyleSheet("color: #000000;font-size:"+QString::number(font)+"px");

 updateButton->setText("Programı Güncelle");

 connect(updateButton, &QToolButton::clicked, [=]() {
     if (updateFile=="") return;
     QString kmt="wget -O /tmp/prg.deb https://github.com/bayramkarahan/betikyukleyici/raw/master/"+updateFile;
     system(kmt.toStdString().c_str());
      system("sleep 1");
     system("chmod 777 /tmp/prg.deb");
      system("sleep 1");
     system("dpkg -i --force-all /tmp/prg.deb");
      //system("sleep 2");
     //system("rm  /tmp/prg.deb");
 });

 QGridLayout *aramalayout = new QGridLayout(aramaWidget);
//aramalayout->setSpacing(0);
aramalayout->setContentsMargins(0,0,0,0);
 aramalayout->addWidget(findTextEditLabel,1,1,1,1,Qt::AlignCenter);
 aramalayout->addWidget(findTextEdit,1,2,1,1,Qt::AlignCenter);
 aramalayout->addWidget(statusLabel,1,3,1,1,Qt::AlignCenter);
 aramalayout->addWidget(updateButton,1,4,1,1,Qt::AlignCenter);

    // layout->setVerticalSpacing(0);
   //  layout->setHorizontalSpacing(10);
    //layout->setColumnMinimumWidth(0, 37);
   // QWidget *paket = paketSlot(mwidget);
      //QWidget *appsWidget =
      // appList(appsListWidget);
/**********************ilk Liste oluşturma***************************************/
/**********************ilk Liste oluşturma***************************************/
 getIndex();
        if (appsListButton.count()==0)
        {
            localDir="/tmp/";
            QStringList list=fileToList("index.conf");
            uygulamaListeHazirla(list);
        }
        qDebug()<<"apps list"<<appsListButton.count();
        appsWidgetListe=new QWidget(appsWidget);
        appsWidgetListe->setObjectName("appsListewidget");
        appsWidgetListe->setStyleSheet("background-color: #ffffff");
        //appsWidgetListe->setAutoFillBackground(false);
        /**************************************************/
        appslayout = new QGridLayout();
        appslayout->setContentsMargins(0, 0, 0,0);
        appslayout->setSpacing(0);
        appsWidgetListe->setLayout(appslayout);

        uygulamaListele();
        /*****************************************************************/
        /*****************************************************************/
        kategoriListele();
/*****************************************************************/
/*****************************************************************/

      QScrollArea *appsWidgetscrollArea=new QScrollArea(appsWidget);
      appsWidgetscrollArea->setFixedSize(appsWidget->width(),appsWidget->height());
      appsWidgetscrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      appsWidgetscrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
      appsWidgetscrollArea->setStyleSheet("border:0;border-bottom:2px solid #dcdcdc;");
      appsWidgetscrollArea->setWidget(appsWidgetListe);

    layout->addWidget(aramaWidget,1,1,1,1,Qt::AlignCenter);
    layout->addWidget(kategoriWidget,2,1,1,1,Qt::AlignCenter);
    layout->addWidget(appsWidget,3,1,1,1,Qt::AlignCenter);
    layout->addWidget(scriptWidget,4,1,1,1,Qt::AlignCenter);
   layout->addWidget(progressbar,5,1,1,1,Qt::AlignCenter);


  /****************versiyon kontrolü yapılıyor***********************************************/
  //system("wget https://github.com/bayramkarahan/betikyukleyici/raw/master/debian/files -O /tmp/version");
  /*procesType="getversion";
  QString kmt="wget https://github.com/bayramkarahan/betikyukleyici/raw/master/debian/files -O /tmp/version";
  proces->start(kmt);
  proces->waitForFinished(-1);
  /****************index listesi çekiliyor***********************************************/
  // system("wget  https://raw.githubusercontent.com/bayramkarahan/betikyukleyici/master/index.conf -O /usr/share/betikyukleyici/betikyukleyicilist");
 /* procesType="getindex";
  proces->start("wget  https://raw.githubusercontent.com/bayramkarahan/betikyukleyici/master/script/index.conf -O /usr/share/betikyukleyici/betikyukleyicilist");
  proces->waitForFinished(-1);

  /***************************************************************/
 // paketTableWidgetWindow_cellClicked(0, 0);
}

void   MainWindow::about(){
    QSize screenSize = qApp->screens()[0]->size();
   // qDebug()<<screenSize.width()/65<<screenSize.height()/35;

    QWidget *hk=hakkinda();

    hk->show();
    hk->move(screenSize.width()/2-hk->width()/2,screenSize.height()/2-hk->height()/2);
     hk->setWindowTitle("Betik Yükleyici");
     auto appIcon = QIcon(":/icons/about.svg");
     hk->setWindowIcon(appIcon);



}
MainWindow::~MainWindow()
{

}

QWidget *MainWindow::paketSlot(QWidget *parent)
{
   // qDebug()<<"ayar click";
    QString font="12";
    QWidget * d = new QWidget(parent);
  //  d->setStyleSheet("background-color: #dfdfdf;");


    /***********************************************************************/
   twl=new QTableWidget(d);
    twl->setFixedSize(QSize(en*120,boy*55));
    twl->setColumnCount(3);
    //twl->setRowCount(0);
    twl->setColumnWidth(0, en*35);
     twl->setColumnWidth(1, en*55);
    twl->setColumnWidth(2, en*10);

    twl->setHorizontalHeaderItem(0, new QTableWidgetItem("Paket Adı"));
    twl->setHorizontalHeaderItem(1, new QTableWidgetItem("Açıklama"));

   twl->setHorizontalHeaderItem(2, new QTableWidgetItem("Drm"));

    twl->setSelectionBehavior(QAbstractItemView::SelectRows);
    twl->setSelectionMode(QAbstractItemView::SingleSelection);
     //connect(twl, SIGNAL(cellDoubleClicked(int,int)),SLOT(paketTableCellDoubleClicked(int,int)));
    connect(twl, SIGNAL(cellClicked(int, int)),
            this, SLOT(paketTableWidgetWindow_cellClicked(int, int)));

    twl->setRowCount(0);


 installerButton= new QToolButton(d);
 installerButton->setFixedSize(QSize(en*35,boy*10));
 installerButton->setIconSize(QSize(en*35,boy*5));
 installerButton->setStyleSheet("Text-align:center");
 installerButton->setIcon(QIcon(":/icons/betikyukleyici.svg"));
 installerButton->setAutoRaise(true);
 installerButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
 // powerOnButton->setFont(f2);
 installerButton->setText("Betik Yükle");

 connect(installerButton, &QToolButton::clicked, [=]() {

     if(selectPaketName!=""&&selectPaketAddressInstall!="")
     {
         if(!QFile::exists("/tmp/installscript.sh"))
         {
             qDebug()<<"paket seçildi..";
             paketTableWidgetWindow_cellClicked(selectRowIndex, 0);
         }else
         {
              qDebug()<<"paket seçilmiş install başladı..";
         procesType="install";
        system("chmod a+x /tmp/installscript.sh");
        proces->start("/tmp/installscript.sh");

         }
     }else
     {
         statusLabel->setText("Paket Seçilmemiş");
         int font=boy*2;
         qDebug()<<"paket seçilmemiş..";
         //   statusLabel->setStyleSheet("color: #ac0000;Text-align:center;font-size:"+QString::number(font)+"px");

     }

 });


 removeButton= new QToolButton(d);
 removeButton->setFixedSize(QSize(en*35,boy*10));
 removeButton->setIconSize(QSize(en*35,boy*5));
 removeButton->setStyleSheet("Text-align:center");
 removeButton->setIcon(QIcon(":/icons/remove.svg"));
 removeButton->setAutoRaise(true);
 removeButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
 // powerOnButton->setFont(f2);
 removeButton->setText("Betik Kaldır");

 connect(removeButton, &QToolButton::clicked, [=]() {

     if(selectPaketName!=""&&selectPaketAddressInstall!="")
     {
         if(!QFile::exists("/tmp/removescript.sh"))
         {
             paketTableWidgetWindow_cellClicked(selectRowIndex, 0);
         }else
         {
         procesType="remove";
         system("chmod a+x /tmp/removescript.sh");
         proces->start("/tmp/removescript.sh");
         }
     }else
     {
         statusLabel->setText("Paket Seçilmemiş");
         int font=boy*2;
         // statusLabel->setStyleSheet("color: #ac0000;Text-align:center;font-size:"+QString::number(font)+"px");
     }

 });
 aboutButton= new QToolButton(d);
 aboutButton->setFixedSize(QSize(en*35,boy*10));
 aboutButton->setIconSize(QSize(en*35,boy*5));
 aboutButton->setStyleSheet("Text-align:center");
 aboutButton->setIcon(QIcon(":/icons/about.svg"));
 aboutButton->setAutoRaise(true);
 aboutButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
 // powerOnButton->setFont(f2);
 aboutButton->setText("Hakkında");

 connect(aboutButton, &QToolButton::clicked, [=]() {
//about();
    // getIndex();



});
 QHBoxLayout *btnlayout = new QHBoxLayout;
 btnlayout->addWidget(installerButton);
 btnlayout->addWidget(removeButton);
 btnlayout->addWidget(aboutButton);

     auto dlayout = new QGridLayout(d);
 dlayout->setContentsMargins(0,0, 0,0);
 //dlayout->setVerticalSpacing();
 //dlayout->setHorizontalSpacing(0);

     dlayout->addWidget(twl, 6,1,1,2,Qt::AlignCenter);
     dlayout->addLayout(btnlayout, 7,1,1,2,Qt::AlignCenter);


     /*dlayout->addWidget(installerButton, 7,1,1,1,Qt::AlignCenter);
     dlayout->addWidget(removeButton, 7,2,1,1,Qt::AlignCenter);
     dlayout->addWidget(aboutButton, 7,3,1,1,Qt::AlignCenter);
*/
d->setLayout(dlayout);

return d;
   // int result = d->exec();
}
void MainWindow::paketTableWidgetWindow_cellClicked(int iRow, int iColumn)
{
   // qDebug()<<"satır seçildi"<<iRow;
    int ldrm=0;
    if(QFile::exists("/usr/share/betikyukleyici/betikyukleyicilist"))
    {
    QString paketname= twl->item(iRow, 0)->text();
    QStringList list=fileToList("betikyukleyicilist");
  /*  if(findTextEdit->toPlainText().length()>0)
    {
        list=listGetList(list, findTextEdit->toPlainText(),0);
       // ldrm=1;
    }*/
    for(int i=0;i<list.count();i++)
    {
        QString line=list[i];
        QStringList lst=line.split("|");
        if(paketname==lst[0])
        {
           /// qDebug()<<"seçilen paket"<<lst[0]<<lst[1];
            selectPaketName=lst[0];
           if(lst.count()>1) selectPaketAddressInstall=lst[1];
          // qDebug()<<lst.count();
           if(lst.count()>2) selectPaketAddressRemove=lst[2];

                     statusLabel->setText("Paket: "+selectPaketName);
                   //  int font=boy*2;
                    // statusLabel->setStyleSheet("color: #0000ac;Text-align:center;font-size:"+QString::number(font)+"px");
                     statusLabel->setStyleSheet("color: #ac0000;Text-align:center;");

                     selectRowIndex=iRow;
        }
    }

///qDebug()<<"paket adı: "<<selectPaketAddressInstall;
 ///   proces->terminate();

    /*********************************************************************/
     procesType="getscriptinstall";
     QString kmt="wget -O /tmp/installscript.sh "+selectPaketAddressInstall;
     proces->start(kmt);
    proces->waitForFinished(-1);

     procesType="getscriptremove";
     kmt="wget -O /tmp/removescript.sh "+selectPaketAddressRemove;
     proces->start(kmt);
     proces->waitForFinished(-1);
    /*********************************************************************/

}
}
void MainWindow::paketTableCellDoubleClicked(int iRow, int iColumn)
{
QString paketname= twl->item(iRow, 0)->text();
QStringList list=fileToList("betikyukleyicilist");
/******************************************************************/
//QMessageBox::StandardButton reply;
// reply = QMessageBox::question(this, "Uyarı", "Bilgisayar Silinecek! Emin misiniz?",
//                             QMessageBox::Yes|tr(QMessageBox::No);
QMessageBox messageBox(this);
messageBox.setText("Uyarı");
    messageBox.setInformativeText("Paket Listesi İşlem Seçiniz!");
QAbstractButton *evetButton =messageBox.addButton(tr("Sil"), QMessageBox::ActionRole);
QAbstractButton *hayirButton =messageBox.addButton(tr("Düzenle"), QMessageBox::ActionRole);
                               messageBox.setIcon(QMessageBox::Question);
messageBox.exec();
if (messageBox.clickedButton() == evetButton) {
     // qDebug()<<"evet basıldı";
     list=listRemove(list,paketname);
     listToFile(list,"betikyukleyicilist");
     if(list.count()==0) twl->setRowCount(0);
     for(int i=0;i<list.count();i++)
     {
        QString line=list[i];
        QStringList lst=line.split("|");
        twl->setRowCount(i+1);
        twl->setItem(i, 0, new QTableWidgetItem(lst[0]));//package name
        twl->setItem(i, 1, new QTableWidgetItem(lst[1]));//package address
     }
}
if (messageBox.clickedButton() == hayirButton) {
     //qDebug()<<"hayır basıldı";
}


}



 void MainWindow::installSlot(QString paket)
 {
     qDebug()<<"Yüklenecek Paket: "<<paket;
 }
 void MainWindow::removeSlot(QString paket)
 {
     qDebug()<<"Kaldırılacak Paket: "<<paket;
 }

QStringList MainWindow::listMerge(QStringList list1, QStringList list2, int dataIndex)
{
    for(int i=0;i<list1.count();i++)
    {
        QString line=list1[i];
        if(line!="")
        {

            QStringList lst=line.split("|");
            list2=listRemove(list2,lst[dataIndex]);
        }
    }
    for(int i=0;i<list1.count();i++)
    {
       list2.append(list1[i]);
    }
    return list2;
}
QStringList MainWindow::listReplace(QStringList list, QString oldData, QString newData, int index)
 {
    QStringList liste;
         QRegularExpression re(oldData);
     for(int i=0;i<list.count();i++)
     {
         if(list[i].contains(re))
         {
             QStringList lst=list[i].split("|");
             lst[index].replace(oldData, newData);
            // qDebug()<<lst;

             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);
             if(lst.count()>6)ln.append("|").append(lst[4]);
             if(lst.count()>7)ln.append("|").append(lst[7]);
             if(lst.count()>8)ln.append("|").append(lst[8]);
             if(lst.count()>9)ln.append("|").append(lst[9]);
            // list.removeAt(i);
             liste.append(ln);
         }
     }
    // qDebug()<<list;
     return liste;
 }
QStringList MainWindow::listGetList(QStringList list, QString data,int index)
 {
    QStringList liste;
    QRegularExpression re(data);
     for(int i=0;i<list.count();i++)
     {
         if(list[i].contains(re))
         {
            liste.append(list[i]);

         }
     }
    // qDebug()<<list;
     return liste;
 }
QStringList MainWindow::listRemove(QStringList list,QString data)
 {
         QRegularExpression re(data);
     for(int i=0;i<list.count();i++)if(list[i].contains(data)) list.removeAt(i);
    // qDebug()<<list;
     return list;
 }
QString MainWindow::listGetLine(QStringList list,QString data)
 {
         QRegularExpression re(data);
     for(int i=0;i<list.count();i++) if(list[i].contains(re)) return list[i];
     //qDebug()<<list;
     return "";
 }
QStringList MainWindow::fileToList(QString filename)
 {
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+filename;
    QStringList list;
    for(int i=1;i<=fcc->fileCount();i++)
    {
         QString line=fcc->fileGetLine(i);
         if(line!="")
         {
             line.chop(1);
             QStringList lst=line.split("|");
             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);
             if(lst.count()>6)ln.append("|").append(lst[4]);
             if(lst.count()>7)ln.append("|").append(lst[7]);
             if(lst.count()>8)ln.append("|").append(lst[8]);
             if(lst.count()>9)ln.append("|").append(lst[9]);

             list <<ln;
            // qDebug()<<ln;
             // list <<lst[0]+"|"+lst[1]+"|"+lst[2]+"|"+lst[3]+"|"+lst[4]+"|"+lst[5];

         }
    }
        return list;
 }
void MainWindow::listToFile(QStringList list, QString filename)
 {
  //  qDebug()<<" listtofile";
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+filename;
    //QStringList list;
    fcc->fileRemove();
    for(int i=0;i<list.count();i++)
    {
         QString line=list[i];
         if(line!="")
         {
             //line.chop(1);
             QStringList lst=line.split("|");
             //qDebug()<<line;
             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);
             if(lst.count()>6)ln.append("|").append(lst[4]);
             if(lst.count()>7)ln.append("|").append(lst[7]);
             if(lst.count()>8)ln.append("|").append(lst[8]);
             if(lst.count()>9)ln.append("|").append(lst[9]);

             //qDebug()<<ln;
             fcc->fileWrite(ln);
            // fcc->fileWrite(lst[0]+"|"+lst[1]+"|"+lst[2]+"|"+lst[3]+"|"+lst[4]+"|"+lst[5]);

         }

    }
/********************file permission*************************/
   QFile file(localDir+filename);
    if (file.open(QFile::ReadWrite)){
            if(!file.setPermissions(QFileDevice::WriteUser | QFileDevice::ReadUser|QFileDevice::ExeUser|
                                    QFileDevice::WriteOwner | QFileDevice::ReadOwner|QFileDevice::ExeOwner|
                                    QFileDevice::WriteGroup | QFileDevice::ReadGroup|QFileDevice::ExeGroup|
                                    QFileDevice::WriteOther | QFileDevice::ReadOther|QFileDevice::ExeOther)){
                qDebug()<< "Error in permissions";
             }
             // qDebug()<<localDir+filename<< "dosya izinleri ayarlandı..";
            file.close();
    }
/***********************************************/
 }

QString MainWindow::myMessageBox(QString baslik, QString mesaj, QString evet, QString hayir, QString tamam, QMessageBox::Icon icon)
{
    Qt::WindowFlags flags = 0;
    flags |= Qt::Dialog;
   flags |= Qt::X11BypassWindowManagerHint;

    QMessageBox messageBox(this);
   //messageBox.setWindowFlags(flags);
    messageBox.setText(baslik+"\t\t\t");
    messageBox.setInformativeText(mesaj);
    messageBox.setWindowTitle("Betik Yükleyici");

    QAbstractButton *evetButton;
    QAbstractButton *hayirButton;
    QAbstractButton *tamamButton;

    if(evet=="evet") evetButton =messageBox.addButton(tr("Evet"), QMessageBox::ActionRole);
    if(hayir=="hayir") hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
    if(tamam=="tamam") tamamButton =messageBox.addButton(tr("Tamam"), QMessageBox::ActionRole);

    messageBox.setIcon(icon);
    messageBox.exec();
    if(messageBox.clickedButton()==evetButton) return "evet";
    if(messageBox.clickedButton()==hayirButton) return "hayir";
    if(messageBox.clickedButton()==tamamButton) return "tamam";
    return "";
}
