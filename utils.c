//
// Created by HJH201314 on 2021/11/4.
//

#ifndef BIGPROJECT_UTILS_C
#define BIGPROJECT_UTILS_C

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include "headList.h"
#include "global.h"

void initStrBlank(char *str, int size) {//初始化str为空格
    //memset设置内存
    memset(str, ' ', size);
}

void clearStr(char *str) {//将str前面不为\0的元素设置为空格
    //memset设置内存
    int len = (int) strlen(str);
    memset(str, ' ', len);
}

void setStrFrom(char *str, int from, char *ch) {//从from(>0)开始设置str的值，注意str可设置的范围不为\0即已经初始化
    int len_ch = (int) strlen(ch);
    for (int i = from - 1; i < from - 1 + len_ch; i++) {
        if (*(str + i) != '\0') *(str + i) = ch[i - (from - 1)];
    }
}

void setStrCenter(char *str, char *ch) {//居中在str中放置ch，注意str可设置的范围不为\0即已经初始化
    int len_ch = (int) strlen(ch);
    int start = (W_MAX - len_ch) / 2;//start为数组下标开始处
    if (len_ch <= W_MAX) {
        for (int i = start; i < start + len_ch; i++) {
            if (*(str + i) != '\0') *(str + i) = ch[i - (start)];
        }
    }
}

void setStrRight(char *str, char *ch) {//居右在str中放置ch，注意str可设置的范围不为\0即已经初始化
    int len_ch = (int) strlen(ch);
    int start = W_MAX - len_ch;//start为数组下标开始处
    if (len_ch <= W_MAX) {
        for (int i = start; i < start + len_ch; i++) {
            if (*(str + i) != '\0') *(str + i) = ch[i - (start)];
        }
    }
}

void resetStrCenter(char *str, char *ch) {//清空原有文字并居中在str中放置ch，注意str可设置的范围不为\0即已经初始化
    clearStr(str);
    int len_ch = (int) strlen(ch);
    int start = (W_MAX - len_ch) / 2;//start为数组下标开始处
    if (len_ch <= W_MAX) {
        for (int i = start; i < start + len_ch; i++) {
            if (*(str + i) != '\0') *(str + i) = ch[i - (start)];
        }
    }
}

void resetStrRight(char *str, char *ch) {//清空原有文字并居右在str中放置ch，注意str可设置的范围不为\0即已经初始化
    clearStr(str);
    int len_ch = (int) strlen(ch);
    int start = W_MAX - len_ch;//start为数组下标开始处
    if (len_ch <= W_MAX) {
        for (int i = start; i < start + len_ch; i++) {
            if (*(str + i) != '\0') *(str + i) = ch[i - (start)];
        }
    }
}

char *formatStr(char *format, int count, ...) {//直接返回格式化后的文本,最长不超过128
    static char result[128] = "";//提供128字节的缓冲区
    va_list vaList;
    va_start(vaList, count);
    vsprintf(result, format, vaList);
    va_end(vaList);
    return result;
}

char *connectStr(int count, ...) {//将count个字符串拼接起来,最长不超过128
    int i;
    va_list vaList;
    va_start(vaList, count);
    static char result[128] = "";//提供128字节的缓冲区
    for (i = 0; i < count; i++)
        strcat(result, va_arg(vaList, char*));
    va_end(vaList);
    return result;
}

//bitUtils

//获取无符号整数n的低第k位
int getBit(unsigned int n, int k) {
    return (int) ((n >> (k - 1)) & 1);
}

//设置无符号整数n的低第k位为1并返回
unsigned int setBit(unsigned int n, int k) {
    return (n | (1 << (k - 1)));
}

//设置无符号整数n的低第k位为0并返回
unsigned int resetBit(unsigned int n, int k) {
    return n & (~(1 << (k - 1)));
}

//timeUtils
char *getNowTime() {//获取当前时间的文本
    struct tm *newtime;
    static char buf[20] = {};
    time_t lt1;
    lt1 = time(NULL);
    newtime = localtime(&lt1);
    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", newtime);
    return buf;
}

char *getTimePeriod() {//获取当前时间段
    time_t lt1;
    lt1 = time(NULL);
    struct tm *newtime;
    newtime = localtime(&lt1);
    if (newtime->tm_hour < 6) {
        return TIMEPERIOD_BEFORE_DAWN;
    } else if (newtime->tm_hour < 11) {
        return TIMEPERIOD_MORNING;
    } else if (newtime->tm_hour < 14) {
        return TIMEPERIOD_NOON;
    } else if (newtime->tm_hour < 19) {
        return TIMEPERIOD_AFTERNOON;
    } else return TIMEPERIOD_NIGHT;
}

void setError(int *error, int msg) {
    if (error != NULL) *error = msg;
}

char *getGameNameById(int gameid) {
    switch (gameid) {
        case GAMEID_GLUTTONOUSSNAKE:
            return GAMENAME_GLUTTONOUSSNAKE;
        case GAMEID_GUESSNUMBER:
            return GAMENAME_GUESSNUMBER;
        case GAMEID_TETRIS:
            return GAMENAME_TETRIS;
    }
}


#endif //BIGPROJECT_UTILS_C
