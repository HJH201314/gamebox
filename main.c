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
#include "lib/hashMap.h"
#include "global.h"

extern char esctip[];
extern int freq;

char username[129] = "guest";
HASHMAP(char, int) setting_map;//定义一个以char为key,int为value的hashmap
sqlite3 *db;//数据库

int main() {
    //控制台光标处理
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
    CursorInfo.bVisible = 0; //隐藏控制台光标
    SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态

    //初始化数据库
    sqlite3_open_v2("gamebox.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    //创建表
    if (!isTableExist(db, "record")) {//游戏记录
        sqlite3_exec(db,
                     "CREATE TABLE record ( game INTEGER, username TEXT, score INTEGER, points INTEGER, time TEXT (20) ); ",
                     NULL, NULL, NULL);
    }
    if (!isTableExist(db, "user")) {//用户
        sqlite3_exec(db,
                     "CREATE TABLE user ( username TEXT, password TEXT, points INTEGER DEFAULT (0), regtime TEXT (20), logtime TEXT (20) ); ",
                     NULL, NULL, NULL);
    }
    if (!isTableExist(db, "setting")) {//设置
        sqlite3_exec(db,
                     "CREATE TABLE setting ( item TEXT PRIMARY KEY, value INTEGER ); ",
                     NULL, NULL, NULL);
    }
    if (!isTableExist(db, "backpack")) {
        sqlite3_exec(db, "CREATE TABLE backpack ( username TEXT, item INTEGER, count INTEGER DEFAULT (0) ); ", NULL, NULL, NULL);
    }
    //创建默认用户
    if (!isUserExist("guest")) {
        createUser("guest", "123456", NULL);
    }
    //载入上次的用户
    char temp[256] = {};
    readFileOneLine("CurrentUser", temp);
    if (isUserExist(temp)) {
        strcpy(username, temp);
    } else {
        strcpy(username, "guest");
    }

    //TODO: 设置
//    //初始化设置
//    if (!isSettingExist("freq")) {
//        putSetting("freq",FREQ_DEFAULT);
//    }
//    //初始化hashmap
//    hashmap_init(&setting_map,hashmap_hash_string,strcmp);
//    initSettingMap();
//    freq = getSetting("freq");

    //设置最后一行的Esc键提示
    memset(esctip, ' ', WIDTH - 1);
    setStrFrom(esctip, 1, "按下Esc键退出或返回上级");

    //生成随机数种子
    srand((unsigned)time(NULL));

    //初始化界面
    initPage();

    //载入首页
    pageMain();

    //退出程序时关闭数据库
    sqlite3_close_v2(db);
    return 0;
}

#endif //BIGPROJECT_MAIN_C