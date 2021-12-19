//
// Created by HJH201314 on 2021/12/11.
// 本头文件包含所有页面的主函数
//

#ifndef BIGPROJECT_PAGELIST_H
#define BIGPROJECT_PAGELIST_H

#define GAMEID_GUESSNUMBER 1
#define GAMENAME_GUESSNUMBER "猜数字"
#define GAMEID_GLUTTONOUSSNAKE 2
#define GAMENAME_GLUTTONOUSSNAKE "贪吃蛇"
#define GAMEID_TETRIS 3
#define GAMENAME_TETRIS "俄罗斯方块"

void pageMain();
int pageGuessNumber();
int pageGluttonousSnake();
int pageTetris();

int pageUser();

#endif //BIGPROJECT_PAGELIST_H
