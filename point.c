//
// Created by HJH201314 on 2021/11/9.
//

#ifndef BIGPROJECT_POINT_C
#define BIGPROJECT_POINT_C

int point = 0;

int getPoints() {
    return point;
}

void addPoints(int n) {
    point += n;
}

void delPoints(int n) {
    point -= n;
}

#endif //BIGPROJECT_POINT_C
