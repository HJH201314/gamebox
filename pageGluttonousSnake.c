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
static void initSnake();
static int goSnake();
static void drawSnake();

//表示蛇的每一个点的信息
struct partofsnake {
    int x;
    int y;
    int lastdir;//上一次的方向(1/2/3/4对应上左下右)
};

//全局变量
static struct partofsnake snake[H_MAX*W_MAX];
static int snake_length = 0;

//该页面主程序
int pageGluttonousSnake() {//返回0即返回mainPage
    buildFrame();
    initSnake();
    setLineCenter(H_MAX/2,"Press Enter to Start...");
    int key_result = 0;
    while(1) {
        key_result = getKeyPress();
        if(key_result) return !key_result;
        if(is_started) {
            buildFrame();
            if(goSnake() != 0) return 0;
            drawSnake();
        }
        output();
        Sleep(24);
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
                    snake[0].x = rand() % H_MAX + 1;
                    snake[0].y = rand() % W_MAX + 1;
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
static void initSnake() {//因为全局变量都会复用,必须要初始化,这里只是初始化蛇
    //还原snake和lenght
    memset(snake,0x00,sizeof(snake));
    snake_length = 0;
    is_started = !is_started;
}

//蛇前进程序
static int goSnake() {//返回0为正常,1为碰壁
    int tempdir = 0;
    for(int i = snake_length - 1; i >= 0; i--) {
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
    return 0;
}

//蛇形绘制程序
static void drawSnake() {
    for(int i = 0; i < snake_length; i++) {
        setPoint(snake[i].x,snake[i].y,'o');
    }
}

#endif //BIGPROJECT_PAGEGLUTTONOUSSNAKE_C
