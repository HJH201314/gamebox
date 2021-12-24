//
// Created by HJH201314 on 2021/12/12.
//

#include <stdio.h>
#include "global.h"

#define LINE_MAX 256

void writeFileOneLine(char *filename, char *content) {
    FILE *fp = NULL;
    fp = fopen(formatStr("%s", 1, filename), "w+");
    fprintf(fp, "%s", content);
    fclose(fp);
}

void readFileOneLine(char *filename, char *result) {
    FILE *fp = NULL;
    fp = fopen(formatStr("%s", 1, filename), "r+");
    fgets(result, LINE_MAX, fp);
    fclose(fp);
}
