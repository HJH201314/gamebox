//
// Created by HJH201314 on 2021/11/3.
//

#ifndef BIGPROJECT_PAINT_H
#define BIGPROJECT_PAINT_H

#include <windows.h>
#define h 28
#define hmax 26//最大行是h-2
#define w 100
#define wmax 97//最大列是w-3

char cWin[h][w] = {};

void gotoxy(short x,short y);

void buildFrame() {//构造边框
    for (int i = 0; i < h; i++) {//左右两侧的壁
        cWin[i][0] = '|';
        cWin[i][w-2] = '|';
        cWin[i][w-1] = '\n';//换行
    }
    cWin[h-1][w-1] = '\0';//结束符
    for (int i = 1; i < w-2; i++) {
        cWin[0][i] = '-';
        cWin[h-1][i] = '-';
    }
    for (int i = 1; i < h-1; i++) {
        for (int j = 1; j < w-2; j++) {
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
        rand1=rand()%(h-2)+1;
        rand2=rand()%(w-3)+1;
        if(cWin[rand1][rand2] >= 'a' && cWin[rand1][rand2] <= 'z')
            cWin[rand1][rand2]++;
        else
            cWin[rand1][rand2] = ch;
    }

}

void setPoint(int x,int y,char ch){
    if(x <= hmax && y <= wmax) {//x,y都不能超过范围
        cWin[x][y] = ch;
    }
}

void setLine(int line,char * ch){
    int len = (int)strlen(ch);//取回有效字符数
    if(line > 0 && line <= hmax) {//不能超过列最大值
        for(int i = 1;i <= len;i++) {
            if(i > wmax){
                break;//不能超过行最大值
            }
            cWin[line][i] = ch[i-1];//写入字符
        }
    }
}

void setLineLeft(int line,char * ch) {//直接在某行左侧输出
    char str[wmax+1];
    initStrBlank(str,wmax);
    setStrFrom(str,1,ch);
    setLine(line,str);
}

void setLineCenter(int line,char * ch) {//直接在某行中间输出
    char str[wmax+1];
    initStrBlank(str,wmax);
    resetStrCenter(str,ch);
    setLine(line,str);
}

void setLineRight(int line,char * ch) {//直接在某行右侧输出
    char str[wmax+1];
    initStrBlank(str,wmax);
    resetStrRight(str,ch);
    setLine(line,str);
}

void output() {
    printf("%s",(char *)cWin);//将cWin数组输出
    printf("\nPress Esc to exit.\n按Esc键退出或返回上一级.");
    gotoxy(0,0);
}

#endif //BIGPROJECT_PAINT_H
