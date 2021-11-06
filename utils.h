//
// Created by HJH201314 on 2021/11/4.
//

#ifndef BIGPROJECT_UTILS_H
#define BIGPROJECT_UTILS_H

void initStrBlank(char * str, int size) {//初始化str为空格
    //memset设置内存
    memset(str, ' ', size);
}

void clearStr(char * str) {//将str前面不为\0的元素设置为空格
    //memset设置内存
    int len = (int)strlen(str);
    memset(str, ' ', len);
}

void setStrFrom(char * str,int from,char * ch){//从from(>0)开始设置str的值，注意str可设置的范围不为\0即已经初始化
    int len_ch = (int)strlen(ch);
    for(int i = from-1;i < from-1+len_ch;i++) {
        if(*(str+i) != '\0') *(str+i) = ch[i-(from-1)];
    }
}

void setStrCenter(char * str,char * ch){//居中在str中放置ch，注意str可设置的范围不为\0即已经初始化
    int len_ch = (int)strlen(ch);
    int start = (wmax - len_ch) / 2;//start为数组下标开始处
    if(len_ch <= wmax) {
        for(int i = start;i < start+len_ch;i++) {
            if(*(str+i) != '\0') *(str+i) = ch[i-(start)];
        }
    }
}

void setStrRight(char * str,char * ch){//居右在str中放置ch，注意str可设置的范围不为\0即已经初始化
    int len_ch = (int)strlen(ch);
    int start = wmax - len_ch;//start为数组下标开始处
    if(len_ch <= wmax) {
        for(int i = start;i < start+len_ch;i++) {
            if(*(str+i) != '\0') *(str+i) = ch[i-(start)];
        }
    }
}

void resetStrCenter(char * str,char * ch){//清空原有文字并从from(>0)开始设置str的值，注意str可设置的范围不为\0即已经初始化
    clearStr(str);
    int len_ch = (int)strlen(ch);
    int start = (wmax - len_ch) / 2;//start为数组下标开始处
    if(len_ch <= wmax) {
        for(int i = start;i < start+len_ch;i++) {
            if(*(str+i) != '\0') *(str+i) = ch[i-(start)];
        }
    }
}

void resetStrRight(char * str,char * ch){//清空原有文字并居右在str中放置ch，注意str可设置的范围不为\0即已经初始化
    clearStr(str);
    int len_ch = (int)strlen(ch);
    int start = wmax - len_ch;//start为数组下标开始处
    if(len_ch <= wmax) {
        for(int i = start;i < start+len_ch;i++) {
            if(*(str+i) != '\0') *(str+i) = ch[i-(start)];
        }
    }
}

#endif //BIGPROJECT_UTILS_H
