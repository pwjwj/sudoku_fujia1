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
bool go_next = false;

bool shengcheng( int hang, int lie, const QSet<int> &shu) {
    QSet<int> houxuan_number(shu);
    int suiji_number(0);
    //填充
    while (!houxuan_number.empty()) {
        suiji_number = Random(9) + 1;
        //qDebug() << "suiji_number " << suiji_number<<endl;
        auto itear = houxuan_number.find(suiji_number);
        if (itear != houxuan_number.end()) {
            //不是end 说明这个数据在QSet中是存在的
            houxuan_number.erase(itear);
        }
        else
        {
            //随机找到的这个数是不存在在QSet中的数字
            continue;
        }
        if (valid( hang, lie, suiji_number)) {
            //验证通过了再进行写入
           // shuju.at(hang).at(lie) = suiji_number
            shuju[hang][lie]=suiji_number;
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
            go_next = shengcheng( hang, lie, shu);
            //这时候看上一个是否还有houxuan_number的数据  有的话再次while
            //如果匹配成功 那么 就会进行下一个的查找
            if (go_next == true) {
                //在最后一个返回true时 由于记录了这个返回值 在这里就会一直往回返true
                return true;
            }
        }
        else
        {
            //如果没通过  在当前行 当前列下  接着试探下一个
            continue;
        }
    }
    //所有的1-9都试探完了 还没找到位置 那就先随便给一个值
    if (houxuan_number.empty()) {
        shuju[hang][lie] = 0;
        return false;
    }

}
//QVector<QVector<int>> &shuju
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


    if (shengcheng( 0, 0, shu)) {
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
