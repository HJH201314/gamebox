//
// Created by HJH201314 on 2021/12/14.
//

#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include "global.h"

#define BLOCK_SYMBOL 'o'
#define BLOCK_COUNT 7

extern int width_flex;
extern int height_flex;
extern char cWin[HEIGHT][WIDTH];

//局部函数声明
static int getKeyPress();

static void initGame();

static void drawBlock();

static int goBlock();

static void rotateBlock();

static void eliminateLine();

static int hasBlock(unsigned int shape, int m, int n);

static int getBitPos(int m, int n);

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
static unsigned int blocklist[BLOCK_COUNT] = {
        0b1100110000000000,//田
        0b1100011000000000,//z
        0b0110110000000000,//反z
        0b1000100010001000,//|
        0b1000110010000000,//├
        0b1100100010000000,//┌
        0b1100000000000000//test
};//列表
static struct block lastblock = {1, 1, 0b1111111111111111};//记录上一个块以便清除
static struct block thisblock = {1, 1, 0b1100011000000000};//当前操作的块
static struct block nextblock = {0, 1, 0b1100011000000000};//下一个块

//该页面主程序
int pageTetris() {//返回0即返回mainPage
    SetConsoleTitleA("俄罗斯方块");
    initGame();
    initPage();
    setLineCenter(H_MAX / 2, "Press Enter to Start...");
    int key_result = 0;
    while (1) {
        key_result = getKeyPress();//获取返回值
        if (key_result != FLAG_NOTHING && key_result != KEY_BOTTOM) return key_result;
        if (is_started && (timetick % 20 == 0 || key_result == KEY_BOTTOM)) {//后面一半是控制方块的速度
            //setTips(formatStrD("Score:%d Timetick:%d", 2, score, timetick));//先输出提示再走,否则有问题
            if (goBlock() == 0) {//goblock返回0表示该块到底了
                eliminateLine();
                memcpy(&thisblock, &nextblock, sizeof(nextblock));
                nextblock.shape = blocklist[rand() % BLOCK_COUNT];
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
    int i, j;
    //清除lastblock的符号
    for (i = 0; i < 16; i++) {//i为从低到高(右到左)第i+1位
        j = 16 - i;//j为从高到低第j位,含0方便计算
        if ((lastblock.shape >> i) & 1)
            setPoint(lastblock.x + (j - 1) / 4, lastblock.y + (j - 1) % 4, ' ');
    }
    //画出thisblock的符号
    for (i = 0; i < 16; i++) {//i为从低到高(右到左)第i+1位
        j = 16 - i;//j为从高到低第j位,含0方便计算
        if ((thisblock.shape >> i) & 1)
            setPoint(thisblock.x + (j - 1) / 4, thisblock.y + (j - 1) % 4, 'o');
    }
}

//让块堆往下走
static int goBlock() {
    int i, j;
    //判断是否还能下
    for (j = 1; j <= 4; j++) {//从第一列开始,往右边走
        for (i = 5; i >= 2; i--) {//从最后一行+1开始,往上走(第一行就不用了)
            //如果下面一个点是0上面一个点是1,就要判断再往下一个点是不是非空的
            if (!hasBlock(thisblock.shape, i, j) && hasBlock(thisblock.shape, i - 1, j)) {
                if (getPoint(thisblock.x + i - 1, thisblock.y + j - 1) != ' ') {
                    return 0;
                }
                break;//只需要判断到最下面的一个
            }
        }
    }
    memcpy(&lastblock, &thisblock, sizeof(thisblock));//储存thisblock信息到lastblock
    thisblock.x++;
    return 1;
}

//消除整行
static void eliminateLine() {
    int i, j, flag;
    do {
        for (i = height_flex; i >= 1; i--) {
            flag = i;
            for (j = 1; j <= width_flex; j++) {
                if (getPoint(i, j) == ' ')
                    flag = 0;
            }
            if (flag) break;
        }
        if (flag) {//如果整行都是
            score += width_flex;
            for (i = flag; i > 1; i--) {//将上面的往下压
                memmove(cWin[i] + 1, cWin[i - 1] + 1, width_flex);
            }
        }
    } while (flag);//如果flag了那就继续看看还有没有其它行
}

//向右旋转块
static void rotateBlock() {
    int m = 0, n = 0;//有效行数m和有效列数n
    int i, j;
    //计算有效行数m和有效列数n
    for (i = 1; i <= 4; i++) {
        for (j = 1; j <= 4; j++) {
            if (hasBlock(thisblock.shape, i, j)) {
                if (i > m) m = i;
                if (j > n) n = j;
            }
        }
    }
    setTips(formatStrD("%d %d",2,m,n));
    //构造新shape
    unsigned int newshape = 0b0000000000000000;
    for (i = m; i >= 1; i--) {
        for (j = 1; j <= n; j++) {
            if (hasBlock(thisblock.shape, i, j))
                newshape = setBit(newshape, getBitPos(j,m-i+1));
        }
    }
    //设置thisblock的shape
    thisblock.shape = newshape;
}

//判断shape(4*4)的m行n列是否为1
static int hasBlock(unsigned int shape, int m, int n) {
    if (m >= 1 && m <= 4 && n >= 1 && n <= 4)
        return getBit(shape, 21 - 4 * m - n);//k = 16-(4(m-1)+(n-1))
    else
        return 0;
}

//传入行列,返回位
static int getBitPos(int m, int n) {
    return 21 - 4 * m - n;//k = 16-(4(m-1)+(n-1))
}

//判断是否能右移
static int isMovableRight() {
    int i, j;
    for (i = 4; i >= 1; i--) {//从最后一行开始,往上走
        for (j = 5; j >= 2; j--) {//从最后一列+1开始,往左走(第一列就不用了)
            //如果右边一个点是0左边一个点是1,就要判断再往右一个点是不是非空的
            if (!hasBlock(thisblock.shape, i, j) && hasBlock(thisblock.shape, i, j - 1)) {
                if (getPoint(thisblock.x + i - 1, thisblock.y + j - 1) != ' ') {
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
    int i, j;
    for (i = 4; i >= 1; i--) {//从最后一行开始,往上走
        for (j = 0; j <= 3; j++) {//从第一列-1开始,往右走(最后一列就不用了)
            //如果左边一个点是0右边一个点是1,就要判断再往右一个点是不是非空的
            if (!hasBlock(thisblock.shape, i, j) && hasBlock(thisblock.shape, i, j + 1)) {
                if (getPoint(thisblock.x + i - 1, thisblock.y + j - 1) != ' ') {
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
    //初始化中间分隔
    //width_flex = W_MAX / 3;
    width_flex = 10;
    height_flex = 18;
    //初始化当前块和将来块
    thisblock.shape = blocklist[rand() % BLOCK_COUNT];
    nextblock.shape = blocklist[rand() % BLOCK_COUNT];
    //thisblock.shape = blocklist[0];
    //nextblock.shape = blocklist[0];
}

//按键处理程序
static int getKeyPress() {
    int ch;
    if (_kbhit()) {//是否有按下键盘
        ch = _getch();//
        switch (ch) {
            case KEY_ESC://按下Esc,退出page
                return FLAG_EXIT;
            case KEY_ENTER: {
                if (!is_started) {
                    if (is_failed) return FLAG_RESTART;
                    is_started = !is_started;
                    buildFrame();//清除掉提示语
                    buildFlexFrame();//设置边框
                    drawBlock();
                }
                break;
            }
            case KEY_BOTTOM:
                return KEY_BOTTOM;
            case KEY_RIGHT: {
                if (is_started) {
                    //判断是否撞到已有的块或墙
                    if (!isMovableRight())
                        break;
                    memcpy(&lastblock, &thisblock, sizeof(thisblock));
                    thisblock.y++;
                    drawBlock();
                }
                break;
            }
            case KEY_LEFT: {
                if (is_started) {
                    if (!isMovableLeft())
                        break;
                    memcpy(&lastblock, &thisblock, sizeof(thisblock));
                    thisblock.y--;
                    drawBlock();
                }
                break;
            }
            case KEY_TOP: case 'r': {
                memcpy(&lastblock, &thisblock, sizeof(thisblock));
                rotateBlock();//处理thisblock的shape
                drawBlock();
                break;
            }
            default:
                break;
        }
    }
    return FLAG_NOTHING;
};