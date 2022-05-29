#include "mainwindow.h"
#include<QLabel>
#include<QLineEdit>
#include<QApplication>
#include<QScreen>
#include<QGridLayout>
#include<QToolButton>
#include<stdio.h>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mwidget=new QWidget(this);
    localDir="/usr/share/tinyinstaller/";

      QSize screenSize = qApp->screens()[0]->size();
    boy=screenSize.height()/153.6;
    en=boy*1.1;
    int e=en;
    int b=boy;
    this->setFixedSize(boy*75,en*120);
    int x = (screenSize.width() - this->width())/2;
    int y = (screenSize.height() - this->height()) / 2;
    this->move(x, y);

    progressbar = new QProgressBar(mwidget);
    progressbar->setFixedSize(boy*75,en*5);
    progressbar->setRange(0,1000);
    progressbar->setStyleSheet("background-color: #dfdfdf;");

    doc=new QTextEdit(mwidget);
    doc->setFixedSize(boy*75,en*40);
    doc->setStyleSheet("background-color: #dfdfdf;");
    doc->setReadOnly(true);
    mwidget->setFixedSize(boy*75,en*120);
  // this->setStyleSheet("background-color: #00df00;");
    auto appIcon = QIcon(":/icons/tinyinstaller.svg");
    this->setWindowIcon(appIcon);


    int font=boy*2;
    statusLabel=new QLabel(mwidget);
    statusLabel->setText("Yüklebilecek Paketler");
    statusLabel->setStyleSheet("color: #0000ac;font-size:"+QString::number(font)+"px");
    statusLabel->setFixedSize(boy*75,en*5);
    statusLabel->setAlignment(Qt::AlignCenter);



    auto layout = new QGridLayout;
    layout->setContentsMargins(0,0, 0,0);
    layout->setVerticalSpacing(0);
     layout->setHorizontalSpacing(0);
    //layout->setColumnMinimumWidth(0, 37);
  QWidget *paket = paketSlot(mwidget);
    paket->setFixedSize(en*75,en*70);
  //paket->setStyleSheet("background-color: #00dfdf;");

    layout->addWidget(statusLabel, 2,1,1,2,Qt::AlignCenter);
    layout->addWidget( paket,3,1,1,2,Qt::AlignCenter);
    layout->addWidget( doc,4,1,1,2,Qt::AlignCenter);
    layout->addWidget(progressbar,5,1,1,2,Qt::AlignCenter);

    mwidget->setLayout(layout);
    setCentralWidget(mwidget);
}

MainWindow::~MainWindow()
{

}

