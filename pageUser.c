//
// Created by HJH201314 on 2021/12/19.
//

#include <conio.h>
#include <windows.h>

#include "global.h"

void drawPageUser();
int subpageGameData();
void drawSubpageGameData();

extern char *username;

int pageUser() {
    SetConsoleTitleA("个人信息");
    initPage();
    drawPageUser();
    output();
    int ch = 0;
    while(1) {
        ch = _getch();
        switch (ch) {
            case KEY_ESC: return FLAG_EXIT;
            case '1':
                subpageGameData();break;
        }
        initPage();
        drawPageUser();
        output();
    }
}

//user界面的提示
void drawPageUser() {
    setLineCenter(H_MAX / 2 - 2, formatStr("%s好,%s!",2,getTimePeriod(),username));
    setLineCenter(H_MAX / 2,"(1)游戏数据 (2)修改密码");
    setLineCenter(H_MAX / 2 + 2,"(3)切换帐号 (4)鹅鹅鹅鹅");
}

int subpageGameData() {
    initPage();
    drawSubpageGameData();
    output();
    int ch = 0;
    while(1) {
        ch = _getch();
        switch (ch) {
            case KEY_ESC: return FLAG_EXIT;
        }
        output();
    }
}

void drawSubpageGameData() {
    int t = 0;
    GameRecord* gr = getRecord(username, 10, 1, &t);
    //setTips(formatStr("%d",1,t));
    setLineCenter(2, formatStr("%-11s %-5s %-5s %-20s",4,"游戏","得分","积分","时间"));
    for (int i = 0; i < t; i++) {
        setLineCenter(i+4, formatStr("%-11s %-5d %-5d %-20s",4, getGameNameById(gr[i].game),gr[i].score,gr[i].points,gr[i].time));
    }
    free(gr);
}