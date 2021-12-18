//
// Created by HJH201314 on 2021/12/18.
//

#ifndef BIGPROJECT_USER_H
#define BIGPROJECT_USER_H

#define ERROR_DATABASE 1000//数据库错误
#define ERROR_EXIST 1001//已存在
#define ERROR_INEXIST 1002//不存在

int isUserExist(char *username);

int createUser(char *username, char *password, int *error);

int deleteUser(char *username, char *password, int *error);

#endif //BIGPROJECT_USER_H
