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
    int points;//吃掉苹果可以获得的积分(长度)
};

//全局变量
static int midline = H_MAX / 2;//中间行
static int is_started = 0;//是否已开始游戏
static int is_failed = 0;//是否已经输了
static int dir = 0;//方向
static struct partofsnake snake[H_MAX*W_MAX];
static struct applesample apple = {-1,-1,0};
static int snake_length = 0;
static int dynamic_freq = FREQ;

//该页面主程序
int pageGluttonousSnake() {//返回0即返回mainPage
    SetConsoleTitleA("贪吃蛇");
    init();
    initPage();
    setLineCenter(H_MAX/2,"Press Enter to Start...");
    int key_result = 0;
    while(1) {
        key_result = getKeyPress();
        if(key_result != FLAG_NOTHING) return key_result;
        if(is_started) {
            setTips(formatStrD("Length:%d",1,snake_length));//先输出提示再走蛇,否则有问题
            if(goSnake() != 0) {//撞墙的时候
                addPoints(snake_length-1);
                setLineCenter(midline - 2, "YOU FAILED!");
                setLineCenter(midline, formatStrD("+ %d Points.",1,snake_length-1));
                setLineCenter(midline + 2,"Press Enter to restart or Esc to exit.");
                output();
                is_started = 0;
                is_failed = 1;
            }
            if (!is_failed) {
                buildFrame();//buildFrame要在goSnake后面,不然获取不到上一状态
                generateApple();
                drawSnake();
            }
        }
        output();
        if(dir % 2) dynamic_freq = 10*FREQ;
        else dynamic_freq = 5*FREQ;
        Sleep(dynamic_freq);
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
            case KEY_TOP:
                if (dir != 3)
                    dir = 1;
                break;
            case KEY_LEFT:
                if (dir != 4)
                    dir = 2;
                break;
            case KEY_BOTTOM:
                if (dir != 1)
                    dir = 3;
                break;
            case KEY_RIGHT:
                if (dir != 2)
                    dir = 4;
                break;
            default:
                break;
                //setLineCenter(H_MAX, formatStrD("%d",1,ch));
        }
    }
    return FLAG_NOTHING;
};

//初始化
static void init() {//因为全局变量都会复用,必须要初始化
    //还原snake
    memset(snake,0x00,sizeof(snake));
    snake_length = 0;
    //还原start状态
    is_started = 0;
    is_failed = 0;
    //还原apple
    apple.x = apple.y = -1;
    apple.points = 0;
}

//生成苹果(如果没有被吃)
static void generateApple() {
    if(apple.x == -1) {
        int x = rand() % H_MAX + 1;
        int y = rand() % W_MAX + 1;
        while(getPoint(x,y) == 'o' || getPoint(x,y) == 'O') {//如果蛇在上面就要重复生成(这种方法不完备)
            x = rand() % H_MAX + 1;
            y = rand() % W_MAX + 1;
        }
        apple.x = x;
        apple.y = y;
        if(x == H_MAX || x == 1 || y == W_MAX || y == 1) {
            apple.points = 2;
        } else {
            apple.points = 1;
        }
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
        while(apple.points--) {
            switch (snake[snake_length - 1].lastdir) {//蛇尾的前进方向
                case 1:snake[snake_length].x = snake[snake_length - 1].x + 1;snake[snake_length].y = snake[snake_length - 1].y;break;
                case 2:snake[snake_length].y = snake[snake_length - 1].y + 1;snake[snake_length].x = snake[snake_length - 1].x;break;
                case 3:snake[snake_length].x = snake[snake_length - 1].x - 1;snake[snake_length].y = snake[snake_length - 1].y;break;
                case 4:snake[snake_length].y = snake[snake_length - 1].y - 1;snake[snake_length].x = snake[snake_length - 1].x;break;
            }
            snake[snake_length].lastdir=snake[snake_length-1].lastdir;//给蛇的最新的尾部设置前进方向
            snake_length++;
        }
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
    setPoint(snake[0].x,snake[0].y,'O');
    for(int i = 1; i < snake_length; i++) {
        setPoint(snake[i].x,snake[i].y,'o');
    }
}

#endif //BIGPROJECT_PAGEGLUTTONOUSSNAKE_C
