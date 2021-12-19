//
// Created by HJH201314 on 2021/12/18.
//

#ifndef BIGPROJECT_SQLUTILS_H
#define BIGPROJECT_SQLUTILS_H

#include "lib/sqlite3.h"

int isTableExist(sqlite3 *db, char *tablename);//判断数据表是否存在
int getResultRows(sqlite3 *db, char *expandedSql);//通过完整sql获取记录集的行数

#endif //BIGPROJECT_SQLUTILS_H
