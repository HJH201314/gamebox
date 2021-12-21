//
// Created by HJH201314 on 2021/12/19.
//

#include <conio.h>
#include <windows.h>

#include "global.h"

static void drawPageUser();
static int subpageGameRecord();
static void drawSubpageGameData();

extern char *username;

int pageUser() {
    initPage();
    drawPageUser();
    output();
    int ch = 0;
    while(1) {
        SetConsoleTitleA("个人信息");
        ch = _getch();
        switch (ch) {
            case KEY_ESC: return FLAG_EXIT;
            case '1':
                subpageGameRecord();break;
        }
        initPage();
        drawPageUser();
        output();
    }
}

//user界面的提示
static void drawPageUser() {
    setLineCenter(H_MAX / 2 - 2, formatStr("%s好,%s!",2,getTimePeriod(),username));
    setLineCenter(H_MAX / 2,"(1)游戏数据 (2)修改密码");
    setLineCenter(H_MAX / 2 + 2,"(3)切换帐号 (4)鹅鹅鹅鹅");
}

static int subpageGameRecord_page = 1;

//游戏记录子界面
static int subpageGameRecord() {
    initPage();
    drawSubpageGameData();
    output();
    int ch = 0;
    while(1) {
        SetConsoleTitleA("游戏记录");
        ch = _getch();
        switch (ch) {
            case KEY_ESC: return FLAG_EXIT;
            case KEY_TOP: case KEY_LEFT: {
                if (subpageGameRecord_page - 1 >= 1) {
                    subpageGameRecord_page--;
                    drawSubpageGameData();
                } else {
                    setTips("没有上一页了啦~");
                }
                break;
            }
            case KEY_BOTTOM: case KEY_RIGHT: {
                int ret = getRecordPageCount(username, H_MAX - 6);
                if (subpageGameRecord_page + 1 <= ret) {
                    subpageGameRecord_page++;
                    drawSubpageGameData();
                } else {
                    setTips("没有下一页了啦~");
                }
                break;
            }
            default:
                setTips("");
        }
        output();
    }
}

//游戏记录子界面的显示
static void drawSubpageGameData() {
    buildFrame();//因为换页,需要刷新
    int t = 0;
    GameRecord* gr = getRecord(username, H_MAX-6, subpageGameRecord_page, &t);
    setLineLeftN_(1,"使用↑/↓切换上下页");
    setLineRightN_(1, formatStr("总积分数:%d",1, getPoints(username)));
    setLineCenter(2, formatStr("%s的游戏记录(%d/%d)",3,username,subpageGameRecord_page, getRecordPageCount(username,H_MAX-6)));
    setLineCenter(4, formatStr("%-11s %-5s %-5s %-20s",4,"游戏","得分","积分","时间"));
    for (int i = 0; i < t; i++) {
        setLineCenter(i+6, formatStr("%-11s %-5d %-5d %-20s",4, getGameNameById(gr[i].game),gr[i].score,gr[i].points,gr[i].time));
    }
    free(gr);
}