//
// Created by HJH201314 on 2021/11/3.
//

#ifndef BIGPROJECT_PAGEMAIN_H
#define BIGPROJECT_PAGEMAIN_H

extern int pageGuessNumber();
extern int pageGluttonousSnake();

void pageMain(){
    int ch;
    while(1){
        //示例：获取按下的键
        if(_kbhit()) {//是否有按下键盘
            ch = _getch();//
            if (ch == KEY_ESC) goto back;
            else{
                switch(ch){
                    case '1': {
                        int result = 1;
                        while (result) {
                            result = pageGuessNumber();
                        }
                        break;
                    }
                    case '2': {
                        int result = 1;
                        while (result) {
                            result = pageGluttonousSnake();
                        }
                        break;
                    }
                }
            }
        }
        buildFrame();
        setLineRight(1, formatStrD("You have collect %d points",1,getPoints()));
        setLineCenter(2,"Press a number to start:");
        setLineCenter(4,"1:Guess number");
        setLineCenter(6,"2:Gluttonous snake");
        output();
        Sleep(FREQ);
    }
    back:
    return;
}

#endif //BIGPROJECT_PAGEMAIN_H
