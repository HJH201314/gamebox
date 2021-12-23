//
// Created by HJH201314 on 2021/12/19.
//

#include <conio.h>
#include <windows.h>
#include <stdio.h>

#include "global.h"

static void drawPageUser();
static int subpageGameRecord();
static void drawSubpageGameData();
static int subpageChangePwd();
static void drawSubpageChangePwd();
static int subpageChangeAccount();
static void drawSubpageChangeAccount();

extern char username[129];

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
            case '3':
                subpageChangeAccount();break;
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
    setLineCenter(H_MAX / 2 + 2,"(3)切换帐号 (4)删除账号");
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

static char userinfo[3][129];
static int progress = 0;//0-验证旧密码;1-输入新密码;2-重复输入新密码
static int isInputingDir = 0;//是否正在输入方向键,方向键由两个字符构成,需要屏蔽
//主控 - 修改密码子界面
static int subpageChangePwd() {
    memset(userinfo, '\0', 129 * 3);
    progress = 0;
    isInputingDir = 0;
    initPage();
    drawSubpageChangePwd();
    output();
    int ch = 0;
    while(1) {
        setTips("");
        SetConsoleTitleA("修改密码");
        switch (ch) {
            case KEY_ESC: return FLAG_EXIT;
            case KEY_TAB: {
                progress = (progress + 1) % 3;
                drawSubpageChangePwd();
                break;
            }
            case KEY_BACK: {
                int len = (int)strlen(userinfo[progress]);
                if (len >= 1) {//如果至少有一位密码
                    userinfo[progress][len - 1] = '\0';//删除最后一位
                    drawSubpageChangePwd();
                }
                break;
            }
            case KEY_TOP: {
                if (isInputingDir && progress > 0) {
                    progress--;
                    drawSubpageChangePwd();
                }
                break;
            }
            case KEY_BOTTOM: {
                if (isInputingDir && progress < 2) {
                    progress++;
                    drawSubpageChangePwd();
                }
                break;
            }
            case KEY_ENTER: {
                if (progress < 2) {//回车下移
                    progress++;
                    drawSubpageChangePwd();
                } else if (progress >= 3) {//已经修改完毕
                    return FLAG_EXIT;
                } else if (strlen(userinfo[0]) && strlen(userinfo[1]) && strlen(userinfo[2])) {
                    if (login(username, userinfo[0]) == 1) {//验证旧密码成功
                        if (strcmp(userinfo[1], userinfo[2]) == 0) {//两次输入相同
                            if (changePwd(username, userinfo[2]) == 1) {//修改密码成功
                                progress++;
                                buildFrame();
                                setLineCenter(H_MAX / 2 - 1,"修改密码成功!");
                                setLineCenter(H_MAX / 2 + 1,"按下Enter或Esc返回");
                                shineGreen();
                            } else {
                                setTips("修改密码失败,数据库错误!");
                                shineRed();
                            }
                        } else {
                            setTips("两次输入的密码不一致!");
                            shineRed();
                        }
                    } else {
                        setTips("原密码错误!");
                        shineRed();//发生错误闪烁警告
                    }
                }
                break;
            }
            case KEY_DIR_FLAG: //方向键会触发两个字符,需要屏蔽
                isInputingDir = 1;
                break;
            default: isInputingDir = 0;
        }
        if (ch >= 32 && ch <= 126 && !isInputingDir) {//正确的字符且不是方向键输入
            if (strlen(userinfo[progress]) <= 127) {//如果不超过127位,则添加字符
                char p[2] = {};
                p[0] = (char)ch;
                strcat(userinfo[progress], p);
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
    setLineCenter(H_MAX / 2 - 6, "修改密码");
    setLineCenter(H_MAX / 2 - 3, "请输入您的旧密码:");
    setLineCenter(H_MAX / 2 - 2, formatStr("%s%s%s", 3, (progress == 0 ? ">" : ""), userinfo[0], (progress == 0 ? "<" : "")));
    setLineCenter(H_MAX / 2 - 1, "请输入您的新密码:");
    setLineCenter(H_MAX / 2 - 0, formatStr("%s%s%s", 3, (progress == 1 ? ">" : ""), userinfo[1], (progress == 1 ? "<" : "")));
    setLineCenter(H_MAX / 2 + 1, "请重复您的新密码:");
    setLineCenter(H_MAX / 2 + 2, formatStr("%s%s%s", 3, (progress == 2 ? ">" : ""), userinfo[2], (progress == 2 ? "<" : "")));
}

//主控 - 切换账号子界面
static int selector = 0;
static int subpageChangeAccount() {
    initPage();
    memset(userinfo, '\0', 2 * 129);
    isInputingDir = 0;
    progress = 0;
    drawSubpageChangeAccount();
    output();
    int ch = 0;
    while(1) {
        setTips("");
        SetConsoleTitleA("切换账号");
        switch (ch) {
            case KEY_ESC: return FLAG_EXIT;
            case KEY_TAB: {
                progress = (progress + 1) % 2;
                drawSubpageChangeAccount();
                break;
            }
            case KEY_BACK: {
                int len = (int)strlen(userinfo[progress]);
                if (len >= 1) {//如果至少有一位
                    userinfo[progress][len - 1] = '\0';//删除最后一位
                    drawSubpageChangeAccount();
                }
                break;
            }
            case KEY_TOP: {
                if (isInputingDir && progress > 0) {
                    progress--;
                    drawSubpageChangeAccount();
                }
                break;
            }
            case KEY_BOTTOM: {
                if (isInputingDir && progress < 2) {
                    progress++;
                    drawSubpageChangeAccount();
                }
                break;
            }
            case KEY_LEFT: {
                if (isInputingDir && selector > 0 && progress == 2) {
                    selector--;
                    drawSubpageChangeAccount();
                }
                break;
            }
            case KEY_RIGHT: {
                if (isInputingDir && selector < 1 && progress == 2) {
                    selector++;
                    drawSubpageChangeAccount();
                }
                break;
            }
            case KEY_ENTER: {
                //progress:0-输入帐号,1-输入密码,2-选择登录或注册
                if (progress < 2) {//回车下移
                    progress++;
                    drawSubpageChangeAccount();
                } else if (progress >= 3) {//已经修改完毕
                    return FLAG_EXIT;
                } else if (selector == 0 && strlen(userinfo[0]) && strlen(userinfo[1])) {//指向登录时
                    if (isUserExist(userinfo[0])) {
                        if (login(userinfo[0], userinfo[1]) == 1) {//登录成功
                            progress++;
                            strcpy(username, userinfo[0]);
                            buildFrame();
                            setLineCenter(H_MAX / 2 - 1,formatStr("欢迎回来,%s!",1,username));
                            setLineCenter(H_MAX / 2 + 1,"按下Enter或Esc返回");
                            shineGreen();
                        } else {
                            setTips("密码错误!");
                            shineRed();//发生错误闪烁警告
                        }
                    } else {
                        setTips("账号不存在!");
                        shineRed();
                    }
                }
                break;
            }
            case KEY_DIR_FLAG: //方向键会触发两个字符,需要屏蔽
                isInputingDir = 1;
                break;
            default: isInputingDir = 0;
        }
        if (ch >= 32 && ch <= 126 && !isInputingDir) {//正确的字符且不是方向键输入
            //TODO: 目前使用左右键时仍然会输入字母
            if (strlen(userinfo[progress]) <= 127) {//如果不超过127位,则添加字符
                char p[2] = {};
                p[0] = (char)ch;
                strcat(userinfo[progress], p);
                drawSubpageChangeAccount();
            } else {
                setTips("最多只能输入128位哦~");
            }
        }
        output();
        ch = _getch();
    }
}

//界面 - 切换帐号子界面
static void drawSubpageChangeAccount() {
    setLineCenter(H_MAX / 2 - 4,"切换账号");
    setLineCenter(H_MAX / 2 - 1, formatStr("账号:%s%s", 2, (progress == 0 ? ">" : ""), userinfo[0]));
    setLineCenter(H_MAX / 2 + 1, formatStr("密码:%s%s", 2, (progress == 1 ? ">" : ""), userinfo[1]));
    setLineCenter(H_MAX / 2 + 3, formatStr("%s登录%s %s注册%s", 4, ((progress == 2 && selector == 0) ? ">" : ""), ((progress == 2 && selector == 0) ? "<" : ""), ((progress == 2 && selector == 1) ? ">" : ""), ((progress == 2 && selector == 1) ? "<" : "")));
}