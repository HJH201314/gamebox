//
// Created by HJH201314 on 2021/12/18.
//

#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "lib/sqlite3.h"

extern sqlite3 *db;

int isUserExist(char *username) {
    sqlite3_stmt *pStmt;
    sqlite3_prepare_v2(db, "SELECT count(*) FROM user WHERE username=?", -1, &pStmt, 0);
    if (pStmt == 0)
        return 0;
    sqlite3_bind_text(pStmt, 1, username, (int) strlen(username), NULL);
    if (sqlite3_step(pStmt) != SQLITE_ROW) {
        sqlite3_finalize(pStmt);
        return 0;
    }
    int ret = sqlite3_column_int(pStmt, 0);
    sqlite3_finalize(pStmt);
    return (ret != 0);
}

int createUser(char *username, char *password, int *error) {
    if (!isUserExist(username)) {
        sqlite3_stmt *pStmt;
        sqlite3_prepare_v2(db, "INSERT INTO user (username,password) VALUES(?,?)", -1, &pStmt, 0);
        if (pStmt == 0)
            return 0;
        sqlite3_bind_text(pStmt, 1, username, -1, NULL);
        sqlite3_bind_text(pStmt, 2, password, -1, NULL);
        int ret = sqlite3_step(pStmt);
        sqlite3_finalize(pStmt);
        return (ret == SQLITE_DONE);
    } else {
        setError(error, ERROR_EXIST);
        return 0;
    }
}

int deleteUser(char *username, char *password, int *error) {
    if (isUserExist(username)) {
        sqlite3_stmt *pStmt;
        sqlite3_prepare_v2(db, "DELETE FROM user WHERE username=? AND password=?", -1, &pStmt, 0);
        if (pStmt == 0)
            return 0;
        sqlite3_bind_text(pStmt, 1, username, -1, NULL);
        sqlite3_bind_text(pStmt, 2, password, -1, NULL);
        int ret = sqlite3_step(pStmt);
        sqlite3_finalize(pStmt);
        return (ret == SQLITE_DONE);
    } else {
        setError(error, ERROR_INEXIST);
        return 0;
    }
}

//游戏记录相关
int addRecord(char *username, int gameid, int score, int points) {
    if (isUserExist(username)) {
        sqlite3_stmt *pStmt;
        sqlite3_prepare_v2(db, "INSERT INTO record (username,game,score,points,time) VALUES(?,?,?,?,?)", -1, &pStmt,
                           0);
        if (pStmt == 0)
            return 0;
        sqlite3_bind_text(pStmt, 1, username, -1, NULL);
        sqlite3_bind_int(pStmt, 2, gameid);
        sqlite3_bind_int(pStmt, 3, score);
        sqlite3_bind_int(pStmt, 4, points);
        sqlite3_bind_text(pStmt, 5, getNowTime(), -1, NULL);
        int ret = sqlite3_step(pStmt);
        sqlite3_finalize(pStmt);
        return (ret == SQLITE_DONE);
    } else {
        return 0;
    }
}

int getRecord(char *username, char *condition, int count, int page, GameRecord **pGameRecord) {//
    if (isUserExist(username)) {
        sqlite3_stmt *pStmt;
        const char *sql = "SELECT game,score,points,time FROM record";
        sqlite3_prepare_v2(db, (condition != NULL ? connectStr(3, sql, " WHERE ", condition) : sql), -1, &pStmt, 0);
        if (pStmt == 0)
            return 0;
        char *newsql = sqlite3_expanded_sql(pStmt);
        int ret = getResultRows(db, newsql);
        if (ret > 0) {
            sqlite3_step(pStmt);
            **pGameRecord = *(GameRecord *) malloc(sizeof(GameRecord) * ret);//分配空间
            int c = 0;
            while (sqlite3_step(pStmt)) {
                pGameRecord[c]->game = sqlite3_column_int(pStmt,0);
                pGameRecord[c]->score = sqlite3_column_int(pStmt,1);
                pGameRecord[c]->points = sqlite3_column_int(pStmt,2);
                strcpy(pGameRecord[c]->time,(char *)sqlite3_column_text(pStmt,3));
            }
        }
        sqlite3_finalize(pStmt);
        return ret;
    } else {
        return 0;
    }
}
