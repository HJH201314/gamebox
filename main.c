#ifndef BIGPROJECT_MAIN_C
#define BIGPROJECT_MAIN_C

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <process.h>
#include <string.h>
#include <stdarg.h>
#include <windows.h>

#include "global.h"

extern char esctip[];

int main() {
    //控制台光标处理start
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
    CursorInfo.bVisible = 0; //隐藏控制台光标
    SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
    //控制台光标处理end
    memset(esctip,' ',WIDTH-1);
    setStrFrom(esctip,1,"按下Esc键退出或返回上级");

    srand(getpid());

    initPage();

    pageMain();

    return 0;
}

#endif //BIGPROJECT_MAIN_C