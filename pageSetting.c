//
// Created by HJH201314 on 2021/12/24.
//

#include <windows.h>
#include <conio.h>
#include "global.h"

void drawPageSetting();

int pageSetting() {
    initPage();
    drawPageSetting();
    output();
    int ch = 0;
    while (1) {
        SetConsoleTitleA("设置");
        ch = _getch();
        switch (ch) {
            case KEY_ESC:
                return FLAG_EXIT;
        }
        initPage();
        drawPageSetting();
        output();
    }
}

void drawPageSetting() {

}