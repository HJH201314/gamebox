//
// Created by HJH201314 on 2021/12/24.
//

#ifndef BIGPROJECT_SETTING_H
#define BIGPROJECT_SETTING_H

int isSettingExist(char *item);
void initSettingMap();
int putSetting(char *item, int value);
int getSetting(const char *item);

#endif //BIGPROJECT_SETTING_H
