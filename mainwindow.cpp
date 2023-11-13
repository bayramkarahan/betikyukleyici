
#include "mainwindow.h"
#include<function.h>
#include<process.h>
#include<QLabel>
#include<QLineEdit>
#include<QApplication>
#include<QScreen>
#include<QGridLayout>
#include<QToolButton>
#include<stdio.h>
#include<QDebug>
#include<hakkinda.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    downloadAddress="https://github.com/bayramkarahan/betikyukleyici/raw/master/";
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
    font=boy*2;
    int fontt=font*1;
    int fonttt=font*0.7;

    auto appIcon = QIcon(":/icons/betikyukleyici.svg");
    this->setWindowIcon(appIcon);
    this->setWindowTitle("Betik Yükleyici");
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
    /*****************************************************************************************/
    QWidget *anaWidget= new QWidget(this);
    anaWidget->setFixedSize(pencereW,pencereH);
    anaWidget->setObjectName("anaWidget");
    anaWidget->setStyleSheet("QWidget#anaWidget{background-color: #ffffff;}");
    auto layout = new QGridLayout(anaWidget);
    layout->setContentsMargins(0,0, 0,0);
    layout->setSpacing(0);
    appsWidget=new QWidget(anaWidget);
    localDir="/usr/share/betikyukleyici/";


    system("rm -rf /tmp/installscript.sh");
    system("rm -rf /tmp/removescript.sh");
     /**********************Arama Widget*************************************************/
    /**********************Arama Widget*************************************************/
   aramaWidget=new QWidget(anaWidget);
   aramaWidget->setObjectName("aramaWidget");
   aramaWidget->setStyleSheet("QWidget#aramaWidget{/*background-color: #44ff22;*/border-bottom:1px solid #dcdcdc;}");
   aramaWidget->setFixedSize(pencereNW,pencereNH*0.05);

  statusLabel=new QLabel(aramaWidget);
  statusLabel->setObjectName("statusLabel");
  statusLabel->setStyleSheet("QLabel#statusLabel{color: #aa0000;font-size:"+QString::number(font)+"px;}");
  // statusLabel->setStyleSheet("background-color: #0000ac;");
  statusLabel->setFixedSize(aramaWidget->width()*0.55,aramaWidget->height()*0.9);


    findTextEditLabel=new QLabel(aramaWidget);
    findTextEditLabel->setText("Paket Ara");
    //findTextEditLabel->setStyleSheet("background-color: #0000ac;");
    findTextEditLabel->setStyleSheet("color: #000000;font-size:"+QString::number(font)+"px");
    findTextEditLabel->setFixedSize(aramaWidget->width()*0.05,aramaWidget->height()*0.9);
  //  findTextEditLabel->setAlignment(Qt::AlignLeft);

    findTextEdit=new QTextEdit(aramaWidget);
    findTextEdit->setFixedSize(aramaWidget->width()*0.10,aramaWidget->height()*0.80);

    findTextEdit->setStyleSheet("color: #000000;font-size:"+QString::number(font)+"px");

 //connect(findTextEdit, SIGNAL(textChanged()), this, SLOT(findTextEditChanged()));
    connect(findTextEdit, SIGNAL(textChanged()), this, SLOT(appWidgetfindTextEditChanged()));

 updateButton= new QToolButton(aramaWidget);
 updateButton->setFixedSize(aramaWidget->width()*0.14,aramaWidget->height()*0.9);
 updateButton->setIconSize(QSize(aramaWidget->width()*0.10,aramaWidget->height()*0.9));
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

 aboutButton= new QToolButton(aramaWidget);
 aboutButton->setFixedSize(aramaWidget->width()*0.1,aramaWidget->height()*0.9);
 aboutButton->setIconSize(QSize(aramaWidget->width()*0.15,aramaWidget->height()*0.9));
 aboutButton->setStyleSheet("Text-align:center;color: #000000;font-size:"+QString::number(font)+"px");
 aboutButton->setIcon(QIcon(":/icons/about.svg"));
 aboutButton->setAutoRaise(true);
 aboutButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
 // powerOnButton->setFont(f2);
 aboutButton->setText("Hakkında");

     connect(aboutButton, &QToolButton::clicked, [=]() {
         about();
     //if(appsWidget!=nullptr)
      //     appsWidget->setEnabled(false);

     });
 QGridLayout *aramalayout = new QGridLayout(aramaWidget);
