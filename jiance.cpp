#include "jiance.h"
#include"shudu.h"

#include<QSet>
#include<QPair>

#include<QDebug>
jiance::jiance(QTableWidget *table,shudu* su)
{
    table_self=table;
    shu=su;
    //for(int i=0;i<9;i++){
       // for(int j=0;j<9;j++){
           // qDebug()<<table_self->item(i,j)->text().toInt();
       // }
    //}
}

bool valid( const int hang, const int lie, const int &num,QTableWidget *tab ) {


    //所以 对于行、列、宫 三个条件 只需要到自己所对应的行去就好了

    //先检查同一行的有没有一样的
    for (int j = 0; j < 9; j++) {
        if(j==lie){
            continue;
        }
        if (tab->item(hang,j)->text().toInt() == num) {
            qDebug()<<hang<<" "<<j<<"  与 "<<hang<<" "<<lie<<"  "<<"相同";
            return false;
        }
    }
    //检查列有没有相同的
    for (int i = 0; i < 9; i++) {
        if(i==hang){
            continue;
        }
        if (tab->item(i,lie)->text().toInt() == num) {
            qDebug()<<i<<" "<<lie<<"  与 "<<hang<<" "<<lie<<"  "<<"相同";
            return false;
        }
    }

    //检查宫格

    int block_hang_start = (hang / 3) * 3;
    int block_hang_end = block_hang_start + 3;

    int block_lie_start = (lie / 3) * 3;
    int block_lie_end = block_lie_start + 3;


    for (int i = block_hang_start; i < block_hang_end; i++) {
        for (int j = block_lie_start; j < block_lie_end; j++) {
            if(i==hang&&j==lie){
                continue;
            }
            if (tab->item(i,j)->text().toInt() == num) {
                 qDebug()<<i<<" "<<j<<"  与 "<<hang<<" "<<lie<<"  "<<"相同";
                return false;
            }
        }
    }
    return true;
}
bool jiance::isTongguo(){

    QSet<QPair<int ,int >> daijiance=shu->wakong_set();
    qDebug()<<"daijiance.count()  "<<daijiance.count();
    auto ibegin=daijiance.begin();
    auto iend=daijiance.end();
    qDebug()<<"table_self->item(1,1)->text().toInt()  "<<table_self->item(1,1)->text().toInt();
    for(;ibegin!=iend;ibegin++){
        jiance_i=(*ibegin).first;
        jiance_j=(*ibegin).second;
        tianru_num=table_self->item(jiance_i,jiance_j)->text().toInt();
        //qDebug()<<table_self->item(5,5)->text().toInt();
        if(valid(jiance_i,jiance_j,tianru_num,table_self)){
            continue;
        }else {
            return false;
        }
    }

    return true;
}
