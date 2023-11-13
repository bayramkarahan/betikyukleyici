#ifndef PROCESS_H
#define PROCESS_H
#include<mainwindow.h>
void MainWindow :: procresbegin()
{
    if(appsWidget!=nullptr)
       appsWidget->setEnabled(false);

      val=0;
    progressbar->setValue(val);
    doc->setText("");
    doc->moveCursor (QTextCursor::End);

    if(procesType=="install")
    {
        // qDebug()<<"kurulum başladı.";
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Yükleme Başladı***</p>");
    }
    if(procesType=="remove")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Kaldırma Başladı***</p>");
        }

    if(procesType=="getindex")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Listesi İndirme Başladı***</p>");
    }

      if(procesType=="getindexscript")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Verileri İndirme Başladı***</p>");
    }

}
void MainWindow :: procresend()
{
    // qDebug()<<"procresend";
    val=100;
    int procesTypeStatus=0;

    progressbar->setValue(val);
    if(appsWidget!=nullptr)
      appsWidget->setEnabled(true);

    doc->moveCursor (QTextCursor::End);
    if(procesType=="install")
    {
        qDebug()<<"kurulum bitti.";
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Yükleme Tamamlandı***</p>");
       /// system("rm /tmp/installscript.sh");
           myMessageBox("", "\n\Yükleme Betiğinin Çalışması Tamamlandı..\n","","","tamam",QMessageBox::Information);
        procesTypeStatus=1;
    //runEndPackageSlot(selectPaketName);
    }
    if(procesType=="remove")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Kaldırma Tamamlandı***</p>");
   // system("rm /tmp/removescript.sh");
    myMessageBox("", "\n\Kaldırma Betiğinin Çalışması Tamamlandı..\n","","","tamam",QMessageBox::Information);
   // runEndPackageSlot(selectPaketName);
        procesTypeStatus=2;
      }
    if(procesType=="getindexscript")
    {
         doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Verileri İndirme Tamamlandı***</p>");
         procesTypeStatus=5;
         /* localDir="/usr/share/betikyukleyici/";
        QStringList list=fileToList("betikyukleyicilist");
        listToFile(list,"betikyukleyicilist");*/
         system("unzip -q -x -o /tmp/betikyukleyiciscript.zip -d /tmp/");
         // qDebug()<<"icon indirme tamamlandı";
         progressbar->setValue(0);
    }

    if(procesType=="getversion")
    {
        QStringList arguments;
        arguments << "-c" << "dpkg -s betikyukleyici|grep -i version";
        QString resultVersion;
        QProcess process;
        process.start("/bin/bash",arguments);
        if(process.waitForFinished())
        {
            resultVersion = process.readAll();
        }
        resultVersion.chop(1);
        version = resultVersion.right(5);

        //qDebug()<<"version kontrol yapılıyor"<<sonuc;
        localDir="/tmp/";
        QStringList listv=fileToList("version");
        for(int i=0;i<listv.count();i++)
        {
            QString line=listv[i];
          //  qDebug()<<line;
            if(line!="")
            {
                //qDebug()<<"**"<<line;
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
         progressbar->setValue(0);
    }

 doc->moveCursor(QTextCursor::End);
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

        //doc->moveCursor(QTextCursor::End);

        }
        else
        {
            doc->textCursor().insertHtml("<br/><lu style=\"color:red;\">"+t+"</lu>");
            statusLabel->setText("Kurulumda hatalarla karşılaşıldı..");
            int font=boy*2;
          //  statusLabel->setStyleSheet("color: #ac0000;Text-align:center;font-size:"+QString::number(font)+"px");
        }
        if(val>99) val=0;

        progressbar->setValue(val);
         doc->moveCursor(QTextCursor::End);
    }
}


#endif // PROCESS_H
