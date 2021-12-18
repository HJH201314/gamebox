//
// Created by HJH201314 on 2021/12/18.
//

#include <string.h>
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
        setError(error,ERROR_EXIST);
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
        setError(error,ERROR_INEXIST);
        return 0;
    }
}
