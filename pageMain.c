//
// Created by HJH201314 on 2021/11/3.
//

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include "global.h"

extern char *username;

void pageMain(){
    int ch;
    while(1){
        SetConsoleTitleA("小游戏合集");
        //示例：获取按下的键
        if(_kbhit()) {//是否有按下键盘
            ch = _getch();//
            if (ch == KEY_ESC) goto back;
            else{
                switch(ch){
                    case '1': {
                        int result = FLAG_RESTART;
                        while (result == FLAG_RESTART) {
                            result = pageGuessNumber();
                        }
                        initPage();
                        break;
                    }
                    case '2': {
                        int result = FLAG_RESTART;
                        while (result == FLAG_RESTART) {
                            result = pageGluttonousSnake();
                        }
                        initPage();
                        break;
                    }
                    case '3': {
                        int result = FLAG_RESTART;
                        while (result == FLAG_RESTART) {
                            result = pageTetris();
                        }
                        initPage();
                        break;
                    }
                }
            }
        }
        buildFrame();
        setLineLeftN_(1, formatStr("Hello,%s!",1,username));
        setLineRightN_(1, formatStr("You have collected %d points", 1, getPoints(username)));
        setLineCenter(3,"Press a number to start:");
        setLineCenter(4,"按下相应的数字开始游戏:");
        setLineCenter(6,"1:Guess number");
        setLineCenter(7,"1:猜数字");
        setLineCenter(9,"2:Gluttonous snake");
        setLineCenter(10,"2:贪吃蛇");
        setLineCenter(12,"3:Tetris");
        setLineCenter(13,"3:俄罗斯方块");
        output();
        Sleep(FREQ);
    }
    back:
    return;
}
