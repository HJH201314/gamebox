//
// Created by HJH201314 on 2021/12/18.
//

#include <string.h>
#include "global.h"
#include "lib/sqlite3.h"

int isTableExist(sqlite3 *db, char *tablename) {
    sqlite3_stmt *pStmt;
    sqlite3_prepare_v2 (db, "select count(*) from sqlite_master where type='table' and tbl_name=?", -1, &pStmt, 0);
    if (pStmt == 0)
        return 0;
    sqlite3_bind_text(pStmt, 1, tablename, (int)strlen(tablename), NULL);
    if (sqlite3_step (pStmt) != SQLITE_ROW)
        return 0;
    int ret = sqlite3_column_int (pStmt, 0);
    sqlite3_finalize (pStmt);
    return (ret != 0);
}

//通过完整的sql获取记录集的行数,失败返回-1,成功返回行数
int getResultRows(sqlite3 *db, char *expandedSql) {
    sqlite3_stmt *pStmt;
    sqlite3_prepare(db, formatStr("SELECT COUNT(*) FROM (%s)",1,expandedSql),-1,&pStmt,0);
    if (pStmt == 0)
        return -1;
    sqlite3_step(pStmt);//到第一行
    int ret = sqlite3_column_int(pStmt,0);
    sqlite3_finalize(pStmt);
    return ret;
}
