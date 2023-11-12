/*****************************************************************************
 *   Copyright (C) 2020 by Bayram KARAHAN                                    *
 *   <bayramk@gmail.com>                                                     *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/
#include<QCheckBox>
#include<QProcess>
#include<QPalette>
#include<QPushButton>

#ifndef HAKKINDA_H
#define HAKKINDA_H
QWidget *MainWindow::hakkinda()
{

    QWidget *hakkindaPage=new QWidget();
    /*******************************************************/
    hakkindaPage->setFixedWidth(boy*100);
    hakkindaPage->setFixedHeight(boy*100);
    auto *icon=new QLabel(hakkindaPage);
    icon->setPixmap( QPixmap( ":/icons/betikyukleyici.svg" ) );
    icon->setScaledContents( true );
    icon->setFixedSize(hakkindaPage->width()*0.1,hakkindaPage->height()*0.1);
   auto *hak=new QLabel(hakkindaPage);

    hak->setText("\n* Bu uygulama istediğimiz görevi yükleyen ve kaldıran betikleri çalıştırmak için yazılmıştır."
                 "\n\n* Betiklerin çalıştırılmasından doğacak verikaybı veya sorunlarını kullanıcı kabul etmiş sayılır."
                "\n\n* Yazılımı kullanarak Yükleme ve Kaldırma betiklerini çalıştırmadan önce kontrol ediniz."
                "\n\n* Bu betik yükleme listesinde bulunmayan yazılımları talep edebilirsiniz."
                "\n\n* Listede bulunan betiklerde hata varsa iletişime geçebilirsiniz."
                 "\n"
                   "\n   Copyright (C) 2023 by Bayram KARAHAN                                     "
                  "\n   github.com/bayramkarahan/betikyukleyici                                         "
                  "\n"
                  "\n   This program is free software; you can redistribute it and/or modify    "
                  "\n   it under the terms of the GNU General Public License as published by    "
                  "\n   the Free Software Foundation; either version 3 of the License, or       "
                  "\n   (at your option) any later version.                                     "
                  "\n                                                                           "
                  "\n   This program is distributed in the hope that it will be useful,         "
                  "\n   but WITHOUT ANY WARRANTY; without even the implied warranty of          "
                  "\n   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           "
                  "\n   GNU General Public License for more details.                            "
                  "\n                                                                           "
                  "\n   You should have received a copy of the GNU General Public License       "
                  "\n   along with this program; if not, write to the                          "
                  "\n   Free Software Foundation, Inc.,                                         "
                  "\n   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          "

                 "\n\n\n"
                 "İstek ve önerileriniz için;"
                 "\nE-Posta: bayramk@gmail.com"
                 "\nbayramkarahan.blogspot.com"
                 "\n");
    QFont ff( "Arial", 8, QFont::Normal);
    hak->setFont(ff);

    auto layout = new QGridLayout(hakkindaPage);
    layout->setContentsMargins(0, 0, 0,0);
    layout->addWidget( icon,10,0,1,1,Qt::AlignHCenter);

    layout->addWidget( hak,20,0,1,1,Qt::AlignHCenter);

   // layout->setColumnStretch(6, 255);
    //hakkindaPage->resize(500,300);

   // hakkindaPage->setStyleSheet("background-color: #acacac");

    return hakkindaPage;
}
#endif // HAKKINDA_H
