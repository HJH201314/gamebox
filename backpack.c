//
// Created by HJH201314 on 2021/12/24.
//

#include <string.h>
#include "lib/sqlite3.h"
#include "global.h"

extern sqlite3 *db;

int isBpItemExist(char *username, char *item) {
    sqlite3_stmt *pStmt;
    sqlite3_prepare_v2(db, "SELECT count(*) FROM backpack WHERE username=? AND item=?", -1, &pStmt, 0);
    if (pStmt == 0)
        return 0;
    sqlite3_bind_text(pStmt, 1, username, -1, NULL);
    sqlite3_bind_text(pStmt, 2, item, -1, NULL);
    if (sqlite3_step(pStmt) != SQLITE_ROW) {
        sqlite3_finalize(pStmt);
        return 0;
    }
    int ret = sqlite3_column_int(pStmt, 0);
    sqlite3_finalize(pStmt);
    return (ret != 0);
}

//置设置,成功返回1,失败返回0
int addBpItem(char *username, char *item, int count) {
    sqlite3_stmt *pStmt;
    int ret;//sqlite3_step的返回值
    if (!isBpItemExist(username, item)) {//若不存在则插入
        sqlite3_prepare_v2(db, "INSERT INTO backpack (username,item,count) VALUES(?,?,?)", -1, &pStmt, 0);
        if (pStmt == 0)
            return 0;
        sqlite3_bind_text(pStmt, 1, username, -1, NULL);
        sqlite3_bind_text(pStmt, 2, item, -1, NULL);
        sqlite3_bind_int(pStmt, 3, count);
        ret = sqlite3_step(pStmt);
        sqlite3_finalize(pStmt);
    } else {
        sqlite3_prepare_v2(db, "UPDATE backpack SET count=count+? WHERE username=? AND item=?", -1, &pStmt, 0);
        if (pStmt == 0)
            return 0;
        sqlite3_bind_text(pStmt, 2, username, -1, NULL);
        sqlite3_bind_text(pStmt, 3, item, -1, NULL);
        sqlite3_bind_int(pStmt, 1, count);
        ret = sqlite3_step(pStmt);
        sqlite3_finalize(pStmt);
    }
    return (ret == SQLITE_DONE);
}

int getBpItemCount(char *username, char *item) {
    sqlite3_stmt *pStmt;
    char *sql = "SELECT count FROM backpack WHERE username=? AND item=? LIMIT 1";
    sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
    if (pStmt == 0)
        return 0;
    sqlite3_bind_text(pStmt, 1, username, -1, NULL);
    sqlite3_bind_text(pStmt, 2, item, -1, NULL);
    int ret = 0;
    while (sqlite3_step(pStmt) == SQLITE_ROW) {
        ret = sqlite3_column_int(pStmt, 0);
    }
    sqlite3_finalize(pStmt);
    return ret;
}

void useBpItem(char *username, char *item) {
    sqlite3_stmt *pStmt;
    sqlite3_prepare_v2(db, "UPDATE backpack SET count=count-1 WHERE username=? AND item=?", -1, &pStmt, 0);
    if (pStmt == 0)
        return;
    sqlite3_bind_text(pStmt, 1, username, -1, NULL);
    sqlite3_bind_text(pStmt, 2, item, -1, NULL);
    sqlite3_step(pStmt);
    sqlite3_finalize(pStmt);
}