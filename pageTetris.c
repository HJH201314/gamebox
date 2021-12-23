//
// Created by HJH201314 on 2021/12/14.
//

#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include "global.h"

#define BLOCK_SYMBOL 'o'//用于构成block的符号
#define BLOCK_COUNT 9//预定义的block种类数量
#define BLOCK_TOTAL_COUNT 6//包括当前block和未来blocks在内的所有blocks

extern int width_flex;
extern int height_flex;
extern char cWin[HEIGHT][WIDTH];

//表示一个堆的信息
struct block {
    int x;//左上顶点x
    int y;//左上顶点y
    unsigned int shape;//用2字节16位(short其实够了)来表示每一个点
};

typedef struct linkedBlock {
    int x;//左上顶点x
    int y;//左上顶点y
    unsigned int shape;//用2字节16位来表示每一个点
    struct linkedBlock *next;//指向下一个块
} blocklink;

//局部函数声明
static int getKeyPress();
static void initGame();
static void clearBlock();
static blocklink *initBlocks();
static blocklink *delBlock(blocklink *p, int pos);
static blocklink *insertBlock(blocklink *p, int pos, int x, int y, unsigned int shape);
static void drawNowBlock(blocklink *p);
static void drawPreBlocks(blocklink *p);
static int goBlock();
static void rotateBlock();
static void eliminateLine();
static int isMovableDown();
static int isMovableLeft();
static int isMovableRight();
static int hasBlock(unsigned int shape, int m, int n);
static int getBitPos(int m, int n);

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
        0b0100110001000000,//┤
        0b1100100010000000,//┌
        0b1100010001000000,//┐
        0b1100000000000000//oo
};//列表
static blocklink *blockhead;
static blocklink lastblock = {1,1,0b1111111111111111};

extern char username[129];

//该页面主程序
int pageTetris() {//返回0即返回mainPage
    SetConsoleTitleA("俄罗斯方块");
    initGame();
    initPage();
    setLineCenter(H_MAX / 2 - 2, "Tetris");
    setLineCenter(H_MAX / 2 - 1, "俄罗斯方块");
    setLineCenter(H_MAX / 2 + 1, "Press Enter to Start...");
    setLineCenter(H_MAX / 2 + 2, "按下回车键开始游戏~");
    int key_result = 0;
    while (1) {
        key_result = getKeyPress();//获取返回值
        if (key_result != FLAG_NOTHING && key_result != KEY_BOTTOM) {
            //释放链表
            for (int i = BLOCK_TOTAL_COUNT; i >= 1; i--) {
                delBlock(blockhead,i);
            }
            //复原动态宽度和高度
            free(blockhead);
            height_flex = H_MAX;
            width_flex = W_MAX;
            return key_result;
        }
        if (is_started && (timetick % 20 == 0 || key_result == KEY_BOTTOM)) {//后面一半是控制方块的速度
            setTips(formatStr("Score:%d Timetick:%d", 2, score, timetick));//先输出提示再走,否则有问题
            if (goBlock() == 0) {//goblock返回0表示该块到底了
                eliminateLine();
                //在节点BLOCK_TOTAL_COUNT插入新的块
                blockhead = insertBlock(blockhead,BLOCK_TOTAL_COUNT+1,0,width_flex/2,blocklist[rand() % BLOCK_COUNT]);
                //删除首个块
                blockhead = delBlock(blockhead,1);
                if (isMovableDown() == 0) {//新产生的也动不了了
                    is_started = 0;
                    is_failed = 1;
                    setLineLeft(height_flex+3," Gameover!");
                    setLineLeft(height_flex+5, formatStr(" +%d Points.", 1, score));
                    setLineLeft(height_flex+7," Press Enter to restart or Esc to exit.");
                    addPoints(username,score);
                    addRecord(username,GAMEID_TETRIS,score,score);
                }
                drawPreBlocks(blockhead);
            } else {
                drawNowBlock(blockhead);
            }
        }
        output();
        timetick++;
        Sleep(FREQ);
    }
}

