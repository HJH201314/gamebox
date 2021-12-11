//
// Created by HJH201314 on 2021/11/3.
//

#ifndef BIGPROJECT_PAGEMAIN_C
#define BIGPROJECT_PAGEMAIN_C

#include <windows.h>
#include <conio.h>
#include "global.h"

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
                }
            }
        }
        buildFrame();
        setLineRight(1, formatStrD("You have collect %d points",1,getPoints()));
        setLineCenter(2,"Press a number to start:");
        setLineCenter(4,"1:Guess number(猜数字)");
        setLineCenter(6,"2:Gluttonous snake(贪吃蛇)");
        output();
        Sleep(FREQ);
    }
    back:
    return;
}

#endif //BIGPROJECT_PAGEMAIN_C
