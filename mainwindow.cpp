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
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mwidget=new QWidget(this);
    localDir="/usr/share/betikyukleyici/";
    version="betikyukleyici_1.3.0_amd64.deb";
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

      QSize screenSize = qApp->screens()[0]->size();
     // qDebug()<<"boyut"<<screenSize.height()*0.65<<screenSize.width()*0.5;
    boy=screenSize.height()/153;
    en=boy*1.1;
  //   qDebug()<<"en"<<en;
    int e=en;
    int b=boy;
    this->setFixedSize(en*120,boy*125);
    int x = (screenSize.width() - this->width())/2;
    int y = (screenSize.height() - this->height()) / 2;
    this->move(x, y);
    progressbar = new QProgressBar(mwidget);
    progressbar->setFixedSize(en*120,boy*5);
    progressbar->setRange(0,100);
  //  progressbar->setStyleSheet("background-color: #dfdfdf;");
    QTabWidget *tabw=new QTabWidget(mwidget);
    tabw->setFixedSize(en*120,boy*40);


    doc=new QTextEdit(tabw);
    doc->setFixedSize(en*120,boy*35);
    doc->setReadOnly(true);

    installscriptTextEdit=new QTextEdit(tabw);
    installscriptTextEdit->setFixedSize(en*120,boy*35);
    installscriptTextEdit->setReadOnly(true);

    removescriptTextEdit=new QTextEdit(tabw);
    removescriptTextEdit->setFixedSize(en*120,boy*35);
    removescriptTextEdit->setReadOnly(true);

  //  doc->setStyleSheet("background-color: #dfdfdf;");
    tabw->addTab(installscriptTextEdit,"Y??kleme Beti??i");
    tabw->addTab(removescriptTextEdit,"Kald??rma Beti??i");

    tabw->addTab(doc,"S??re??");
   // tabw->setTabPosition(QTabWidget::West);
    mwidget->setFixedSize(en*120,boy*125);
  // this->setStyleSheet("background-color: #00df00;");
    auto appIcon = QIcon(":/icons/betikyukleyici.svg");
    this->setWindowIcon(appIcon);
  this->setWindowTitle("Betik Y??kleyici");

    int font=boy*2;
    statusLabel=new QLabel(mwidget);
    statusLabel->setText("Y??klebilecek Paketler");
    //statusLabel->setStyleSheet("color: #0000ac;font-size:"+QString::number(font)+"px");
    statusLabel->setFixedSize(en*120,boy*5);
    statusLabel->setAlignment(Qt::AlignCenter);


    findTextEditLabel=new QLabel(mwidget);
    findTextEditLabel->setText("Paket Ara");
    ///findTextEditLabel->setStyleSheet("background-color: #0000ac;");
    findTextEditLabel->setFixedSize(en*15,boy*5.5);
  //  findTextEditLabel->setAlignment(Qt::AlignLeft);

    findTextEdit=new QTextEdit(mwidget);
    findTextEdit->setFixedSize(en*30,boy*6);
 connect(findTextEdit, SIGNAL(textChanged()), this, SLOT(findTextEditChanged()));

    QHBoxLayout *aramalayout = new QHBoxLayout;
    aramalayout->addWidget(findTextEditLabel);
    aramalayout->addWidget(findTextEdit);



 updateButton= new QToolButton(mwidget);
 updateButton->setFixedSize(QSize(en*30,boy*9));
 updateButton->setIconSize(QSize(en*30,boy*3));
 updateButton->setStyleSheet("Text-align:center");
 updateButton->setIcon(QIcon(":/icons/update.svg"));
 updateButton->setAutoRaise(true);
 updateButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
 // powerOnButton->setFont(f2);
 updateButton->setText("Program?? G??ncelle");

 connect(updateButton, &QToolButton::clicked, [=]() {
     if (updateFile=="") return;
     QString kmt="wget -O /tmp/prg.deb https://github.com/bayramkarahan/betikyukleyici/raw/master/"+updateFile;
     system(kmt.toStdString().c_str());
      system("sleep 1");
     system("chmod 777 /tmp/prg.deb");
      system("sleep 1");
     system("pkexec dpkg -i --force-all /tmp/prg.deb");
      //system("sleep 2");
     //system("rm  /tmp/prg.deb");
 });

    auto layout = new QGridLayout;
    layout->setContentsMargins(0,0, 0,0);
   // layout->setVerticalSpacing(0);
   //  layout->setHorizontalSpacing(10);
    //layout->setColumnMinimumWidth(0, 37);
  QWidget *paket = paketSlot(mwidget);
    paket->setFixedSize(en*120,boy*65);
  //paket->setStyleSheet("background-color: #00dfdf;");
    layout->addWidget(statusLabel, 1,1,1,2,Qt::AlignCenter);

     layout->addWidget(updateButton, 1,2,1,1,Qt::AlignRight);

     layout->addLayout(aramalayout, 2,2,1,1,Qt::AlignLeft);

    layout->addWidget( paket,3,1,1,2,Qt::AlignCenter);
    layout->addWidget( tabw,4,1,1,2,Qt::AlignCenter);
    layout->addWidget(progressbar,5,1,1,2,Qt::AlignCenter);

    mwidget->setLayout(layout);
    setCentralWidget(mwidget);


    /****************versiyon kontrol?? yap??l??yor***********************************************/
    //system("wget https://github.com/bayramkarahan/betikyukleyici/raw/master/debian/files -O /tmp/version");
   procesType="getversion";
   QString kmt="wget https://github.com/bayramkarahan/betikyukleyici/raw/master/debian/files -O /tmp/version";
  proces->start(kmt);
  proces->waitForFinished(-1);
  /****************index listesi ??ekiliyor***********************************************/
  // system("wget  https://raw.githubusercontent.com/bayramkarahan/betikyukleyici/master/index.conf -O /usr/share/betikyukleyici/betikyukleyicilist");
  procesType="getindex";
  proces->start("wget  https://raw.githubusercontent.com/bayramkarahan/betikyukleyici/master/script/index.conf -O /usr/share/betikyukleyici/betikyukleyicilist");
  proces->waitForFinished(-1);

     /***************************************************************/
  paketTableWidgetWindow_cellClicked(0, 0);
}
void   MainWindow::findTextEditChanged()
{
//  qDebug()<<"tu??a bas??ld??..";
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
        twl->setItem(i, 2, new QTableWidgetItem("Y??kl??"));//package address
    else
        twl->setItem(i, 2, new QTableWidgetItem("-----"));//package address
}
//twl->selectRow(0);

    // paketTableWidgetWindow_cellClicked(0,0);
}
void   MainWindow::about(){
    QSize screenSize = qApp->screens()[0]->size();
   // qDebug()<<screenSize.width()/65<<screenSize.height()/35;

    QWidget *hk=hakkinda();

    hk->show();
    hk->move(screenSize.width()/2-hk->width()/2,screenSize.height()/2-hk->height()/2);
     hk->setWindowTitle("Betik Y??kleyici");
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

    twl->setHorizontalHeaderItem(0, new QTableWidgetItem("Paket Ad??"));
    twl->setHorizontalHeaderItem(1, new QTableWidgetItem("A????klama"));

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
 installerButton->setText("Betik Y??kle");

 connect(installerButton, &QToolButton::clicked, [=]() {

     if(selectPaketName!=""&&selectPaketAddressInstall!="")
     {
         if(!QFile::exists("/tmp/installscript.sh"))
         {
             paketTableWidgetWindow_cellClicked(selectRowIndex, 0);
         }
         procesType="install";

         proces->start("pkexec bash -c \"chmod a+x /tmp/installscript.sh&&/tmp/installscript.sh\"");

     }else
     {
         statusLabel->setText("Paket Se??ilmemi??");
         int font=boy*2;
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
 removeButton->setText("Betik Kald??r");

 connect(removeButton, &QToolButton::clicked, [=]() {

     if(selectPaketName!=""&&selectPaketAddressInstall!="")
     {
         if(!QFile::exists("/tmp/removescript.sh"))
         {
             paketTableWidgetWindow_cellClicked(selectRowIndex, 0);
         }
         procesType="remove";
         proces->start("pkexec bash -c \"chmod a+x /tmp/removescript.sh&&/tmp/removescript.sh\"");

     }else
     {
         statusLabel->setText("Paket Se??ilmemi??");
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
 aboutButton->setText("Hakk??nda");

 connect(aboutButton, &QToolButton::clicked, [=]() {
about();
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
void MainWindow :: procresbegin()
{
    installerButton->setEnabled(false);
    removeButton->setEnabled(false);
      val=0;
    progressbar->setValue(val);
    doc->setText("");
    doc->moveCursor (QTextCursor::End);

    if(procesType=="install")
    {
        doc->textCursor().insertHtml("<p style=\"color:green;\">***Paket Y??kleme Ba??lad??***</p>");
              }
    if(procesType=="remove")
    {
        doc->textCursor().insertHtml("<p style=\"color:green;\">***Paket Kald??ra Ba??lad??***</p>");
        }
    if(procesType=="getscriptinstall")
    {
        doc->textCursor().insertHtml("><p style=\"color:green;\">***Script ??ndirme Ba??lad??***</p>");

       }
    if(procesType=="getscriptremove")
    {
        doc->textCursor().insertHtml("><p style=\"color:green;\">***Script ??ndirme Ba??lad??***</p>");

       }
    if(procesType=="getindex")
    {
        doc->textCursor().insertHtml("<p style=\"color:green;\">***Paket Listesi ??ndirme Ba??lad??***</p>");
       }

}
void MainWindow :: procresend()
{
    val=100;
    int procesTypeStatus=0;

    progressbar->setValue(val);
    doc->moveCursor (QTextCursor::End);
    if(procesType=="install")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Y??kleme Tamamland??***</p>");
        system("rm /tmp/installscript.sh");
           myMessageBox("", "\n\Y??kleme Beti??inin ??al????mas?? Tamamland??..\n","","","tamam",QMessageBox::Information);
        procesTypeStatus=1;
    }
    if(procesType=="remove")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Kald??rma Tamamland??***</p>");
    system("rm /tmp/removescript.sh");
    myMessageBox("", "\n\Kald??rma Beti??inin ??al????mas?? Tamamland??..\n","","","tamam",QMessageBox::Information);

        procesTypeStatus=2;
    }
    if(procesType=="getscriptinstall")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Script ??ndirme Tamamland??***</p>");
        procesTypeStatus=3;
        localDir="/tmp/";
        QStringList list1=fileToList("installscript.sh");
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

    }
    if(procesType=="getscriptremove")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Script ??ndirme Tamamland??***</p>");
        procesTypeStatus=3;
        localDir="/tmp/";
        QStringList list1=fileToList("removescript.sh");
        removescriptTextEdit->clear();
        int font=boy*2;
        for(int i=0;i<list1.count();i++)
        {
            QString line=list1[i];
            if(line!="")
            {
                // script->insertPlainText(line+"\n");
                removescriptTextEdit->textCursor().insertHtml("<br/><lu style=\"color:black;font-size:"+QString::number(font)+"px;\">"+line+"</lu>");

            }
        }

    }
    if(procesType=="getindex")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Listesi ??ndirme Tamamland??***</p>");
        procesTypeStatus=4;
    }
    if(procesType=="getversion")
    {
        localDir="/tmp/";
        QStringList listv=fileToList("version");
        for(int i=0;i<listv.count();i++)
        {
            QString line=listv[i];
            if(line!="")
            {
                ///qDebug()<<"**"<<line;
                if(line.contains(version,Qt::CaseInsensitive))
                {
                    updateButton->hide();

                }else
                {
                    updateButton->show();
                    line.truncate(line.lastIndexOf("deb")+3);
                    // qDebug()<<line;
                    updateFile=line;
                }

            }
        }
    }
        localDir="/usr/share/betikyukleyici/";
   /***********************************************************************/
            QStringList list=fileToList("betikyukleyicilist");
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
                twl->setItem(i, 2, new QTableWidgetItem("Y??kl??"));//package address
            else
                twl->setItem(i, 2, new QTableWidgetItem("-----"));//package address
        }
        twl->selectRow(selectRowIndex);

        if(list.count()<1)
        {
            statusLabel->setText("??nternet Ba??lant??s?? Yok veya Paket Listesi Yok");
            int font=boy*2;
            statusLabel->setStyleSheet("color: #ac0000;Text-align:center;font-size:"+QString::number(font)+"px");
        }

    /**************************************************************/
        installerButton->setEnabled(true);
        removeButton->setEnabled(true);

}
void MainWindow :: disp()
{
    int font=boy*2;
    while( 1 ){
        val++;
        QString t = proces->readLine();

        t.remove("\n");
      // qDebug()<<t.toUtf8();

        if( t.isEmpty()||t=="" ) {break;}
       // t=t+"\n\n";
      //  doc->moveCursor (QTextCursor::End);
        if(!t.contains("error",Qt::CaseInsensitive)&&!t.contains("hata",Qt::CaseInsensitive))
        {

           doc->textCursor().insertHtml("<br/><lu style=\"color:black;font-size:"+QString::number(font)+"px;\">"+t+"</lu>");
          //  doc->insertPlainText(t);

        }
        else
        {
            doc->textCursor().insertHtml("<br/><lu style=\"color:red;\">"+t+"</lu>");
            statusLabel->setText("Kurulumda hatalarla kar????la????ld??..");
            int font=boy*2;
          //  statusLabel->setStyleSheet("color: #ac0000;Text-align:center;font-size:"+QString::number(font)+"px");
        }
        if(val>99) val=0;

        progressbar->setValue(val);
    }
}
void MainWindow::paketTableWidgetWindow_cellClicked(int iRow, int iColumn)
{
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
           /// qDebug()<<"se??ilen paket"<<lst[0]<<lst[1];
            selectPaketName=lst[0];
           if(lst.count()>1) selectPaketAddressInstall=lst[1];
          // qDebug()<<lst.count();
           if(lst.count()>2) selectPaketAddressRemove=lst[2];

                     statusLabel->setText("Paket: "+selectPaketName);
                   //  int font=boy*2;
                  //   statusLabel->setStyleSheet("color: #0000ac;Text-align:center;font-size:"+QString::number(font)+"px");

                     selectRowIndex=iRow;
        }
    }

///qDebug()<<"paket ad??: "<<selectPaketAddressInstall;
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
    // reply = QMessageBox::question(this, "Uyar??", "Bilgisayar Silinecek! Emin misiniz?",
      //                             QMessageBox::Yes|tr(QMessageBox::No);
     QMessageBox messageBox(this);
     messageBox.setText("Uyar??");
     messageBox.setInformativeText("Paket Listesi ????lem Se??iniz!");
     QAbstractButton *evetButton =messageBox.addButton(tr("Sil"), QMessageBox::ActionRole);
     QAbstractButton *hayirButton =messageBox.addButton(tr("D??zenle"), QMessageBox::ActionRole);
     messageBox.setIcon(QMessageBox::Question);
             messageBox.exec();
             if (messageBox.clickedButton() == evetButton) {
                 // qDebug()<<"evet bas??ld??";
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
                 //qDebug()<<"hay??r bas??ld??";
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

QString MainWindow::myMessageBox(QString baslik, QString mesaj, QString evet, QString hayir, QString tamam, QMessageBox::Icon icon)
{
    Qt::WindowFlags flags = 0;
    flags |= Qt::Dialog;
   flags |= Qt::X11BypassWindowManagerHint;

    QMessageBox messageBox(this);
   //messageBox.setWindowFlags(flags);
    messageBox.setText(baslik+"\t\t\t");
    messageBox.setInformativeText(mesaj);
    messageBox.setWindowTitle("Betik Y??kleyici");

    QAbstractButton *evetButton;
    QAbstractButton *hayirButton;
    QAbstractButton *tamamButton;

    if(evet=="evet") evetButton =messageBox.addButton(tr("Evet"), QMessageBox::ActionRole);
    if(hayir=="hayir") hayirButton =messageBox.addButton(tr("Hay??r"), QMessageBox::ActionRole);
    if(tamam=="tamam") tamamButton =messageBox.addButton(tr("Tamam"), QMessageBox::ActionRole);

    messageBox.setIcon(icon);
    messageBox.exec();
    if(messageBox.clickedButton()==evetButton) return "evet";
    if(messageBox.clickedButton()==hayirButton) return "hayir";
    if(messageBox.clickedButton()==tamamButton) return "tamam";
    return "";
}
