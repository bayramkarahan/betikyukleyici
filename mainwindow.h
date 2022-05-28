#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<filecrud.h>
#include<QDialog>
#include<QPushButton>
#include<QTableWidget>
#include<QMessageBox>

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
   QWidget *paketSlot();
   void paketTableCellDoubleClicked(int iRow, int iColumn);
   void paketTableWidgetWindow_cellClicked(int iRow, int iColumn);
private:
    int en;
    int boy;
    QString localDir;
    QTableWidget *twl;
    QString selectPaketName;
    QString selectPaketAddress;

};

#endif // MAINWINDOW_H
