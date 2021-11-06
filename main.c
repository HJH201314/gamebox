#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <process.h>
#include <string.h>
#include <stdarg.h>

#define FREQ 10//窗口刷新率
#define KEY_BACK 8//Backspace的键值
#define KEY_ENTER 13//Enter的键值
#define KEY_ESC 27//Esc的键值

#include "funtionList.h"
#include "paint.h"//绘制窗口的头文件,include了windows.h
#include "utils.h"//工具
#include "pageMain.h"//首页

int main() {
    //控制台光标处理start
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
    CursorInfo.bVisible = 0; //隐藏控制台光标
    SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
    //控制台光标处理end

    srand(getpid());

    buildFrame();

    pageMain();

    return 0;
}
