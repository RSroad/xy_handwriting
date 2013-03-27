#ifndef JUDGE_H
#define JUDGE_H

#define MAXSIZE 600
#define TRUE_  1
#define FALSE_ 0

/*数据流斜率判断的定义*/
#define TAN22_5 0.4142135   //tan(22.5)   tan(x)的值与后面数据流斜率的判断有关，需要经过多次测试 寻找出一个合理笔画判断的范围
#define TAN45 1 //tan(45)   //小于25判断为点
#define TAN315 -1	    //tan(337.5)

/*五笔码笔画宏定义*/
#define HENG 1
#define SHU 2
#define PIE 3
#define NA 4
#define DIAN 4
#define OTHER 5


#define M_ROW 16  /*结果数组行*/
#define M_COL 4   /*结果数组列*/

/*图像界*/
#define OVER 400

typedef struct my_arr {
        int x;
        int y;
}Coor;

typedef struct l_oth
{
    char other[50];
    struct l_oth *next;
}l_other;

extern char chinese_result[M_ROW][M_COL];
extern int m_FLAG;

#endif // JUDGE_H
