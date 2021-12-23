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

//注册用户,成功返回1,失败返回0,具体错误可传入error获取ERROR_常量
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

//删除用户,成功返回1,失败返回0,具体错误可传入error获取ERROR_常量
int deleteUser(char *username, char *password, int *error) {
    if (isUserExist(username)) {
        if (!login(username,password)) {
            setError(error,ERROR_WRONGPWD);
            return 0;
        }
        sqlite3_stmt *pStmt;
        sqlite3_prepare_v2(db, "DELETE FROM user WHERE username=? AND password=?", -1, &pStmt, 0);
        if (pStmt == 0) {
            setError(error,ERROR_DATABASE);
            return 0;
        }
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

//登录,返回值包括1-成功/0-错误/ERROR_
int login(char *username, char *password) {
    if (isUserExist(username)) {
        sqlite3_stmt *pStmt;
        sqlite3_prepare_v2(db, "SELECT * FROM user WHERE username=? AND password=?", -1, &pStmt, 0);
        if (pStmt == 0) {
            return ERROR_DATABASE;
        }
        sqlite3_bind_text(pStmt, 1, username, -1, NULL);
        sqlite3_bind_text(pStmt, 2, password, -1, NULL);
        int ret = 0;
        if(sqlite3_step(pStmt) == SQLITE_ROW) {
            ret = 1;
        }
        sqlite3_finalize(pStmt);
        return ret;
    } else {
        return ERROR_INEXIST;
    }
}

//修改密码,传入username和newpassword,返回值包括1-成功/ERROR_
int changePwd(char *username, char *password) {
    if (isUserExist(username)) {
        sqlite3_stmt *pStmt;
        sqlite3_prepare_v2(db, "UPDATE user SET password=?1 WHERE username=?", -1, &pStmt, 0);
        if (pStmt == 0) {
            return ERROR_DATABASE;
        }
        sqlite3_bind_text(pStmt, 2, username, -1, NULL);
        sqlite3_bind_text(pStmt, 1, password, -1, NULL);
        char *sql = sqlite3_expanded_sql(pStmt);
        sqlite3_finalize(pStmt);
        sqlite3_exec(db,sql,NULL,NULL,NULL);
        return 1;
    } else {
        return ERROR_INEXIST;
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

//获取记录数的最大页码
int getRecordPageCount(char *username, int count) {
    if (isUserExist(username)) {
        sqlite3_stmt *pStmt;
        char *sql = "SELECT game,score,points,time FROM record WHERE username=?";
        sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
        if (pStmt == 0)
            return -1;
        sqlite3_bind_text(pStmt, 1, username, -1, NULL);
        char *newsql = sqlite3_expanded_sql(pStmt);
        int ret = getResultRows(db, newsql);
        sqlite3_finalize(pStmt);
        return ret / count + 1;
    } else {
        return -1;
    }
}

//获取username的游戏记录
GameRecord *getRecord(char *username, int count, int page, int *ret) {
    if (isUserExist(username)) {
        sqlite3_stmt *pStmt;
        char *sql = "SELECT game,score,points,time FROM record WHERE username=? LIMIT %d OFFSET %d";
        sqlite3_prepare_v2(db, formatStr(sql, 2, count, count * (page - 1)), -1, &pStmt, 0);
        if (pStmt == 0)
            return NULL;
        sqlite3_bind_text(pStmt, 1, username, -1, NULL);
        char *newsql = sqlite3_expanded_sql(pStmt);
        *ret = getResultRows(db, newsql);
        static GameRecord *gr;
        gr = malloc(sizeof(GameRecord) * (*ret));//分配空间
        if (*ret > 0) {
            //sqlite3_step(pStmt);
            int c = 0;
            while (sqlite3_step(pStmt) == SQLITE_ROW) {
                gr[c].game = sqlite3_column_int(pStmt, 0);
                gr[c].score = sqlite3_column_int(pStmt, 1);
                gr[c].points = sqlite3_column_int(pStmt, 2);
                strcpy(gr[c].time, (char *) sqlite3_column_text(pStmt, 3));
                c++;
            }
        }
        sqlite3_finalize(pStmt);
        return gr;
    } else {
        return NULL;
    }
}
