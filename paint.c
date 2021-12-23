//
// Created by HJH201314 on 2021/11/3.
//

#ifndef BIGPROJECT_PAINT_C
#define BIGPROJECT_PAINT_C

#include <windows.h>
#include <stdio.h>
#include "global.h"

#define WALL_HORIZONTAL '@'
#define WALL_VERTICAL '#'
#define WALL_FLEX '+'

char esctip[WIDTH] = {};
char cWin[HEIGHT][WIDTH] = {};
char tips[WIDTH] = {};
int width_flex = W_MAX;
int height_flex = H_MAX;

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

void buildFlexFrame() {//构造可变的边框
    if (width_flex != W_MAX) {
        for (int i = 1; i <= height_flex; i++) {
            cWin[i][width_flex + 1] = WALL_FLEX;
        }
    }
    if (height_flex != H_MAX) {
        for (int i = 1; i <= width_flex + 1; i++) {//这个width_flex+1是给角落的
            cWin[height_flex + 1][i] = WALL_FLEX;
        }
    }
}

void gotoxy(short x, short y)//设置光标到x(左到右),y坐标(上到下),与项目的xy轴不同
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
    //system("cls");
    //不使用清除控制台,可以避免页面闪烁
}

void shineRed() {//闪烁红色警告
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_RED);
    output();//输出以应用红色
    Sleep(200);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    output();//输出以恢复白色
}

void shineGreen() {//闪烁绿色成功
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
    output();
    Sleep(200);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    output();
}

void randomDot(char ch) {
    int n = 10;
    int rand1, rand2;
    while (n--) {
        rand1 = rand() % (HEIGHT - 2) + 1;
        rand2 = rand() % (WIDTH - 3) + 1;
        if (cWin[rand1][rand2] >= 'a' && cWin[rand1][rand2] <= 'z')
            cWin[rand1][rand2]++;
        else
            cWin[rand1][rand2] = ch;
    }

}

void setPoint(int x, int y, char ch) {
    if (x >= 1 && y >= 1 && x <= H_MAX && y <= W_MAX) {//x,y都不能超过范围
        cWin[x][y] = ch;
    }
}

char getPoint(int x, int y) {
    if (x < 1 || x > height_flex) {
        return WALL_HORIZONTAL;
    } else if (y < 1 || y > width_flex) {//动态宽度
        return WALL_VERTICAL;
    } else {//x,y都没超过范围
        return cWin[x][y];
    }
}

void setLine(int line, char *ch) {//从cWin[]开头输出,不占满整行
    int len = (int) strlen(ch);//取回有效字符数
    if (line > 0 && line <= H_MAX) {//不能超过列最大值
        for (int i = 1; i <= len; i++) {
            if (i > W_MAX) {
                break;//不能超过行最大值
            }
            cWin[line][i] = ch[i - 1];//写入字符
        }
    }
}

void setLineFrom(int line, char *ch, int start) {//从cWin[]的第start位输出,不占满整行
    int len = (int) strlen(ch);//取回有效字符数
    if (line > 0 && line <= H_MAX && start > 0 && start <= W_MAX) {//不能超过列最大值
        for (int i = 0; i < len; i++) {
            if (i + start > W_MAX) {
                break;//不能超过行最大值
            }
            cWin[line][i + start] = ch[i];//写入字符
        }
    }
}

void setLineLeft(int line, char *ch) {//在某行左侧输出,占满整行
    char str[W_MAX + 1];
    initStrBlank(str, W_MAX);
    setStrFrom(str, 1, ch);
    setLine(line, str);
}

//在某行某范围居左输出,不占满整行
void setLineLeftN(int line, char *str, int rangeA, int rangeB) {
    setLineFrom(line, str, 1);
}

void setLineCenter(int line, char *ch) {//在某行中间输出,占满整行
    char str[W_MAX + 1];
    initStrBlank(str, W_MAX);
    resetStrCenter(str, ch);
    setLine(line, str);
}

//在某行居中输出,不占满整行
void setLineCenterN(int line, char *str, int rangeA, int rangeB) {
    int len_ch = (int) strlen(str);
    int start = (rangeB - rangeA - len_ch) / 2 + 1;//下标开始处
    setLineFrom(line, str, start);
}

void setLineRight(int line, char *ch) {//在某行右侧输出,占满整行
    char str[W_MAX + 1];
    initStrBlank(str, W_MAX);
    resetStrRight(str, ch);
    setLine(line, str);
}

//在某行居右输出,不占满整行
void setLineRightN(int line, char *str, int rangeA, int rangeB) {
    int len_ch = (int) strlen(str);
    int start = W_MAX - len_ch + 1;//下标开始处
    setLineFrom(line, str, start);
}

//设置tips
void setTips(char *str) {
    int len = (int) strlen(str);
    memset(tips, ' ', WIDTH - 1);
    if (len <= WIDTH - 1) {
        setStrFrom(tips, 1, str);
    }
    output();
}

//初始化页面,包含清空tips和构造框架
void initPage() {
    memset(tips, ' ', WIDTH - 1);
    buildFrame();
}

void output() {
    //输出cWin数组
    printf("%s", (char *) cWin);
    //输出提示和esc提示
    if (tips[0] != ' ') {
        printf("\n%s", (char *) tips);
        printf("\n%s", (char *) esctip);
    } else {
        printf("\n%s", (char *) esctip);
        printf("\n%s", (char *) tips);
    }
    //移动光标
    gotoxy(0, 0);
}

#endif //BIGPROJECT_PAINT_C
