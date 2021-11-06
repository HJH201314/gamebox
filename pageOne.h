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
    long input_num;//输入"数字"转成的长整数
    int try_times = 0;
    int try_time_max = TRYTIME_BASE_MAX;
    int correct_times = 0;
    char is_correct = 0;
    long random_num = rand() % (101+50*correct_times) + 1;//生成一个随机数[1~100(+correct*50)]
    char random_str[20];//随机数转成的字符串
    ltoa(random_num, random_str, 10);//转字符串
    while(1){
        setLineCenter(midline - 4,formatStrD("Level %d (1~%d)",2,correct_times+1,100+50*correct_times));
        setLineCenter(midline - 2, "Please guess a number (and press Enter):");
        //setLineCenter(hmax/2-1, random_str);
        if(_kbhit()) {//是否有按下键盘
            ch = _getch();//
            switch(ch){
                case KEY_ESC://按下Esc,退出page
                    return;
                case KEY_BACK: {//按下退格,删除输入数字中的最后一位
                    int len_input = (int)strlen(input_str);
                    if(len_input >= 1)
                        input_str[len_input - 1] = '\0';
                    break;
                }
                case KEY_ENTER: {
                    input_num = atol(input_str);
                    //清空输入的数字(input_num就够了)
                    memset(input_str,'\0',sizeof(input_str));
                    if(is_correct){//正确后再按Enter
                        is_correct = 0;
                        correct_times++;
                        random_num = rand() % (101+50*correct_times) + 1;
                        ltoa(random_num, random_str, 10);//随机数转字符串
                        try_times = 0;
                        try_time_max = TRYTIME_BASE_MAX + correct_times * 5;//每一关+5
                        buildFrame();//刷新一下
                    } else if(input_num != 0) {//猜数字中Enter
                        if (input_num > random_num) {
                            setLineCenter(midline + 2, formatStrD("%d is too big!",1, input_num));
                            try_times++;
                        } else if (input_num < random_num) {
                            setLineCenter(midline + 2, formatStrD("%d is too small!",1, input_num));
                            try_times++;
                        } else {
                            setLineCenter(midline + 2, "You are correct!!!");
                            setLineCenter(midline + 3, "Press Enter to continue...");
                            is_correct = 1;
                        }
                        //错误达到上限
                        if (try_times >= try_time_max) {
                            setLineCenter(midline + 1, "YOU FAILED!");
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
        setLineRight(1, formatStrD("You have tried %d times(%d max)",2,try_times,try_time_max));
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
