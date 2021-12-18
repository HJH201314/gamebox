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
#include "lib/sqlite3.h"
#include "sqlUtils.h"
#include "global.h"

extern char esctip[];

char *username = "guest";
sqlite3 *db;//数据库

int main() {
    //控制台光标处理start
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
    CursorInfo.bVisible = 0; //隐藏控制台光标
    SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态

    //初始化数据库
    sqlite3_open_v2("gamebox.db",&db,SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE,NULL);
    //新建表
    if(!isTableExist(db,"record")) {
        sqlite3_exec(db,
                     "CREATE TABLE record ( gamename TEXT, username TEXT, score INTEGER, points INTEGER, time TEXT (20) ); ",
                     NULL, NULL, NULL);
    }
    if(!isTableExist(db,"user")) {
        sqlite3_exec(db,
                     "CREATE TABLE user ( username TEXT, password TEXT, points INTEGER DEFAULT (0), regtime TEXT (20), logtime TEXT (20) ); ",
                     NULL, NULL, NULL);
    }
    //创建默认用户
    createUser("guest","123456",NULL);

    //设置最后一行的Esc键提示
    memset(esctip,' ',WIDTH-1);
    setStrFrom(esctip,1,"按下Esc键退出或返回上级");

    //生成随机数种子
    srand(getpid());

    //初始化界面
    initPage();

    //载入首页
    pageMain();

    //退出程序时关闭数据库
    sqlite3_close_v2(db);
    return 0;
}

#endif //BIGPROJECT_MAIN_C