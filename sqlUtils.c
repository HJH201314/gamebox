//
// Created by HJH201314 on 2021/12/18.
//

#include <string.h>
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
