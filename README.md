# tint-yinstaller
Linuxta açık olan yetkili yetkisiz kullanıcının gui olarak paket yüklemesi için yazılmıştır.. 
<br/>
![tinyinstaller](https://github.com/bayramkarahan/tinyinstaller/blob/master/tinyinstaller0.png)<br/>
# install
gcc -o installeryetki --static yetki.c<br/>
qmake tinyinstaller<br/>
make<br/>
sudo make install<br/>
# Kullanım Amacı
index.conf dosyasındaki paket adı ve script dosyasına göre yönetici seviyesinde paket kurulumu yapan bir uygulamadır.