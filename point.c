//
// Created by HJH201314 on 2021/11/9.
//

#ifndef BIGPROJECT_POINT_C
#define BIGPROJECT_POINT_C

#include "stdio.h"
#include "lib/sqlite3.h"
#include "global.h"

extern sqlite3 *db;

int point = 0;

int getPoints(char * username) {
    sqlite3_stmt *pStmt;
    sqlite3_prepare_v2(db, "SELECT points FROM user WHERE username=?", -1, &pStmt, 0);
    if (pStmt == 0)
        return 0;
    sqlite3_bind_text(pStmt, 1, username, -1, NULL);
    if (sqlite3_step(pStmt) != SQLITE_ROW) {
        sqlite3_finalize(pStmt);
        return 0;
    }
    int ret = sqlite3_column_int(pStmt, 0);
    sqlite3_finalize(pStmt);
    return ret;
}

int addPoints(char *username, int n) {
    sqlite3_stmt *pStmt;
    sqlite3_prepare_v2(db, "UPDATE user SET points=points+? WHERE username=?", -1, &pStmt, 0);
    if (pStmt == 0)
        return ERROR_DATABASE;
    sqlite3_bind_int(pStmt, 1, n);
    sqlite3_bind_text(pStmt, 2, username, -1, NULL);
    int ret = sqlite3_step(pStmt);
    sqlite3_finalize(pStmt);
    return (ret == SQLITE_DONE);
}

int delPoints(char *username, int n) {
    sqlite3_stmt *pStmt;
    sqlite3_prepare_v2(db, "UPDATE user SET points=points-? WHERE username=?", -1, &pStmt, 0);
    if (pStmt == 0)
        return ERROR_DATABASE;
    sqlite3_bind_int(pStmt, 1, n);
    sqlite3_bind_text(pStmt, 2, username, -1, NULL);
    int ret = sqlite3_step(pStmt);
    sqlite3_finalize(pStmt);
    return (ret == SQLITE_DONE);
}

#endif //BIGPROJECT_POINT_C
