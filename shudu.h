#ifndef SHUDU_H
#define SHUDU_H


#include<QSet>
#include<QPair>
#include<QVector>
class shudu
{
public:
    shudu();
    QSet<QPair<int ,int >> wakong_set();
    QVector<QVector<int>> shuju_v();

};

#endif // SHUDU_H
