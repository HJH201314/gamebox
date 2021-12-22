//
// Created by HJH201314 on 2021/11/5.
//

#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "global.h"

#define TRYTIME_BASE_MAX 10//第一关的最大值

static int midline = H_MAX / 2;//中间行
static char input_str[W_MAX + 1] = "";//即将输入的数字
static long input_num;//输入"数字"转成的长整数
static int try_times = 0;
static int try_time_max = TRYTIME_BASE_MAX;
static int correct_times = 0;
static char is_correct = 0;
static long random_num = 0;
static char random_str[20];//随机数转成的字符串

static int getKeyPress();//执行获取键盘操作

extern char username[129];

static void initGame() {//初始化游戏
    input_num = 0;//输入"数字"转成的长整数
    try_times = 0;
    try_time_max = TRYTIME_BASE_MAX;
    correct_times = 0;
    is_correct = 0;
    random_num = rand() % (101 + 100 * correct_times) + 1;//生成一个随机数[1~100(+correct*50)]
    ltoa(random_num, random_str, 10);//转字符串
}

int pageGuessNumber() {//返回0即返回mainPage,1就重开
    SetConsoleTitleA("猜数字");
    initPage();
    initGame();
    char key_result = 0;
    while (1) {
        setLineCenter(midline - 4, formatStr("Level %d (1~%d)", 2, correct_times + 1, 100 + 100 * correct_times));
        setLineCenter(midline - 2, "Please guess a number (and press Enter):");
        //setLineCenter(H_MAX/2-1, random_str);
        key_result = getKeyPress();
        if(key_result != 0) return key_result;
        setLineRight(1, formatStr("You have tried %d times(%d max)", 2, try_times, try_time_max));
        setLineCenter(midline, input_str);

        output();
        Sleep(FREQ);
    }
    return FLAG_EXIT;
}

static int getKeyPress(){
    int ch;
    if (_kbhit()) {//是否有按下键盘
        ch = _getch();//
        switch (ch) {
            case KEY_ESC: {//按下Esc,退出page
                if (correct_times != 0) {
                    addRecord(username,GAMEID_GUESSNUMBER,correct_times,sumDown(correct_times)+correct_times);
                }
                return FLAG_EXIT;
            }
            case KEY_BACK: {//按下退格,删除输入数字中的最后一位
                int len_input = (int) strlen(input_str);
                if (len_input >= 1)
                    input_str[len_input - 1] = '\0';
                break;
            }
            case KEY_ENTER: {
                input_num = atol(input_str);
                //清空输入的数字(input_num就够了)
                memset(input_str, '\0', sizeof(input_str));
                if (is_correct) {//正确后再按Enter
                    is_correct = 0;
                    correct_times++;
                    random_num = rand() % (101 + 100 * correct_times) + 1;
                    ltoa(random_num, random_str, 10);//随机数转字符串
                    try_times = 0;
                    try_time_max = TRYTIME_BASE_MAX + correct_times / 2 * 1;//每两关+1
                    buildFrame();//刷新一下,否则需要很麻烦地清空某些行
                } else if (input_num != 0) {//猜数字中Enter
                    if (input_num > random_num) {
                        setLineCenter(midline + 2, formatStr("%d is too big!", 1, input_num));
                        try_times++;
                    } else if (input_num < random_num) {
                        setLineCenter(midline + 2, formatStr("%d is too small!", 1, input_num));
                        try_times++;
                    } else {
                        addPoints(username,correct_times+1);
                        setLineCenter(midline + 1, "You are correct!!!");
                        setLineCenter(midline + 2, formatStr("+ %d Points", 1, correct_times + 1));
                        setLineCenter(midline + 3, "Press Enter to continue...");
                        is_correct = 1;
                    }
                    //错误达到上限9
                    if (try_times >= try_time_max) {
                        setLineCenter(midline + 1, "YOU FAILED!");
                        setLineCenter(midline + 2,
                                      formatStr("(Automatically restart after %ds)", 1, 1));
                        output();
                        Sleep(1000);
                        return FLAG_RESTART;
                    }
                }
                break;
            }
            case '0'...'9': {//输入数字
                char temp[2] = "";
                temp[0] = (char) ch;
                strcat(input_str, temp);
                break;
            }
        }
    }
    return FLAG_NOTHING;
};
