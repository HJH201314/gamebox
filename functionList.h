//
// Created by HJH201314 on 2021/11/5.
// 本头文件包含所有可用的工具函数
//

#ifndef BIGPROJECT_FUNCTIONLIST_H
#define BIGPROJECT_FUNCTIONLIST_H

void initStrBlank(char * str, int size);//初始化str为空格(memset),size为str的可视长度
void clearStr(char * str);//将str前面不为\0的元素设置为空格(strlen)
void setStrFrom(char * str,int from,char * ch);//从from(>0)开始放置str的值(strlen),注意str可被设置的位置不为\0
void setStrCenter(char * str,char * ch);//居中在str中放置ch,注意str可被设置的位置不为\0
void setStrRight(char * str,char * ch);//居右在str中放置ch,注意str可被设置的位置不为\0
void resetStrCenter(char * str,char * ch);//清空原有文字并居中在str中放置ch注意str可被设置的位置不为\0
void resetStrRight(char * str,char * ch);//清空原有文字并居右在str中放置ch注意str可被设置的位置不为\0
char* formatStrD(char * format, int count,...);//直接返回格式化(仅%d)后的文本
char* connectStr(int count,...);//将count个字符串拼接起来,最长不超过wmax

void setLine(int line,char * ch);//将ch放入cWin的第line+1行
void setPoint(int x,int y,char ch);//将ch放入cWin的(x,y)
char getPoint(int x,int y);//获取cWin[x][y]
void setLineLeft(int line,char * ch);//在第line行居左输出ch
void setLineCenter(int line,char * ch);//在第line行居中输出ch
void setLineRight(int line,char * ch);//在第line行居右输出ch
void setTips(char * str);//设置提示
void initPage();//初始化页面,页面载入或重新载入时调用
void buildFrame();//构建框架(墙壁+中空)
void gotoxy(short x, short y);//定位输入到(x,y)
void output();//输出cWin

void addPoints(int n);//加积分
void delPoints(int n);//减积分
int getPoints();//获取积分

//bitUtils
int getBit(unsigned int n, int k);//获取无符号整数n的低第k位
unsigned int setBit(unsigned int n, int k);//设置无符号整数n的低第k位为1并返回
unsigned int resetBit(unsigned int n, int k);//设置无符号整数n的低第k位为0并返回

#endif //BIGPROJECT_FUNCTIONLIST_H
