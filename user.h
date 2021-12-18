//
// Created by HJH201314 on 2021/12/18.
//

#ifndef BIGPROJECT_USER_H
#define BIGPROJECT_USER_H

int isUserExist(char *username);

int createUser(char *username, char *password, int *error);

int deleteUser(char *username, char *password, int *error);

#endif //BIGPROJECT_USER_H
