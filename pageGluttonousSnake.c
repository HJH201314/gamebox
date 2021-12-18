//
// Created by HJH201314 on 2021/11/16.
//

#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "global.h"

#define APPLE_COUNT 20
#define SYMBOL_SNAKE_HEAD 'O'
#define SYMBOL_SNAKE_BODY 'o'
#define SYMBOL_APPLE '*'

//局部函数声明
static int getKeyPress();
static void initGame();
static int goSnake();
static void drawSnake();
static void generateApple();

//表示蛇的每一个点的信息
struct partofsnake {
    int x;
    int y;
    int lastdir;//上一次的方向(1/2/3/4对应上左下右)
};

struct applesample {
    int x;
    int y;
    int points;//吃掉苹果可以获得的积分(长度)
};

//全局变量
static int timetick = 0;
static int midline = H_MAX / 2;//中间行
static int is_started = 0;//是否已开始游戏
static int is_failed = 0;//是否已经输了
static int dir = 0;//方向
static int is_turned = 0;//在方向改变后变为1,走蛇后变回0,用于防止快速按动导致的装上脖子
static struct partofsnake snake[H_MAX*W_MAX];
static struct applesample apples[APPLE_COUNT];
static int snake_length = 0;

extern char *username;

//该页面主程序
int pageGluttonousSnake() {//返回0即返回mainPage
    SetConsoleTitleA("贪吃蛇");
    initGame();
    initPage();
    setLineCenter(H_MAX/2,"Press Enter to Start...");
    int key_result = 0;
    while(1) {
        key_result = getKeyPress();//获取返回值
        if(key_result != FLAG_NOTHING) return key_result;
        if(is_started && timetick % ((dir%2+1)*4) == 0) {//后面一半是控制蛇的速度,但导致操作过快时撞到自己的脖子
            setTips(formatStr("Length:%d Timetick:%d", 2, snake_length, timetick));//先输出提示再走蛇,否则有问题
            if (goSnake() != 0) {//撞墙的时候
                addPoints(username,snake_length - 1);
                setLineCenterN_(midline - 2, "YOU FAILED !");
                setLineCenterN_(midline, formatStr("+ %d Points.", 1, snake_length - 1));
                setLineCenterN_(midline + 2, "Press Enter to restart or Esc to exit.");
                output();
                is_started = 0;
                is_failed = 1;
            } else is_turned = 0;
            if (!is_failed) {
                buildFrame();//buildFrame要在goSnake后面,不然获取不到上一状态
                generateApple();
                drawSnake();
            }
        }
        output();
        timetick++;
        Sleep(FREQ);
    }
}

//初始化
static void initGame() {//因为全局变量都会复用,必须要初始化
    //初始化时间
    timetick = 0;
    //还原snake
    memset(snake,0x00,sizeof(snake));
    snake_length = 0;
    //还原状态
    is_started = 0;
    is_failed = 0;
    is_turned = 0;
    //还原apple
    for(int i = 0; i < APPLE_COUNT; i++) {
        apples[i].x = apples[i].y = -1;
        apples[i].points = 0;
    }
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
                    snake[0].x = H_MAX / 2;
                    snake[0].y = W_MAX / 2;
                    dir = rand() % 4 + 1;
                    snake[0].lastdir = dir;
                    snake_length++;
                }
                break;
            }
            //方向控制要防止掉头
            case KEY_TOP: case 'w':
                if (dir != 3 && !is_turned) {dir = 1; is_turned = 1;} break;
            case KEY_LEFT: case 'a':
                if (dir != 4 && !is_turned) {dir = 2; is_turned = 1;} break;
            case KEY_BOTTOM: case 's':
                if (dir != 1 && !is_turned) {dir = 3; is_turned = 1;} break;
            case KEY_RIGHT: case 'd':
                if (dir != 2 && !is_turned) {dir = 4; is_turned = 1;} break;
            default:
                break;
        }
    }
    return FLAG_NOTHING;
};

//生成苹果(如果被吃了)
static void generateApple() {
    for(int i = 0; i < APPLE_COUNT; i++) {
        if(apples[i].x == -1) {
            int x = rand() % H_MAX + 1;
            int y = rand() % W_MAX + 1;
            while(getPoint(x,y) == SYMBOL_SNAKE_BODY || getPoint(x,y) == SYMBOL_SNAKE_HEAD) {//如果蛇在上面就要重复生成(这种方法不完备)
                x = rand() % H_MAX + 1;
                y = rand() % W_MAX + 1;
            }
            apples[i].x = x;
            apples[i].y = y;
            if(x == H_MAX || x == 1 || y == W_MAX || y == 1) {
                apples[i].points = 2;
            } else {
                apples[i].points = 1;
            }
        }
        setPoint(apples[i].x,apples[i].y,'*');
    }
}

//蛇前进程序
static int goSnake() {//返回0为正常,1为碰壁
    int tempdir = 0;
    for(int i = snake_length - 1; i >= 0; i--) {//遍历蛇
        tempdir = (i == 0) ? dir : snake[i-1].lastdir;//除了头以外,都取上一点的方向
        switch(tempdir) {
            case 1:snake[i].x--;break;
            case 2:snake[i].y--;break;
            case 3:snake[i].x++;break;
            case 4:snake[i].y++;break;
        }
        snake[i].lastdir = tempdir;
        if(snake[i].x < 1 || snake[i].x > H_MAX || snake[i].y < 1 || snake[i].y > W_MAX)
            return 1;
    }
    if(snake_length != 1 && getPoint(snake[0].x,snake[0].y) == SYMBOL_SNAKE_BODY) {//上一刻
        return 1;
    }
    if(getPoint(snake[0].x,snake[0].y) == SYMBOL_APPLE) {
        int i;
        //下方先取得i,嵌套的话缩进太多了
        for(i = 0; i < APPLE_COUNT; i++)
            if(snake[0].x == apples[i].x && snake[0].y == apples[i].y)
                break;
        if(snake[0].x == apples[i].x && snake[0].y == apples[i].y) {
            while(apples[i].points--) {
                switch (snake[snake_length - 1].lastdir) {//蛇尾的前进方向
                    case 1:snake[snake_length].x = snake[snake_length - 1].x + 1;snake[snake_length].y = snake[snake_length - 1].y;break;
                    case 2:snake[snake_length].y = snake[snake_length - 1].y + 1;snake[snake_length].x = snake[snake_length - 1].x;break;
                    case 3:snake[snake_length].x = snake[snake_length - 1].x - 1;snake[snake_length].y = snake[snake_length - 1].y;break;
                    case 4:snake[snake_length].y = snake[snake_length - 1].y - 1;snake[snake_length].x = snake[snake_length - 1].x;break;
                }
                snake[snake_length].lastdir=snake[snake_length-1].lastdir;//给蛇的最新的尾部设置前进方向
                snake_length++;
            }
            apples[i].x = apples[i].y = -1;
            apples[i].points = 0;
        }
    }
    return 0;
}

//蛇形绘制程序
static void drawSnake() {
    setPoint(snake[0].x,snake[0].y,SYMBOL_SNAKE_HEAD);
    for(int i = 1; i < snake_length; i++) {
        setPoint(snake[i].x,snake[i].y,SYMBOL_SNAKE_BODY);
    }
}
