//
// Created by HJH201314 on 2021/12/24.
//

#ifndef BIGPROJECT_BACKPACK_H
#define BIGPROJECT_BACKPACK_H

int isBpItemExist(char *username,char *item);
int addBpItem(char * username, char *item, int count);
int getBpItemCount(char *username, char *item);
void useBpItem(char *username, char *item);

#endif //BIGPROJECT_BACKPACK_H
