//
// Created by HJH201314 on 2021/11/5.
//

#ifndef BIGPROJECT_FUNTIONLIST_H
#define BIGPROJECT_FUNTIONLIST_H

void initStrBlank(char * str, int size);
void clearStr(char * str);
void setStrFrom(char * str,int from,char * ch);
void setStrCenter(char * str,char * ch);
void setStrRight(char * str,char * ch);
void resetStrCenter(char * str,char * ch);
void resetStrRight(char * str,char * ch);

void setLine(int line,char * ch);
void setPoint(int x,int y,char ch);
void setLineLeft(int line,char * ch);
void setLineCenter(int line,char * ch);
void buildFrame();
void gotoxy(short x, short y);
void output();

#endif //BIGPROJECT_FUNTIONLIST_H