//初始化并返回一个blocklink(链表的头)
blocklink *initBlocks() {
    blocklink *p = (blocklink *) malloc(sizeof(blocklink));//创建链表的头
    blocklink *temp = p;//声明一个指针指向头结点，用于遍历链表
    int i;
    //生成链表
    for (i = 0; i < BLOCK_TOTAL_COUNT; i++) {
        //创建节点并初始化
        blocklink *a = (blocklink *) malloc(sizeof(blocklink));
        a->x = 0;
        a->y = width_flex / 2;
        a->shape = blocklist[rand() % BLOCK_COUNT];
        a->next = NULL;
        //连接新节点和上一节点
        temp->next = a;
        temp = temp->next;
    }
    return p;
}

//删除p中的第pos个节点元素
static blocklink *delBlock(blocklink *p, int pos) {
    blocklink *temp = p;
    blocklink *del = NULL;
    int i;
    //遍历到被删除结点的上一个结点
    for (i = 1; i < pos; i++) {
        temp = temp->next;
    }
    del = temp->next;//记录被删除结点,以防丢失
    temp->next = temp->next->next;//删除某个结点的方法就是更改前一个结点的指针域
    free(del);//释放该结点,防止内存泄漏
    return p;
}

//在p的pos位置插入节点元素
static blocklink *insertBlock(blocklink *p, int pos, int x, int y, unsigned int shape) {
    blocklink *temp = p;//创建临时结点temp
    blocklink *new_block = NULL;
    int i = 0;
    //首先找到要插入位置的上一个结点
    for (i = 1; i < pos; i++) {
        if (temp == NULL) {
            //插入位置无效
            return p;
        }
        temp = temp->next;
    }
    //创建插入结点a
    new_block = (blocklink *) malloc(sizeof(blocklink));
    new_block->x = x;
    new_block->y = y;
    new_block->shape = shape;
    //向链表中插入结点
    new_block->next = temp->next;
    temp->next = new_block;
    return p;
}

//画出当前block
void drawNowBlock(blocklink *p) {
    blocklink *temp = p->next;//指向第一个
    int i,j;
    //清除lastblock的符号
    for (i = 0; i < 16; i++) {//i为从低到高(右到左)第i+1位
        j = 16 - i;//j为从高到低第j位,含0方便计算
        if ((lastblock.shape >> i) & 1)
            setPoint(lastblock.x + (j - 1) / 4, lastblock.y + (j - 1) % 4, ' ');
    }
    //画出第一个block的符号
    for (i = 0; i < 16; i++) {//i为从低到高(右到左)第i+1位
        j = 16 - i;//j为从高到低第j位,含0方便计算
        if ((temp->shape >> i) & 1)
        setPoint(temp->x + (j - 1) / 4, temp->y + (j - 1) % 4,BLOCK_SYMBOL);
    }
    output();
}

//画出后面预备的blocks
void drawPreBlocks(blocklink *p) {
    blocklink *temp = p->next;//指向第一个即当前
    int i, j;
    int c = 0;
    while (temp->next) {//存在下一个节点
        temp = temp->next;
        //画出thisblock的符号
        for (i = 0; i < 16; i++) {//i为从低到高(右到左)第i+1位
            j = 16 - i;//j为从高到低第j位,含0方便计算
            setLineFrom(2, formatStr("%d", 1, c + 1), (width_flex + 5 * c + 5));
            setPoint(3 + (j - 1) / 4, (width_flex + 5 * c + 5) + (j - 1) % 4,
                     ((temp->shape >> i) & 1) ? BLOCK_SYMBOL : ' ');
        }
        c++;
    }
    output();
}

