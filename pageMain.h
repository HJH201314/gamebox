//
// Created by HJH201314 on 2021/11/3.
//

#ifndef BIGPROJECT_PAGEMAIN_H
#define BIGPROJECT_PAGEMAIN_H

#include "pageOne.h"

void pageMain(){
    int ch;
    while(1){
        //示例：获取按下的键
        if(_kbhit()) {//是否有按下键盘
            ch = _getch();//
            if (ch == KEY_ESC) goto back;
            else{
                switch(ch){
                    case '1':
                        pageOne();
                        break;
                    case '2':
                        break;
                }
            }
        }
        buildFrame();
        setLineCenter(2,"Press a number to start:");
        setLineCenter(4,"1:Guess number");
        output();
        //Sleep(FREQ);
    }
    back:
    return;
}

#endif //BIGPROJECT_PAGEMAIN_H
