//
// Created by HJH201314 on 2021/12/18.
//

#ifndef BIGPROJECT_USER_H
#define BIGPROJECT_USER_H

int isUserExist(char *username);

int createUser(char *username, char *password, int *error);

int deleteUser(char *username, char *password, int *error);

typedef struct {
    int game;
    int score;
    int points;
    char time[20];
} GameRecord;

int addRecord(char *username, int gameid, int score, int points);

int getRecord(char *username, char *condition, int count, int page, GameRecord **pGameRecord);

#endif //BIGPROJECT_USER_H
