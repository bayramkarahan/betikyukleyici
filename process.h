#ifndef PROCESS_H
#define PROCESS_H

void MainWindow :: procresbegin()
{

   /* installerButton->setEnabled(false);
    removeButton->setEnabled(false);
    twl->setEnabled(false);
*/
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
    if(procesType=="getscriptinstall")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Script İndirme Başladı***</p>");

       }
    if(procesType=="getscriptremove")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Script İndirme Başladı***</p>");

       }
    //qDebug()<<"procresbegin.";

    if(procesType=="getindex")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Listesi İndirme Başladı***</p>");
    }

    if(procesType=="getindexicons")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Listesi İconları İndirme Başladı***</p>");
    }


}
void MainWindow :: procresend()
{
    // qDebug()<<"procresend";
    val=100;
    int procesTypeStatus=0;

    progressbar->setValue(val);
    doc->moveCursor (QTextCursor::End);
    if(procesType=="install")
    {
        qDebug()<<"kurulum bitti.";
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Yükleme Tamamlandı***</p>");
       /// system("rm /tmp/installscript.sh");
           myMessageBox("", "\n\Yükleme Betiğinin Çalışması Tamamlandı..\n","","","tamam",QMessageBox::Information);
        procesTypeStatus=1;

    }
    if(procesType=="remove")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Kaldırma Tamamlandı***</p>");
   // system("rm /tmp/removescript.sh");
    myMessageBox("", "\n\Kaldırma Betiğinin Çalışması Tamamlandı..\n","","","tamam",QMessageBox::Information);

        procesTypeStatus=2;
      }
    if(procesType=="getscriptinstall")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Script İndirme Tamamlandı***</p>");
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
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Script İndirme Tamamlandı***</p>");
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
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Listesi İndirme Tamamlandı***</p>");
        procesTypeStatus=4;
      /*  localDir="/usr/share/betikyukleyici/";
        QStringList list=fileToList("betikyukleyicilist");
        listToFile(list,"betikyukleyicilist");*/
        progressbar->setValue(0);
    }

    if(procesType=="getindexicons")
    {
        doc->textCursor().insertHtml("<br/><p style=\"color:green;\">***Paket Listesi İconları İndirme Tamamlandı***</p>");
        procesTypeStatus=5;
       /* localDir="/usr/share/betikyukleyici/";
        QStringList list=fileToList("betikyukleyicilist");
        listToFile(list,"betikyukleyicilist");*/
        system("unzip -q -x -o /tmp/betikyukleyiciappsicons.zip -d /tmp/");
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
