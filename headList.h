//
// Created by HJH201314 on 2021/11/16.
// 本头文件包含所有公用常量
//

#ifndef BIGPROJECT_HEADLIST_H
#define BIGPROJECT_HEADLIST_H

#define FREQ 10//窗口刷新率
#define HEIGHT 28//数组的一维长度(默认28)
#define H_MAX (HEIGHT-2)//最大行是h-2(1~H_MAX)
#define WIDTH 100//数组的二维长度(默认100)
#define W_MAX (WIDTH-3)//最大列是w-3(1~W_MAX)

#define KEY_BACK 8//Backspace的键值
#define KEY_ENTER 13//Enter的键值
#define KEY_ESC 27//Esc的键值
#define KEY_TOP 72//上
#define KEY_LEFT 75//左
#define KEY_BOTTOM 80//下
#define KEY_RIGHT 77//右

#define FLAG_NOTHING 0//啥也没事
#define FLAG_EXIT 1000//退出标识
#define FLAG_RESTART 2000//重开标识


#endif //BIGPROJECT_HEADLIST_H