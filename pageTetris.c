//
// Created by HJH201314 on 2021/12/14.
//

#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include "global.h"

#define SYMBOL_BLOCK 'o'

//局部函数声明
static int getKeyPress();
static void initGame();
static void drawBlock();
static int goBlock();
static int hasBlock(unsigned int bin, int m, int n);

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
static struct block lastblock = {1,1,0b1111111111111111};//记录上一个块以便清除
static struct block thisblock = {1,1,0b1111111111110000};//当前操作的块
static struct block nextblock = {1,1,0b1111111111110000};//下一个块

//该页面主程序
int pageTetris() {//返回0即返回mainPage
    SetConsoleTitleA("俄罗斯方块");
    initGame();
    initPage();
    setLineCenter(H_MAX/2,"Press Enter to Start...");
    int key_result = 0;
    while(1) {
        key_result = getKeyPress();//获取返回值
        if(key_result != FLAG_NOTHING && key_result != KEY_BOTTOM) return key_result;
        if(is_started && (timetick % 20 == 0 || key_result == KEY_BOTTOM)) {//后面一半是控制方块的速度
            //setTips(formatStrD("Score:%d Timetick:%d", 2, score, timetick));//先输出提示再走蛇,否则有问题
            if (goBlock() == 0) {//goblock返回0表示该块到底了
                memcpy(&thisblock,&nextblock,sizeof(nextblock));
            } else {
                drawBlock();
            }
        }
        output();
        timetick++;
        Sleep(FREQ);
    }
}

//清除lastblock并且画出thisblock
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
    int i,j;
    //判断是否还能下
    for (j = 1; j <= 4; j++) {//从第一列开始,往右边走
        for (i = 5; i >= 2; i--) {//从最后一行+1开始,往上走(第一行就不用了)
            //如果下面一个点是0上面一个点是1,就要判断再往下一个点是不是非空的
            if (!hasBlock(thisblock.shape,i,j) && hasBlock(thisblock.shape,i-1,j)) {
                if (getPoint(thisblock.x+i-1,thisblock.y+j-1) != ' ') {
                    return 0;
                }
                break;//只需要判断到最下面的一个
            }
        }
    }
    memcpy(&lastblock,&thisblock,sizeof(thisblock));//储存thisblock信息到lastblock
    thisblock.x++;
    return 1;
}

//判断shape(4*4)的m行n列是否为1
static int hasBlock(unsigned int bin, int m, int n) {
    if (m >= 0 && m <=4 && n >= 0 && n <=4)
        return getBit(bin,21-4*m-n);//k = 16-(4(m-1)+(n-1))
    else
        return 0;
}

//判断是否能右移
static int isMovableRight() {
    int i,j;
    for (i = 4; i >= 1; i--) {//从最后一行开始,往上走
        for (j = 5; j >= 2; j--) {//从最后一列+1开始,往左走(第一列就不用了)
            //如果右边一个点是0左边一个点是1,就要判断再往右一个点是不是非空的
            if (!hasBlock(thisblock.shape,i,j) && hasBlock(thisblock.shape,i,j-1)) {
                if (getPoint(thisblock.x+i-1,thisblock.y+j-1) != ' ') {
                    return 0;
                }
                break;//只需要判断到最右边的一个
            }
        }
    }
    return 1;
}

//判断是否能左移
static int isMovableLeft() {
    int i,j;
    for (i = 4; i >= 1; i--) {//从最后一行开始,往上走
        for (j = 0; j <= 3; j++) {//从第一列-1开始,往右走(最后一列就不用了)
            //如果左边一个点是0右边一个点是1,就要判断再往右一个点是不是非空的
            if (!hasBlock(thisblock.shape,i,j) && hasBlock(thisblock.shape,i,j+1)) {
                if (getPoint(thisblock.x+i-1,thisblock.y+j-1) != ' ') {
                    return 0;
                }
                break;//只需要判断到最左边的一个
            }
        }
    }
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
                    buildFrame();//清除掉提示语
                    drawBlock();
                }
                break;
            }
            case KEY_BOTTOM:
                return KEY_BOTTOM;
            case KEY_RIGHT: {
                if (is_started) {
                    //判断是否撞到已有的块
                    if (!isMovableRight())
                        break;
                    //判断是否撞墙
                    if (thisblock.y > W_MAX - 4)
                        break;
                    memcpy(&lastblock,&thisblock,sizeof(thisblock));
                    thisblock.y++;
                    drawBlock();
                }
                break;
            }
            case KEY_LEFT: {
                if (is_started) {
                    if (!isMovableLeft())
                        break;
                    if (thisblock.y <= 1)
                        break;
                    memcpy(&lastblock,&thisblock,sizeof(thisblock));
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