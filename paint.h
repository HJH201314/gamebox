//
// Created by HJH201314 on 2021/11/3.
//

#ifndef BIGPROJECT_PAINT_H
#define BIGPROJECT_PAINT_H

#include <windows.h>
#include "headList.h"

#define WALL_HORIZONTAL '@'
#define WALL_VERTICAL '#'

char esctip[WIDTH] = {};
char cWin[HEIGHT][WIDTH] = {};
char tips[WIDTH] = {};

void gotoxy(short x,short y);

void buildFrame() {//构造边框
    for (int i = 0; i < HEIGHT; i++) {//左右两侧的壁
        cWin[i][0] = WALL_VERTICAL;
        cWin[i][WIDTH - 2] = WALL_VERTICAL;
        cWin[i][WIDTH - 1] = '\n';//换行
    }
    cWin[HEIGHT - 1][WIDTH - 1] = '\0';//结束符
    for (int i = 1; i < WIDTH - 2; i++) {
        cWin[0][i] = WALL_HORIZONTAL;
        cWin[HEIGHT - 1][i] = WALL_HORIZONTAL;
    }
    for (int i = 1; i < HEIGHT - 1; i++) {
        for (int j = 1; j < WIDTH - 2; j++) {
            cWin[i][j] = ' ';
        }
    }
}

void gotoxy(short x, short y)//设置光标到x,y坐标
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void randomDot(char ch) {
    int n = 10;
    int rand1,rand2;
    while(n--) {
        rand1=rand()%(HEIGHT - 2) + 1;
        rand2=rand()%(WIDTH - 3) + 1;
        if(cWin[rand1][rand2] >= 'a' && cWin[rand1][rand2] <= 'z')
            cWin[rand1][rand2]++;
        else
            cWin[rand1][rand2] = ch;
    }

}

void setPoint(int x,int y,char ch){
    if(x >= 1 && y >= 1 && x <= H_MAX && y <= W_MAX) {//x,y都不能超过范围
        cWin[x][y] = ch;
    }
}

char getPoint(int x,int y){
    if(x >= 1 && y >= 1 && x <= H_MAX && y <= W_MAX) {//x,y都不能超过范围
        return cWin[x][y];
    }
    return ' ';
}

void setLine(int line,char * ch){
    int len = (int)strlen(ch);//取回有效字符数
    if(line > 0 && line <= H_MAX) {//不能超过列最大值
        for(int i = 1;i <= len;i++) {
            if(i > W_MAX){
                break;//不能超过行最大值
            }
            cWin[line][i] = ch[i-1];//写入字符
        }
    }
}

void setLineLeft(int line,char * ch) {//直接在某行左侧输出
    char str[W_MAX + 1];
    initStrBlank(str, W_MAX);
    setStrFrom(str,1,ch);
    setLine(line,str);
}

void setLineCenter(int line,char * ch) {//直接在某行中间输出
    char str[W_MAX + 1];
    initStrBlank(str, W_MAX);
    resetStrCenter(str,ch);
    setLine(line,str);
}

void setLineRight(int line,char * ch) {//直接在某行右侧输出
    char str[W_MAX + 1];
    initStrBlank(str, W_MAX);
    resetStrRight(str,ch);
    setLine(line,str);
}

void setTips(char * str) {
    if(strlen(str) <= WIDTH - 1) {
        setStrFrom(tips,1,str);
    }
}

void initPage() {//初始化页面
    memset(tips,' ',WIDTH-1);
    buildFrame();
}

void output() {
    printf("%s",(char *)cWin);//将cWin数组输出
    if(tips[0] != ' ') {
        printf("\n%s",(char *)tips);
        printf("\n%s",(char *)esctip);
    } else {
        printf("\n%s",(char *)esctip);
        printf("\n%s",(char *)tips);
    }

    gotoxy(0,0);
}

#endif //BIGPROJECT_PAINT_H
