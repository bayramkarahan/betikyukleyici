#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<appwidget.h>
#include <QMainWindow>
#include<filecrud.h>
#include<QDialog>
#include<QPushButton>
#include<QTableWidget>
#include<QMessageBox>
#include<QProcess>
#include<QProgressBar>
#include<QPlainTextEdit>
#include<QTabWidget>
#include<QToolButton>
#include<QHBoxLayout>
#include<QWidget>
#include<QGridLayout>
#include<QScrollArea>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void installSlot(QString paket);
     void removeSlot(QString paket);
    void listToFile(QStringList list, QString filename);
    QStringList fileToList(QString filename);
    QString listGetLine(QStringList list,QString data);
    QStringList listRemove(QStringList list,QString data);
    QStringList listReplace(QStringList list,QString oldData,QString newData,int index);
    QStringList listMerge(QStringList list1, QStringList list2,int dataIndex);
    QStringList listGetList(QStringList list, QString data,int index);
   QWidget *paketSlot(QWidget *parent);
   void paketTableCellDoubleClicked(int iRow, int iColumn);
   void paketTableWidgetWindow_cellClicked(int iRow, int iColumn);
   void disp();
   void procresbegin();
   void procresend();
   void about();
   QString myMessageBox(QString baslik, QString mesaj, QString evet, QString hayir, QString tamam, QMessageBox::Icon icon);
    void findTextEditChanged();
   void appList();
private:
      // QList<QToolButton*> appsListButton;
    QList<QWidget*> appsListButton;
        QGridLayout *appslayout;
    int en;
    int boy;
    QString localDir;
    QTableWidget *twl;
    QString selectPaketName;
     QString selectPaketAddressInstall;
     QString selectPaketAddressRemove;
    QProgressBar *progressbar;
    QProcess *proces;
     QProcess *proces1;
    int val=0;
    QLabel *statusLabel;
    QLabel *findTextEditLabel;

    QTextEdit *findTextEdit;
    QTextEdit *doc;
    QTextEdit *installscriptTextEdit;
    QTextEdit *removescriptTextEdit;

    QWidget *mwidget;
    QString  procesType="";
    QString version="";
    QString updateFile="";

    QToolButton *updateButton;
    QToolButton *installerButton;
    QToolButton *removeButton;
    QToolButton *aboutButton;

    int selectRowIndex=0;
    QWidget *hakkinda();
};

#endif // MAINWINDOW_H
