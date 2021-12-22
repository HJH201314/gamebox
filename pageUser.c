//
// Created by HJH201314 on 2021/12/19.
//

#include <conio.h>
#include <windows.h>

#include "global.h"

static void drawPageUser();
static int subpageGameRecord();
static void drawSubpageGameData();
static int subpageChangePwd();
static void drawSubpageChangePwd();

extern char *username;

//主控 - 用户中心主界面
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
            case '2':
                subpageChangePwd();break;
        }
        initPage();
        drawPageUser();
        output();
    }
}

//显示 - 用户中心主界面
static void drawPageUser() {
    setLineCenter(H_MAX / 2 - 2, formatStr("%s好,%s!",2,getTimePeriod(),username));
    setLineCenter(H_MAX / 2,"(1)游戏数据 (2)修改密码");
    setLineCenter(H_MAX / 2 + 2,"(3)切换帐号 (4)鹅鹅鹅鹅");
}

static int subpageGameRecord_page = 1;

//主控 - 游戏记录子界面
static int subpageGameRecord() {
    initPage();
    drawSubpageGameData();
    output();
    int ch = 0;
    while(1) {
        SetConsoleTitleA("游戏记录");
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
                setTips("使用↑↓换页");//在框架中用↑↓符号会导致输出问题
        }
        output();
        ch = _getch();
    }
}

//显示 - 游戏记录子界面
static void drawSubpageGameData() {
    buildFrame();//因为换页,需要刷新
    int t = 0;
    GameRecord* gr = getRecord(username, H_MAX-6, subpageGameRecord_page, &t);
    setLineRightN_(1, formatStr("总积分数:%d",1, getPoints(username)));
    setLineCenter(2, formatStr("%s的游戏记录(%d/%d)",3,username,subpageGameRecord_page, getRecordPageCount(username,H_MAX-6)));
    setLineCenter(4, formatStr("%-11s %-5s %-5s %-20s",4,"游戏","得分","积分","时间"));
    for (int i = 0; i < t; i++) {
        setLineCenter(i+6, formatStr("%-11s %-5d %-5d %-20s",4, getGameNameById(gr[i].game),gr[i].score,gr[i].points,gr[i].time));
    }
    free(gr);
}

static char pwd[3][129];
static int progress_changepwd = 0;//0-验证旧密码;1-输入新密码;2-重复输入新密码
static int isInputingDir = 0;//是否正在输入方向键,方向键由两个字符构成,需要屏蔽
//主控 - 修改密码子界面
static int subpageChangePwd() {
    memset(pwd,'\0',129*3);
    progress_changepwd = 0;
    isInputingDir = 0;
    initPage();
    drawSubpageChangePwd();
    output();
    int ch = 0;
    while(1) {
        SetConsoleTitleA("修改密码");
        switch (ch) {
            case KEY_ESC: return FLAG_EXIT;
            case KEY_BACK: {
                int len = (int)strlen(pwd[progress_changepwd]);
                if (len >= 1) {//如果至少有一位密码
                    pwd[progress_changepwd][len - 1] = '\0';//删除最后一位
                    drawSubpageChangePwd();
                }
            }
            case KEY_TOP: {
                if (isInputingDir && progress_changepwd > 0) {
                    progress_changepwd--;
                    drawSubpageChangePwd();
                }
                isInputingDir = 0;
                setTips(formatStr("%d",1,progress_changepwd));
            }
            case KEY_BOTTOM: {
                if (isInputingDir && progress_changepwd < 2) {
                    progress_changepwd++;
                    drawSubpageChangePwd();
                }
                isInputingDir = 0;
                setTips(formatStr("%d",1,progress_changepwd));
            }
            case KEY_ENTER: {
                if (strlen(pwd[0]) && strlen(pwd[1]) && strlen(pwd[2])) {
                    if (login(username,pwd[0]) == 1) {//验证旧密码成功
                        if (strcmp(pwd[1],pwd[2]) == 0) {//两次输入相同
                            if (changePwd(username,pwd[2]) == 1) {//修改密码成功
                                progress_changepwd++;
                                buildFrame();
                                setLineCenter(H_MAX / 2 - 1,"修改密码成功!");
                                setLineCenter(H_MAX / 2 + 1,"按下Enter或Esc返回");
                            }
                        }
                    }
                } else if (progress_changepwd >= 3) {
                    return FLAG_EXIT;
                }
            }
            case KEY_DIR_FLAG: //方向键会触发两个字符,需要屏蔽
                isInputingDir = 1;
                break;
            default: isInputingDir = 0;
        }
        if (ch >= 32 && ch <= 126 && !isInputingDir) {//正确的字符且不是方向键输入
            if (strlen(pwd[progress_changepwd]) <= 127) {//如果不超过127位,则添加字符
                char p[2] = {};
                p[0] = (char)ch;
                strcat(pwd[progress_changepwd],p);
                drawSubpageChangePwd();
            } else {
                setTips("密码最多只能输入128位哦~");
            }
        }
        output();
        ch = _getch();
    }
}

//显示 - 修改密码子界面
static void drawSubpageChangePwd() {
    setLineCenter(H_MAX / 2 - 3, "请输入您的旧密码:");
    setLineCenter(H_MAX / 2 - 2, formatStr("%s%s%s",3,(progress_changepwd==0?">":""),pwd[0],(progress_changepwd==0?"<":"")));
    setLineCenter(H_MAX / 2 - 1, "请输入您的新密码:");
    setLineCenter(H_MAX / 2 - 0, formatStr("%s%s%s",3,(progress_changepwd==1?">":""),pwd[1],(progress_changepwd==1?"<":"")));
    setLineCenter(H_MAX / 2 + 1, "请再次输入您的新密码:");
    setLineCenter(H_MAX / 2 + 2, formatStr("%s%s%s",3,(progress_changepwd==2?">":""),pwd[2],(progress_changepwd==2?"<":"")));
}