#include "shudu.h"
#include<stdlib.h>
#include<QSet>
#include<QVector>
#include<QPair>
#include<time.h>
#include<QDebug>
#define Random(x) rand()%x
using namespace std;


QSet<QPair<int, int> >  s;
QPair<int, int> jilu_QSet;
QVector<QVector<int>> shuju(9, QVector<int>(9, 0));
bool valid( const int hang, const int lie, const int &num) {
    //在这里就是一个一个比对 因为后面的没有生成  只要判断已经生成的干扰项

    //所以 对于行、列、宫 三个条件 只需要到自己所对应的行去就好了

    //先检查同一行的有没有一样的
    for (int j = 0; j < lie; j++) {
        if (shuju.at(hang).at(j) == num) {
            return false;
        }
    }
    //检查列有没有相同的
    for (int i = 0; i < hang; i++) {
        if (shuju.at(i).at(lie) == num) {
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
            if (shuju.at(i).at(j) == num) {
                return false;
            }
        }
    }
    return true;
}
//QVector<QVector<int>> &shuju,
bool shengcheng(const QSet<int> &shu) {

    int hang(0), lie(0), suiji_number(0);
    QVector<QSet<int>> zancun;
    QSet<int> houxuan_number(shu);
    while (hang < 9) {
        while (lie < 9) {

            while (!houxuan_number.empty()) {
                suiji_number = Random(9) + 1;
                //cout << "suiji_number " << suiji_number<<endl;
                auto itear = houxuan_number.find(suiji_number);
                if (itear != houxuan_number.end()) {
                    //不是end 说明这个数据在set中是存在的
                    houxuan_number.erase(itear);
                }
                else
                {
                    //随机找到的这个数是不存在在set中的数字
                    continue;
                }
                //已经生成了随机数
                if (valid(hang, lie, suiji_number)) {
                    //如果成功了 将shuju的i,j置为当前的数
                    shuju[hang][lie] = suiji_number;
                    //之后 移动行、列  准备接收新的东西
                    if (hang == 8 && lie == 8) {
                        //已经接收完毕
                        return true;
                    }
                    if (lie == 8 && hang < 8)
                    {
                        lie = 0;
                        hang++;

                    }
                    else
                    {
                        lie++;

                    }
                    zancun.push_back(houxuan_number);
                    houxuan_number = shu;
                    break;//跳出找随机数的循环
                }
                else
                {
                    continue;
                }
            }
            if (houxuan_number.empty()) {
                //如果候选的number为空了  那么 进行回溯
                shuju[hang][lie] = 0;//将当前位置置零
                if (lie > 0 && lie <= 8) {
                    lie--;
                }
                if(lie==0 && hang>0)
                {
                    lie = 8;
                    hang--;
                }
                if (lie==0 && hang==0) {
                    qDebug() << "没有结果" << endl;
                    return false;
                }
                auto iend = zancun.end();
                houxuan_number = *(iend - 1);
                zancun.pop_back();
            }
        }
    }

}

void print() {

    int sizeofshuju = shuju.size();
    int sizeofshuju1 = shuju.at(1).size();
    for (int i = 0; i < sizeofshuju; i++) {
        for (int j = 0; j < sizeofshuju1; j++) {
            //qDebug() << shuju.at(i).at(j) << " ";
            //fout << shuju.at(i).at(j);
            qDebug()<< shuju.at(i).at(j);

            if (j != (sizeofshuju1 - 1)) {
               // fout << " ";
                qDebug()<<"  ";
            }
        }
        if (i != (sizeofshuju - 1)) {
            qDebug() << endl;
            //fout << endl;
        }
    }
}
//QVector<QVector<int>> &shuju
void gongge_wakong(int i, int j) {
    //只要让每个宫里面的空 大于等于4 小于等于6  那么 总数就是大于30 小于60 的
    int wakong_shu = Random(3) + 4;
    qDebug() << "wakong_shu  " << wakong_shu << endl;
    int jilu (0),suiji_i(0),suiji_j(0);

    while (jilu <= wakong_shu) {
        suiji_i = Random(3) + i;//产生i+(0,1,2)的随机数
        suiji_j = Random(3) + j;
        jilu_QSet = qMakePair(suiji_i, suiji_j);

        if (jilu == 0) {
            s.insert(jilu_QSet);
            jilu++;
        }
        else
        {
            if (s.find(jilu_QSet) == s.end())
            {
                //if not find then insert
                s.insert(jilu_QSet);
                qDebug() << "jilu_QSet  " << jilu_QSet.first << "   " << jilu_QSet.second << endl;
                shuju[suiji_i][suiji_j] = 0;
                jilu++;
            }
            else
            {
                continue;
            }
        }
    }

}
//QVector<QVector<int>> &shuju
void wakong() {
    int gongge_biaoji(0),gongge_i(0),gongge_j(0);
    while (gongge_biaoji < 9) {
        gongge_wakong(gongge_i, gongge_j);
        if (gongge_j == 6&gongge_i<6) {
            gongge_j = 0;
            gongge_i+=3;
        }
        else if(gongge_i==6&&gongge_j==6)
        {
            break;
        }
        else
        {
            gongge_j+=3;
        }
        gongge_biaoji++;
    }
}

shudu::shudu()
{

    srand((unsigned)time(NULL));
    QSet<int > shu;
    for (int i = 1; i < 10; i++) {
        shu.insert(i);
    }


    if (shengcheng(shu)) {
        print();
        //QVector<QVector<int>> shuju_zhongpan(shuju);
        //此时已经生成算法调用完成 接下来就是挖空
        wakong();
        //print();
    }


    //fout.close();system("pause");

}
QSet<QPair<int, int> > shudu::wakong_set(){
    return s;
}
QVector<QVector<int>> shudu::shuju_v(){
    return shuju;

}
