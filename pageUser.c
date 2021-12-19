//
// Created by HJH201314 on 2021/12/19.
//

#include <conio.h>
#include <windows.h>

#include "global.h"

void drawPageUser();

extern char *username;

int pageUser() {
    initPage();
    int ch = 0;
    while(1) {
        switch (ch) {
            case KEY_ESC: return FLAG_EXIT;
            default:drawPageUser();
        }
        output();
        ch = _getch();
    }
}

//user界面的提示
void drawPageUser() {
    setLineCenter(H_MAX / 2 - 2, formatStr("%s好,%s!",2,getTimePeriod(),username));
    setLineCenter(H_MAX / 2,"(1)游戏数据 (2)修改密码");
    setLineCenter(H_MAX / 2 + 2,"(3)切换帐号 (4)鹅鹅鹅鹅");
}