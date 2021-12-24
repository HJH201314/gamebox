//
// Created by HJH201314 on 2021/12/24.
//

#include "setting.h"


#include <string.h>
#include "lib/sqlite3.h"
#include "lib/hashMap.h"
#include "global.h"

extern sqlite3 *db;
extern HASHMAP(char,int) setting_map;

int isSettingExist(char *item) {
    sqlite3_stmt *pStmt;
    sqlite3_prepare_v2(db, "SELECT count(*) FROM setting WHERE item=?", -1, &pStmt, 0);
    if (pStmt == 0)
        return 0;
    sqlite3_bind_text(pStmt, 1, item, (int) strlen(item), NULL);
    if (sqlite3_step(pStmt) != SQLITE_ROW) {
        sqlite3_finalize(pStmt);
        return 0;
    }
    int ret = sqlite3_column_int(pStmt, 0);
    sqlite3_finalize(pStmt);
    return (ret != 0);
}

//初始化设置的表
void initSettingMap() {
    sqlite3_stmt *pStmt;
    char *sql = "SELECT item,value FROM setting";
    sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
    if (pStmt == 0)
        return;
    int ret = getResultRows(db, sql);
    if (ret > 0) {
        //sqlite3_step(pStmt);
        int c = 0;
        while (sqlite3_step(pStmt) == SQLITE_ROW) {
            int value = sqlite3_column_int(pStmt,1);
            const char *key;
            key = (char *)sqlite3_column_text(pStmt,0);
            hashmap_put(&setting_map, key, &value);
            c++;
        }
    }
    sqlite3_finalize(pStmt);
}

//置设置,成功返回1,失败返回0
int putSetting(char *item, int value) {
    sqlite3_stmt *pStmt;
    int ret;//sqlite3_step的返回值
    if (!isSettingExist(item)) {//若不存在则插入
        sqlite3_prepare_v2(db, "INSERT INTO setting (item,value) VALUES(?,?)", -1, &pStmt, 0);
        if (pStmt == 0)
            return 0;
        sqlite3_bind_text(pStmt, 1, item, -1, NULL);
        sqlite3_bind_int(pStmt, 2, value);
        ret = sqlite3_step(pStmt);
        sqlite3_finalize(pStmt);
    } else {
        sqlite3_prepare_v2(db, "UPDATE setting SET value=? WHERE item=?", -1, &pStmt, 0);
        if (pStmt == 0)
            return 0;
        sqlite3_bind_text(pStmt, 2, item, -1, NULL);
        sqlite3_bind_int(pStmt, 1, value);
        ret = sqlite3_step(pStmt);
        sqlite3_finalize(pStmt);
    }
    if (ret == SQLITE_DONE) hashmap_put(&setting_map,item,&value);
    return (ret == SQLITE_DONE);
}

//取设置,在哈希表中取设置
int getSetting(const char *item) {
    int *ret = hashmap_get(&setting_map,item);
    if (ret == NULL) {
        return -1;
    } else {
        return *ret;
    }
}