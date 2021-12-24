//
// Created by HJH201314 on 2021/11/3.
//

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include "global.h"

extern char username[129];
extern int freq;

void pageMain(){
    int ch = 0;
    while(1){
        //示例：获取按下的键
        //if(_kbhit()) {//是否有按下键盘 !!!有BUG,如果输入中文标点会导致卡死
//            ch = _getch();//
//            setTips(formatStr("key:%c",1,ch));
//            output();
// 获取ch移动到后面
        if (ch == KEY_ESC) goto back;
        else{
            switch(ch){
                case '1': {
                    int result = FLAG_RESTART;
                    while (result == FLAG_RESTART) {//如果获得了重启的返回值,那么重新打开页面,也适用于首次打开
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
                case 'u': {
                    pageUser();
                    initPage();
                    break;
                }
                case 's': {
                    pageShop();
                    initPage();
                    break;
                }
            }
        }
        //}
        SetConsoleTitleA("小游戏合集");
        buildFrame();
        setLineLeftN_(1, formatStr("Hello,%s!",1,username));
        setLineRightN_(1, formatStr("You have collected %d points", 1, getPoints(username)));
        setLineCenter(3,"Press a number to start:");
        setLineCenter(4,"按下相应的数字开始游戏:");
        setLineCenter(6,"(1)Guess number");
        setLineCenter(7,"(1)猜数字");
        setLineCenter(9,"(2)Gluttonous snake");
        setLineCenter(10,"(2)贪吃蛇");
        setLineCenter(12,"(3)Tetris");
        setLineCenter(13,"(3)俄罗斯方块");
        setLineLeftN_(H_MAX,"(u)进入用户中心");
        setLineRightN_(H_MAX,"(i)进入游戏商店");
        output();
        ch = _getch();//
        setTips(formatStr("d:%d c:%c",2,(int)ch,ch));
        Sleep(freq);
    }
    back:
    return;
}
