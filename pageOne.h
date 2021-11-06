//
// Created by HJH201314 on 2021/11/5.
//

#ifndef BIGPROJECT_PAGEONE_H
#define BIGPROJECT_PAGEONE_H

void pageOne(){//Guess number
    buildFrame();
    int ch;
    char input[wmax+1] = "";//即将输入的数字
    long randomNum = rand()%101+1;//生成一个随机数
    char randomStr[20];//随机数转成的字符串
    ltoa(randomNum,randomStr,10);//转字符串
    long inputNum;//输入"数字"转成的长整数
    while(1){
        setLineCenter(hmax/2-2,"Please guess a number:");
        //setLineCenter(hmax/2-1, randomStr);
        if(_kbhit()) {//是否有按下键盘
            ch = _getch();//
            switch(ch){
                case KEY_ESC:
                    return;
                case KEY_BACK: {
                    int len_input = (int)strlen(input);
                    if(len_input >= 1)
                        input[len_input-1] = '\0';
                    break;
                }
                case KEY_ENTER: {
                    inputNum = atol(input);
                    if(inputNum != 0){
                        if(inputNum>randomNum){
                            setLineCenter(hmax/2+2,"Too big!");
                        } else if(inputNum<randomNum){
                            setLineCenter(hmax/2+2,"Too small!");
                        } else {
                            setLineCenter(hmax/2+2,"Correct!");
                        }

                    }
                    break;
                }
                case '0'...'9': {
                    char temp[2] = "";
                    temp[0] = (char) ch;
                    strcat(input, temp);
                    break;
                }
            }
        }
        setLineCenter(hmax/2,input);

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