//aramalayout->setSpacing(0);
aramalayout->setContentsMargins(0,0,0,0);
  aramalayout->addWidget(statusLabel,1,0,1,1,Qt::AlignLeft);
 aramalayout->addWidget(findTextEditLabel,1,1,1,1,Qt::AlignRight);
 aramalayout->addWidget(findTextEdit,1,2,1,1,Qt::AlignLeft);
 aramalayout->addWidget(updateButton,1,4,1,1,Qt::AlignRight);
 aramalayout->addWidget(aboutButton,1,5,1,1,Qt::AlignRight);

    /**********************scriptWidget Widget*************************************************/
    /**********************scriptWidget Widget*************************************************/
    scriptWidget=new QWidget(anaWidget);
    scriptWidget->setStyleSheet("background-color: #ffffff;");
    scriptWidget->setFixedSize(pencereNW,pencereNH*0.25);
    QTabWidget *tabw=new QTabWidget(scriptWidget);
    tabw->setFixedSize(pencereNW,pencereNH*0.5);
   // tabw->setStyleSheet("font-size:"+QString::number(font)+"px");

   // qDebug()<<"font:"<<font<<fontt<<fonttt;
    QString tabstyle="QTabWidget::pane {border: 1px solid lightgray;top:-1px; background:#efefef;}\
        QTabBar::tab {background:#eeeeee; border: 1px solid lightgray;font-size:"+QString::number(font)+"px; padding: 5px;} \
        QTabBar::tab:selected { background:#ffffff; margin-bottom: -1px; }";
    tabw->setStyleSheet(tabstyle);
    doc=new QTextEdit(tabw);
    doc->setFixedSize(pencereNW*0.995,pencereNH*0.2);
    doc->setReadOnly(true);
    doc->setStyleSheet(" border:0px solid black;");

    installscriptTextEdit=new QTextEdit(tabw);
    installscriptTextEdit->setFixedSize(pencereNW,pencereNH*0.2);
    installscriptTextEdit->setReadOnly(true);
    installscriptTextEdit->setStyleSheet(" border:0px solid black;");

    removescriptTextEdit=new QTextEdit(tabw);
    removescriptTextEdit->setFixedSize(pencereNW,pencereNH*0.2);
    removescriptTextEdit->setReadOnly(true);
    removescriptTextEdit->setStyleSheet(" border:0px solid black;");

  //  doc->setStyleSheet("background-color: #dfdfdf;");
    tabw->addTab(installscriptTextEdit,"Yükleme Betiği");
    tabw->addTab(removescriptTextEdit,"Kaldırma Betiği");

    tabw->addTab(doc,"Süreç");
   // tabw->setTabPosition(QTabWidget::West);
  //  mwidget->setFixedSize(en*120,boy*125);

    /**********************progressbar Widget*************************************************/
    /**********************progressbar Widget*************************************************/
    progressbar = new QProgressBar(anaWidget);
    progressbar->setFixedSize(pencereNW,pencereNH*0.04);
    progressbar->setRange(0,100);
    progressbar->setStyleSheet("border-radius: 0px;");
   progressbar->setStyleSheet("QProgressBar {"
                          "background-color: #ffffff;"
                          "color: #000000;"
                          "border-style: outset;"
                          "border-width: 2px;"
                          "border-color: #ffffff;"
                          "border-radius: 7px;"
                          "text-align: center; }"

                          "QProgressBar::chunk {"
                          "background-color: #5454ff; }");

    //QString danger = "QProgressBar::chunk: horizontal {border-radius: 3px; background: QLinearGradient(X1:0, y1:0.966136, x2:0, y2:0, stop:0.609721 rgba(242, 53, 53, 255), stop:0.691923 rgba(240, 151, 141, 252));border: .px solid black;}";

    //progressbar->setStyleSheet(danger);
    /**************************************************************/

    /**********************Kategori Widget*************************************************/
    /**********************Kategori Widget*************************************************/
    getIndex();//index bilgileri iniyor.
    kategoriWidget=new QWidget(anaWidget);
    kategoriWidget->setObjectName("kategoriWidget");
    kategoriWidget->setStyleSheet("QWidget#kategoriWidget{/*background-color: #00ffaa;*/border-bottom:1px solid #dcdcdc;}");
    kategoriWidget->setFixedSize(pencereNW,pencereNH*0.10);
    kategoriListele();
    /**********************appsWidget Widget*************************************************/
    /**********************appsWidget Widget*************************************************/

   // appsWidget=new QWidget(anaWidget);
    appsWidget->setObjectName("appsWidget");
    // appsWidget->setStyleSheet("QWidget#appsWidget{background-color: #ff0000;border-bottom:1px solid #dc0000;}");
    appsWidget->setFixedSize(pencereNW,pencereNH*0.55);

        if (appsListButton.count()==0)
        {
            localDir="/tmp/";
            QStringList list=fileToList("/betikyukleyiciscript/betikyukleyiciappsindex.conf");
            uygulamaListeHazirla(list);
        }
        //qDebug()<<"apps list"<<appsListButton.count();
       appsWidgetListe=new QWidget(appsWidget);
        appsWidgetListe->setObjectName("appsListewidget");
      // appsWidgetListe->setStyleSheet("background-color: #000077");
        //appsWidgetListe->setAutoFillBackground(false);
        /**************************************************/
        appslayout = new QGridLayout();
        appslayout->setContentsMargins(0, 0, 0,0);
        appslayout->setSpacing(0);
        appsWidgetListe->setLayout(appslayout);

        uygulamaListele();
        QScrollArea *appsWidgetscrollArea=new QScrollArea(appsWidget);
        appsWidgetscrollArea->setFixedSize(appsWidget->width(),appsWidget->height());
        appsWidgetscrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        appsWidgetscrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        appsWidgetscrollArea->setStyleSheet("background-color: #ffffff;border:0;border-bottom:1px solid #dcdcdc;");
        appsWidgetscrollArea->setWidget(appsWidgetListe);

        /*****************************************************************/
        /*****************************************************************/


        layout->addWidget(aramaWidget,1,1,1,1,Qt::AlignCenter);
        layout->addWidget(kategoriWidget,2,1,1,1,Qt::AlignCenter);
        layout->addWidget(appsWidget,4,1,1,1,Qt::AlignCenter);

        layout->addWidget(scriptWidget,5,1,1,1,Qt::AlignCenter);
        layout->addWidget(progressbar,6,1,1,1,Qt::AlignCenter);


  /****************versiyon kontrolü yapılıyor***********************************************/
  system("rm -rf /tmp/version");
  procesType="getversion";
  QString kmt="wget https://github.com/bayramkarahan/betikyukleyici/raw/master/debian/files -O /tmp/version";
  proces->start(kmt);
  proces->waitForFinished(-1);


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

 // runEndPackageSlot("javamimetype");


}
MainWindow::~MainWindow()
{

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