//清除lastblock
static void clearBlock() {
    int i, j;
    //清除lastblock的符号
    for (i = 0; i < 16; i++) {//i为从低到高(右到左)第i+1位
        j = 16 - i;//j为从高到低第j位,含0方便计算
        if ((lastblock.shape >> i) & 1)
            setPoint(lastblock.x + (j - 1) / 4, lastblock.y + (j - 1) % 4, ' ');
    }
}

//让块堆往下走
static int goBlock() {
    if (isMovableDown()) {
        memcpy(&lastblock, blockhead->next, sizeof(blocklink));//储存thisblock信息到lastblock
        blockhead->next->x++;
        return 1;
    } else {
        return 0;
    }
}

//判断是否能往下走
static int isMovableDown() {
    int i, j;
    //判断是否还能下
    for (j = 1; j <= 4; j++) {//从第一列开始,往右边走
        for (i = 5; i >= 2; i--) {//从最后一行+1开始,往上走(第一行就不用了)
            //如果下面一个点是0上面一个点是1,就要判断再往下一个点是不是非空的
            if (!hasBlock(blockhead->next->shape, i, j) && hasBlock(blockhead->next->shape, i - 1, j)) {
                if (getPoint(blockhead->next->x + i - 1, blockhead->next->y + j - 1) != ' ') {
                    return 0;
                }
                break;//只需要判断到最下面的一个
            }
        }
    }
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
            if (hasBlock(blockhead->next->shape, i, j)) {
                if (i > m) m = i;
                if (j > n) n = j;
            }
        }
    }
    //setTips(formatStr("%d %d",2,m,n));
    //构造新shape
    unsigned int newshape = 0b0000000000000000;
    unsigned int oldshape = blockhead->next->shape;
    for (i = m; i >= 1; i--) {
        for (j = 1; j <= n; j++) {
            if (hasBlock(blockhead->next->shape, i, j))
                newshape = setBit(newshape, getBitPos(j, m - i + 1));
        }
    }
    //设置thisblock的shape
    blockhead->next->shape = newshape;
    if (!isMovableDown()) {//如果发现因为旋转动不了了就回滚
        blockhead->next->shape = oldshape;
    }
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
            if (!hasBlock(blockhead->next->shape, i, j) && hasBlock(blockhead->next->shape, i, j - 1)) {
                if (getPoint(blockhead->next->x + i - 1, blockhead->next->y + j - 1) != ' ') {
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
            if (!hasBlock(blockhead->next->shape, i, j) && hasBlock(blockhead->next->shape, i, j + 1)) {
                if (getPoint(blockhead->next->x + i - 1, blockhead->next->y + j - 1) != ' ') {
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
    width_flex = 12;
    height_flex = 20;
    //初始化当前块和将来块
    blockhead = initBlocks();
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
                    drawNowBlock(blockhead);
                    drawPreBlocks(blockhead);
                }
                break;
            }
            case KEY_BOTTOM:
                return KEY_BOTTOM;
            case KEY_RIGHT: {
                if (is_started && !is_failed) {
                    //判断是否撞到已有的块或墙
                    if (!isMovableRight())
                        break;
                    memcpy(&lastblock, blockhead->next, sizeof(blocklink));
                    blockhead->next->y++;
                    drawNowBlock(blockhead);
                }
                break;
            }
            case KEY_LEFT: {
                if (is_started && !is_failed) {
                    if (!isMovableLeft())
                        break;
                    memcpy(&lastblock, blockhead->next, sizeof(blocklink));
                    blockhead->next->y--;
                    drawNowBlock(blockhead);
                }
                break;
            }
            case KEY_TOP:
            case 'r': {
                if (is_started && !is_failed) {
                    memcpy(&lastblock, blockhead->next, sizeof(blocklink));
                    clearBlock();//要先清除否则可能无法旋转
                    rotateBlock();//处理thisblock的shape
                    drawNowBlock(blockhead);
                }
                break;
            }
            default:
                break;
        }
    }
    return FLAG_NOTHING;
};