//
// Created by HJH201314 on 2021/12/14.
//

#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "global.h"

#define SYMBOL_BLOCK 'o'

//局部函数声明
static int getKeyPress();
static void initGame();
static void drawBlock();
static int goBlock();

//表示一个堆的信息
struct block {
    int x;//左上顶点x
    int y;//左上顶点y
    unsigned int shape;//用2字节16位(short其实够了)来表示每一个点
};

//全局变量
static int timetick = 0;
static int midline = H_MAX / 2;//中间行
static int is_started = 0;//是否已开始游戏
static int is_failed = 0;//是否已经输了
static int score = 0;
static struct block lastblock = {1,1,0b1111111111111111};
static struct block thisblock = {1,1,0b1111111111111111};

//该页面主程序
int pageTetris() {//返回0即返回mainPage
    SetConsoleTitleA("俄罗斯方块");
    initGame();
    initPage();
    setLineCenter(H_MAX/2,"Press Enter to Start...");
    srand( (unsigned int)time( NULL ));
    int key_result = 0;
    while(1) {
        key_result = getKeyPress();//获取返回值
        if(key_result != FLAG_NOTHING) return key_result;
        if(is_started && timetick % 20 == 0) {//后面一半是控制方块的速度
            setTips(formatStrD("Score:%d Timetick:%d", 2, score, timetick));//先输出提示再走蛇,否则有问题
            goBlock();
            drawBlock();
//            if (goBlock() != 0) {//撞墙的时候
//                addPoints(score);
//                setLineCenter(midline - 2, "GAME OVER!");
//                setLineCenter(midline, formatStrD("+ %d Points.", 1, score));
//                setLineCenter(midline + 2, "Press Enter to restart or Esc to exit.");
//                output();
//                is_started = 0;
//                is_failed = 1;
//            }
//            if (!is_failed) {
//                buildFrame();//buildFrame要在goSnake后面,不然获取不到上一状态
//            }
        }
        //thisblock.shape = rand() % 65535 + 1;
        //setLine(1,formatStrD("%d", 1, thisblock.shape));
        output();
        timetick++;
        Sleep(FREQ);
    }
}

//清除lastblock并画出thisblock
static void drawBlock() {
    int i,j;
    //清除lastblock的符号
    for(i = 0; i < 16; i++) {//i为从低到高(右到左)第i+1位
        j = 16 - i;//j为从高到低第j位,含0方便计算
        if ((lastblock.shape >> i) & 1)
            setPoint(lastblock.x + (j-1) / 4,lastblock.y + (j-1)%4,' ');
    }
    //画出thisblock的符号
    for(i = 0; i < 16; i++) {//i为从低到高(右到左)第i+1位
        j = 16 - i;//j为从高到低第j位,含0方便计算
        if ((thisblock.shape >> i) & 1)
            setPoint(thisblock.x + (j-1) / 4,thisblock.y + (j-1)%4,'o');
    }
}

//让块堆往下走
static int goBlock() {
    memcpy(&lastblock,&thisblock,sizeof(thisblock));//储存block信息到lastblock
    thisblock.x++;
    return 1;
}

//初始化
static void initGame() {//因为全局变量都会复用,必须要初始化
    //初始化时间
    timetick = 0;
    //还原状态
    is_started = 0;
    is_failed = 0;
}

//按键处理程序
static int getKeyPress(){
    int ch;
    if (_kbhit()) {//是否有按下键盘
        ch = _getch();//
        switch (ch) {
            case KEY_ESC://按下Esc,退出page
                return FLAG_EXIT;
            case KEY_ENTER: {
                if(!is_started) {
                    if (is_failed) return FLAG_RESTART;
                    is_started = !is_started;
                }
                break;
            }
            case KEY_RIGHT: {
                memcpy(&lastblock,&thisblock,sizeof(thisblock));
                if (thisblock.y <= W_MAX - 4) {
                    thisblock.y++;
                    drawBlock();
                }
                break;
            }
            case KEY_LEFT: {
                memcpy(&lastblock,&thisblock,sizeof(thisblock));
                if (thisblock.y > 1) {
                    thisblock.y--;
                    drawBlock();
                }
                break;
            }
            default:
                break;
        }
    }
    return FLAG_NOTHING;
};