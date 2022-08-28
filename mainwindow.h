#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include<QWidget>

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
private:
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
