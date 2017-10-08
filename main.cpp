#include "mainwindow.h"
#include"shudu.h"
#include"jiance.h"
#include <QApplication>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QDebug>
#include<QVBoxLayout>
#include<QVector>
#include<QString>
#include<QPushButton>
#include<QHBoxLayout>
#include<QMessageBox>

bool has_kongge(QTableWidget * table){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(table->item(i,j)->text()==""){
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QWidget *mainwidget=new QWidget(&w);
    QVBoxLayout lay;

    QTableWidget *table=new QTableWidget();
    table->setColumnCount(9);
    table->setRowCount(9);
    for(int i=0;i<9;i++){
       table->setColumnWidth(i,40);
    }
    for(int i=0;i<9;i++){
       table->setRowHeight(i,40);
    }

    shudu *su=new shudu;

    QTableWidgetItem *item;

    QVector<QVector<int>> re_v=su->shuju_v();

    int sizeofre=re_v.size();
    int sizeofre_1=re_v[1].size();

    for(int i=0;i<sizeofre;i++){
        for(int j=0;j<sizeofre_1;j++){
            item=new QTableWidgetItem();

            item->setTextAlignment(Qt::AlignCenter);

            if(re_v[i][j]!=0){
                item->setText(QString::number(re_v[i][j]));
                item->setFlags(item->flags() & (~Qt::ItemIsEditable));
            }else {
                item->setText("");
            }
            table->setItem(i,j,item);


        }

    }

    lay.addWidget(table);


    QPushButton *button=new QPushButton("提交");

    QMessageBox *box;
    QObject::connect(button,&QPushButton::clicked,[&](){
        qDebug()<<"button clicked";

        jiance jian(table,su);

       if(has_kongge(table)){
           qDebug()<<"has kongge";
           box=new QMessageBox(QMessageBox::Warning,"系统提示","还未完成，请继续答题！");
           box->exec();
           //box->show();
           return;
       }

       if(jian.isTongguo()){
           qDebug()<<"tongguo";

           box=new QMessageBox(QMessageBox::Information,"系统提示","恭喜你，回答正确！");
           box->exec();
       }else {
           qDebug()<<"failed";
           box=new QMessageBox(QMessageBox::Information,"系统提示","很抱歉，您未通过此数独。");
           box->exec();
           //还未找到有效的方法重新加载数据
//           box=new QMessageBox(QMessageBox::Warning,"系统提示","很抱歉，您未通过此数独。");
//           box->setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
//           box->setButtonText (QMessageBox::Ok,QString("继续"));
//           box->setButtonText (QMessageBox::Cancel,QString("重置"));

       }

    });

    lay.addWidget(button);


    mainwidget->setLayout(&lay);
    w.setCentralWidget(mainwidget);
    w.setWindowTitle("sudoku");
    w.resize(400,480);

    w.show();

    return a.exec();
}
