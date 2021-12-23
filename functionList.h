//
// Created by HJH201314 on 2021/11/5.
// 本头文件包含所有可用的工具函数
//

#ifndef BIGPROJECT_FUNCTIONLIST_H
#define BIGPROJECT_FUNCTIONLIST_H

#include "user.h"
#include "point.h"
#include "sqlUtils.h"

//stringUtils - 字符串相关函数
void initStrBlank(char * str, int size);//初始化str为空格(memset),size为str的可视长度
void clearStr(char * str);//将str前面不为\0的元素设置为空格(strlen)
void setStrFrom(char * str,int from,char * ch);//从from(>0)开始放置str的值(strlen),注意str可被设置的位置不为\0
void setStrCenter(char * str,char * ch);//居中在str中放置ch,注意str可被设置的位置不为\0
void setStrRight(char * str,char * ch);//居右在str中放置ch,注意str可被设置的位置不为\0
void resetStrCenter(char * str,char * ch);//清空原有文字并居中在str中放置ch注意str可被设置的位置不为\0
void resetStrRight(char * str,char * ch);//清空原有文字并居右在str中放置ch注意str可被设置的位置不为\0
char* formatStr(char * format, int count, ...);//直接返回格式化后的文本
char* connectStr(int count,...);//将count个字符串拼接起来,最长不超过wmax

//paintUtils - 界面绘制相关函数
void setLine(int line,char * ch);//将ch放入cWin的第line+1行
void setPoint(int x,int y,char ch);//将ch放入cWin的(x,y)
char getPoint(int x,int y);//获取cWin[x][y]
void setLineFrom(int line,char * ch,int start);//将ch从start开始输出到cWin的第line+1行,不占满整行

#define setLineLeftN_(line,str) setLineLeftN(line,str,1,W_MAX)
#define setLineCenterN_(line,str) setLineCenterN(line,str,1,W_MAX)
#define setLineRightN_(line,str) setLineRightN(line,str,1,W_MAX)
void setLineLeft(int line,char * ch);//在第line行居左输出ch,其余填充空格
void setLineLeftN(int line, char *str, int rangeA, int rangeB);//在line行居左输出str,但其余不填充空格
void setLineCenter(int line,char * ch);//在第line行居中输出ch,其余填充空格
void setLineCenterN(int line, char *str, int rangeA, int rangeB);//在line行居中输出str,但其余不填充空格
void setLineRight(int line,char * ch);//在第line行居右输出ch,其余填充空格
void setLineRightN(int line, char *str, int rangeA, int rangeB);//在line行居右输出str,但其余不填充空格

void setTips(char * str);//设置提示
void setTipsAndShineRed(char *str);//设置提示并闪烁红色
void initPage();//初始化页面,页面载入或重新载入时调用
void buildFrame();//构建框架(墙壁+中空)
void buildFlexFrame();//构造中间框
void gotoxy(short x, short y);//定位输入到(x,y)
void shineRed();//闪烁红色警告
void shineGreen();//闪烁绿色成功
void output();//输出cWin

//bitUtils - 二进制位相关函数
int getBit(unsigned int n, int k);//获取无符号整数n的低第k位
unsigned int setBit(unsigned int n, int k);//设置无符号整数n的低第k位为1并返回
unsigned int resetBit(unsigned int n, int k);//设置无符号整数n的低第k位为0并返回

//timeUtils - 时间相关函数
char* getNowTime();//返回YYYY-DD-MM HH:mm:ss
char *getTimePeriod();//获取当前时间段(凌晨、上午、中午、下午、晚上)

void setError(int *error, int msg);

char *getGameNameById(int gameid);//通过游戏id获得游戏名

int sumDown(int n);//1+2+...+n

#endif //BIGPROJECT_FUNCTIONLIST_H