QWidget *MainWindow::paketSlot(QWidget *parent)
{
   // qDebug()<<"ayar click";
    QString font="12";
    QWidget * d = new QWidget(parent);
    d->setStyleSheet("background-color: #dfdfdf;");
   // d->setStyleSheet("font-size:"+QString::number(font.toInt()-2)+"px;");
    //auto appIcon = QIcon(":/icons/tinyinstaller.svg");
   // d->setWindowIcon(appIcon);
    //d->setWindowTitle("Paket Listesi");
   // d->setFixedSize(en*75,en*87);
/*
    QLineEdit * paketname = new QLineEdit(d);
    paketname->setFixedSize(en*20,boy*5);

    QLineEdit * address = new QLineEdit(d);
    address->setFixedSize(en*20,boy*5);
*/
   /* QLabel *nameLabel=new QLabel("Paket Adı");
    QLabel *addressLabel=new QLabel("Adres");

    QToolButton *paketEkleButton= new QToolButton;
    paketEkleButton->setFixedSize(QSize(en*25,boy*10));
    paketEkleButton->setIconSize(QSize(en*25,boy*7));
    paketEkleButton->setStyleSheet("Text-align:center");
    //paketEkleButton->setAutoRaise(true);
    paketEkleButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
     paketEkleButton->setText("Paket Bilgisi Ekle");

    connect(paketEkleButton, &QPushButton::clicked, [=]() {
        QStringList paketlist=fileToList("tinyinstallerlist");
         //QDate date = QDate::fromString(tarih->text(), "dd/MM/yyyy");
        //  int haftaSayisi=date.weekNumber();
       // qDebug()<<"hatfa :"<<haftaSayisi<<date.year()<<date.month()<<date.day();
            paketlist<<paketname->text()+"|"+address->text();

        listToFile(paketlist,"tinyinstallerlist");
        for(int i=0;i<paketlist.count();i++)
        {
            QString line=paketlist[i];
            QStringList lst=line.split("|");
            twl->setRowCount(i+1);
            twl->setItem(i, 0, new QTableWidgetItem(lst[0]));//package name
            //twl->setItem(i, 1, new QTableWidgetItem(lst[1]));//package address

        }

});

    /***********************************************************************/
   twl=new QTableWidget(d);
    twl->setFixedSize(QSize(en*71,en*55));
    twl->setColumnCount(1);
    //twl->setRowCount(0);
    twl->setColumnWidth(0, en*66);
   /// twl->setColumnWidth(1, en*44);

    twl->setHorizontalHeaderItem(0, new QTableWidgetItem("Paket Adı"));
   // twl->setHorizontalHeaderItem(1, new QTableWidgetItem("package address"));

    twl->setSelectionBehavior(QAbstractItemView::SelectRows);
    twl->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(tw, &QTableWidget::cellClicked, this, cellClicked());
    connect(twl, SIGNAL(cellDoubleClicked(int,int)),SLOT(paketTableCellDoubleClicked(int,int)));
    connect(twl, SIGNAL(cellClicked(int, int)),
            this, SLOT(paketTableWidgetWindow_cellClicked(int, int)));

    twl->setRowCount(0);
    system("wget  https://raw.githubusercontent.com/bayramkarahan/tinyinstaller/master/index.conf -O /usr/share/tinyinstaller/tinyinstallerlist");
    QStringList list=fileToList("tinyinstallerlist");
    for(int i=0;i<list.count();i++)
    {
        QString line=list[i];
        QStringList lst=line.split("|");
        twl->setRowCount(twl->rowCount()+1);
        twl->setItem(i, 0, new QTableWidgetItem(lst[0]));//package name
       // twl->setItem(i, 1, new QTableWidgetItem(lst[1]));//package address

    }
if(list.count()<1)
{
    statusLabel->setText("İnternet Bağlantısı bok veya Paket Listesi Yok");
    int font=boy*2;
    statusLabel->setStyleSheet("color: #ac0000;Text-align:center;font-size:"+QString::number(font)+"px");

}
 QToolButton *installerButton= new QToolButton(d);
 installerButton->setFixedSize(QSize(boy*35,boy*10));
 installerButton->setIconSize(QSize(boy*35,boy*5));
 installerButton->setStyleSheet("Text-align:center");
 installerButton->setIcon(QIcon(":/icons/tinyinstaller.svg"));
 installerButton->setAutoRaise(true);
 installerButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
 // powerOnButton->setFont(f2);
 installerButton->setText("Paketi Yükle");

 connect(installerButton, &QToolButton::clicked, [=]() {
   //  qDebug()<<"";
     if(selectPaketName!=""&&selectPaketAddress!="")
     {
         procesType=true;
         QString kmt="wget -O /tmp/script.sh "+selectPaketAddress;
         //qDebug()<<kmt;
         system(kmt.toStdString().c_str());
         system("sleep 1");
         system("chmod a+x /tmp/script.sh");
         /***********************************************************/

          proces=new QProcess(this);
          proces->setReadChannelMode(QProcess::MergedChannels);
          proces->setReadChannel(QProcess::StandardOutput);
          connect(proces, SIGNAL(readyReadStandardOutput()),this, SLOT(disp()));
          connect(proces, SIGNAL(started()), this, SLOT(procresbegin()));
          connect(proces, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(procresend()));
          proces->start("pkexec /tmp/script.sh");
     }else
     {
         statusLabel->setText("Paket Seçilmemiş");
         int font=boy*2;
         statusLabel->setStyleSheet("color: #ac0000;Text-align:center;font-size:"+QString::number(font)+"px");

     }

 });


 QToolButton *removeButton= new QToolButton(d);
 removeButton->setFixedSize(QSize(boy*35,boy*10));
 removeButton->setIconSize(QSize(boy*35,boy*5));
 removeButton->setStyleSheet("Text-align:center");
 removeButton->setIcon(QIcon(":/icons/remove.svg"));
 removeButton->setAutoRaise(true);
 removeButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
 // powerOnButton->setFont(f2);
 removeButton->setText("Paketi Kaldır");

 connect(removeButton, &QToolButton::clicked, [=]() {

     if(selectPaketName!=""&&selectPaketAddress!="")
     {
         procesType=false;
          proces=new QProcess(this);
          proces->setReadChannelMode(QProcess::MergedChannels);
          proces->setReadChannel(QProcess::StandardOutput);
          connect(proces, SIGNAL(readyReadStandardOutput()),this, SLOT(disp()));
          connect(proces, SIGNAL(started()), this, SLOT(procresbegin()));
          connect(proces, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(procresend()));
          QString kmt="pkexec apt remove "+selectPaketName +" -y";

          proces->start(kmt);
     }else
     {
         statusLabel->setText("Paket Seçilmemiş");
         int font=boy*2;
         statusLabel->setStyleSheet("color: #ac0000;Text-align:center;font-size:"+QString::number(font)+"px");
     }

 });
    auto dlayout = new QGridLayout(d);
   // dlayout->setContentsMargins(0,boy, 0,boy);
   // dayout->setVerticalSpacing(5);
    // dlayout->setHorizontalSpacing(5);
    //dlayout->setColumnMinimumWidth(0, 37);
    //dlayout->addWidget(nameLabel,1,1,1,1);
   // dlayout->addWidget(paketname,1,2,1,1);
   // dlayout->addWidget(addressLabel,2,1,1,1);
   // dlayout->addWidget(address,2,2,1,1);
  //  dlayout->addWidget(paketEkleButton, 1,3,2,2,Qt::AlignCenter);

     dlayout->addWidget(twl, 6,1,1,2,Qt::AlignCenter);

     dlayout->addWidget(installerButton, 7,1,1,2,Qt::AlignCenter);
     dlayout->addWidget(removeButton, 7,3,1,2,Qt::AlignCenter);

d->setLayout(dlayout);

return d;
   // int result = d->exec();
}
void MainWindow :: procresbegin()
{
    val=0;
    progressbar->setValue(val);
    doc->setText("");
    doc->moveCursor (QTextCursor::End);
    if(procesType) doc->textCursor().insertHtml("<p style=\"color:green;\">***Paket Yükleme Başladı***</p><br/>");
    else doc->textCursor().insertHtml("<p style=\"color:green;\">***Paket Kaldıra Başladı***</p>\n");
}
void MainWindow :: procresend()
{
    val=0;
    progressbar->setValue(1000);
    doc->moveCursor (QTextCursor::End);
    if(procesType)
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Yükleme Tamamlandı***</p>\n");
        system("rm /tmp/script.sh");
    }
    else  doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Kaldırma Tamamlandı***</p>\n");

}
void MainWindow :: disp()
{
    while( 1 ){
        val++;
        QString t = proces->readLine();
        if( t.isEmpty() ) {break;}
        doc->moveCursor (QTextCursor::End);
        if(!t.contains("error"))
            doc->textCursor().insertHtml("\n<p style=\"color:black;\">"+t+"</p>");
        else
        {
            doc->textCursor().insertHtml("\n<p style=\"color:red;\">"+t+"</p>");
            statusLabel->setText("Kurulumda hatalarla karşılaşıldı..");
            int font=boy*2;
            statusLabel->setStyleSheet("color: #ac0000;Text-align:center;font-size:"+QString::number(font)+"px");
        }
        progressbar->setValue(val);
    }
}
void MainWindow::paketTableWidgetWindow_cellClicked(int iRow, int iColumn)
{
    QString paketname= twl->item(iRow, 0)->text();
    QStringList list=fileToList("tinyinstallerlist");
    for(int i=0;i<list.count();i++)
    {
        QString line=list[i];
        QStringList lst=line.split("|");
        if(paketname==lst[0])
        {
           /// qDebug()<<"seçilen paket"<<lst[0]<<lst[1];
            selectPaketName=lst[0];
            selectPaketAddress=lst[1];

                     statusLabel->setText("Paket: "+selectPaketName);
                     int font=boy*2;
                     statusLabel->setStyleSheet("color: #0000ac;Text-align:center;font-size:"+QString::number(font)+"px");

        }
    }
}

void MainWindow::paketTableCellDoubleClicked(int iRow, int iColumn)
{
     QString paketname= twl->item(iRow, 0)->text();
     QStringList list=fileToList("tinyinstallerlist");
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
                 listToFile(list,"tinyinstallerlist");
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
            file.close();
    }
/***********************************************/
 }
