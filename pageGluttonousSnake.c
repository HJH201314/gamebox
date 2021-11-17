//
// Created by HJH201314 on 2021/11/16.
//

#ifndef BIGPROJECT_PAGEGLUTTONOUSSNAKE_C
#define BIGPROJECT_PAGEGLUTTONOUSSNAKE_C

#include <stdlib.h>
#include <windows.h>
#include "conio.h"
#include "headList.h"
#include "functionList.h"

static int is_started = 0;
static int dir = 0;

//局部函数声明
static int getKeyPress();
static void init();
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
    int points;
};

//全局变量
static struct partofsnake snake[H_MAX*W_MAX];
static struct applesample apple = {-1,-1,0};
static int snake_length = 0;

//该页面主程序
int pageGluttonousSnake() {//返回0即返回mainPage
    init();
    buildFrame();
    setLineCenter(H_MAX/2,"Press Enter to Start...");
    int key_result = 0;
    while(1) {
        key_result = getKeyPress();
        if(key_result) return !key_result;
        if(is_started) {
            if(goSnake() != 0) return 0;//撞墙
            buildFrame();//buildFrame要在goSnake后面,不然获取不到上一状态
            generateApple();
            drawSnake();
        }
        output();
        Sleep(48);
    }
    return 0;
}

//按键处理程序
static int getKeyPress(){
    int ch;
    if (_kbhit()) {//是否有按下键盘
        ch = _getch();//
        switch (ch) {
            case KEY_ESC://按下Esc,退出page
                return 1;
            case KEY_ENTER: {
                if(!is_started) {
                    is_started = !is_started;
                    snake[0].x = H_MAX / 2;
                    snake[0].y = W_MAX / 2;
                    dir = rand() % 4 + 1;
                    snake[0].lastdir = dir;
                    snake_length++;
                }
                break;
            }
            case KEY_TOP: dir = 1;break;
            case KEY_LEFT: dir = 2;break;
            case KEY_BOTTOM: dir = 3;break;
            case KEY_RIGHT: dir = 4;break;
            default:
                break;
                //setLineCenter(H_MAX, formatStrD("%d",1,ch));
        }
    }
    return 0;
};

//初始化
static void init() {//因为全局变量都会复用,必须要初始化
    //还原snake
    memset(snake,0x00,sizeof(snake));
    snake_length = 0;
    //还原start状态
    is_started = 0;
    //还原apple
    apple.x = apple.y = -1;
    apple.points = 0;
}

//生成苹果(如果没有被吃)
static void generateApple() {
    if(apple.x == -1) {
        int x = rand() % H_MAX + 1;
        int y = rand() % W_MAX + 1;
        while(getPoint(x,y) == 'o') {//如果蛇在上面就要重复生成(这种方法不完备)
            x = rand() % H_MAX + 1;
            y = rand() % W_MAX + 1;
        }
        apple.x = x;
        apple.y = y;
        apple.points = 1;
    }
    setPoint(apple.x,apple.y,'*');
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
    if(snake[0].x == apple.x && snake[0].y == apple.y) {
        switch (snake[snake_length - 1].lastdir) {//上一个点
            case 1:snake[snake_length].x = snake[snake_length - 1].x + 1;snake[snake_length].y = snake[snake_length - 1].y;break;
            case 2:snake[snake_length].y = snake[snake_length - 1].y + 1;snake[snake_length].x = snake[snake_length - 1].x;break;
            case 3:snake[snake_length].x = snake[snake_length - 1].x - 1;snake[snake_length].y = snake[snake_length - 1].y;break;
            case 4:snake[snake_length].y = snake[snake_length - 1].y - 1;snake[snake_length].x = snake[snake_length - 1].x;break;
        }
        snake_length++;
        apple.x = apple.y = -1;
        apple.points = 0;
    }
    if(snake_length != 1 && getPoint(snake[0].x,snake[0].y) == 'o') {//上一刻
        return 1;
    }
    return 0;
}

//蛇形绘制程序
static void drawSnake() {
    for(int i = 0; i < snake_length; i++) {
        setPoint(snake[i].x,snake[i].y,'o');
    }
}

#endif //BIGPROJECT_PAGEGLUTTONOUSSNAKE_C
