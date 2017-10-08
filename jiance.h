#ifndef JIANCE_H
#define JIANCE_H

#include<QTableWidget>
#include"shudu.h"
class jiance
{
public:
    int jiance_i;
    int jiance_j;
    int tianru_num;
    QTableWidget *table_self;
    shudu *shu;
    jiance(QTableWidget *table,shudu* su);
    bool isTongguo();
};

#endif // JIANCE_H
