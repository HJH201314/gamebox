//
// Created by HJH201314 on 2021/11/5.
//

#ifndef BIGPROJECT_PAGEONE_H
#define BIGPROJECT_PAGEONE_H

#define TRYTIME_BASE_MAX 10//第一关的最大值

void pageOne(){//Guess number
    buildFrame();
    int ch;
    int midline = hmax / 2;//中间行
    char input_str[wmax + 1] = "";//即将输入的数字
    long random_num = rand() % 101 + 1;//生成一个随机数
    char random_str[20];//随机数转成的字符串
    ltoa(random_num, random_str, 10);//转字符串
    long input_num;//输入"数字"转成的长整数
    int try_times = 0;
    while(1){
        setLineCenter(midline - 2, "Please guess a number (and press Enter):");
        //setLineCenter(hmax/2-1, random_str);
        if(_kbhit()) {//是否有按下键盘
            ch = _getch();//
            switch(ch){
                case KEY_ESC:
                    return;
                case KEY_BACK: {
                    int len_input = (int)strlen(input_str);
                    if(len_input >= 1)
                        input_str[len_input - 1] = '\0';
                    break;
                }
                case KEY_ENTER: {
                    input_num = atol(input_str);
                    if(input_num != 0){
                        if(input_num > random_num){
                            setLineCenter(midline+2, formatStrD("%d is too big!",1,input_num));
                            try_times++;
                        } else if(input_num < random_num){
                            setLineCenter(midline+2,formatStrD("%d is too small!",1,input_num));
                            try_times++;
                        } else {
                            setLineCenter(midline+2,"You are correct!!!");
                            setLineCenter(midline+3,"Press Enter to continue...");
                        }
                        //清空输入的数字
                        memset(input_str,'\0',sizeof(input_str));
                        //错误达到上限
                        if(try_times >= TRYTIME_BASE_MAX) {
                            setLineCenter(midline+1, "YOU FAILED!");
                        }
                    }
                    break;
                }
                case '0'...'9': {//输入数字
                    char temp[2] = "";
                    temp[0] = (char) ch;
                    strcat(input_str, temp);
                    break;
                }
            }
        }
        setLineRight(1, formatStrD("You have tried %d times",1,try_times));
        setLineCenter(midline, input_str);

        output();
        Sleep(FREQ);
    }
}

//long str2num(char * str){
//    int length = (int) strlen(str);
//    long result = 0;
//    for(int i = 0 ;i <= length-1;i++) {
//        result += (*(str+i)-48) * (int)pow(10,length-i-1);
//    }
//    return result;
//}

#endif //BIGPROJECT_PAGEONE_H
