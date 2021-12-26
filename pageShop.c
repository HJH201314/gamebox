//
// Created by HJH201314 on 2021/12/24.
//

#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "lib/sqlite3.h"
#include "global.h"

typedef struct {
    char name[16];//用作标识的商品名
    char name_show[16];//用作展示的商品名
    int price;//商品价格
    int count;//一次购买的份数
} ShopItem;

static void initShop();

static void loadItems();

static void addItem(char *item, char *showname, int price, int count);

static ShopItem itemlist[100];
static int itemcount = 0;
static int selector = 0;

extern char username[129];
extern sqlite3 *db;

int pageShop() {
    SetConsoleTitleA("游戏商店");
    initPage();
    initShop();
    selector = 0;
    output();
    int ch = 0;
    while (1) {
        ch = _getch();
        switch (ch) {
            case KEY_ESC:
                return FLAG_EXIT;
            case KEY_TOP: {
                if (selector > 0) {
                    selector--;
                    loadItems();
                }
                break;
            }
            case KEY_BOTTOM: {
                if (selector < itemcount - 1) {
                    selector++;
                    loadItems();
                }
                break;
            }
            case KEY_ENTER:
            {
                if (getPoints(username) >= itemlist[selector].price) {
                    addBpItem(username,itemlist[selector].name,itemlist[selector].count);
                    delPoints(username,itemlist[selector].price);
                    loadItems();//刷新一下
                    setTipsAndShineGreen("购买成功!");
                } else {
                    setTipsAndShineRed("积分不足!");
                }
                break;
            }
        }
        output();
    }
}

static void initShop() {
    itemcount = 0;
    selector = 0;
    addItem("life","一线生机", 199, 1);
    addItem("life","一线生机 * 5", 899, 5);
    setLineCenter(2, "商店");
    setLineCenter(4, formatStr(" %-16s %-5s %-5s %11s", 4, "物品", "价格", "数量",""));
    loadItems();
}

static void loadItems() {//加载商品
    setLineRight(1, formatStr("Points:%d",1, getPoints(username)));
    for (int i = 0; i < itemcount; i++) {
        setLineCenter(5 + i,
                      formatStr("%1s%-16s %-5d %-5d 已拥有:%-4d", 4, (selector == i ? ">" : ""), itemlist[i].name_show, itemlist[i].price,
                                itemlist[i].count, getBpItemCount(username,itemlist[i].name)));
    }
}

static void addItem(char *item, char *showname, int price, int count) {
    strcpy(itemlist[itemcount].name, item);
    strcpy(itemlist[itemcount].name_show, showname);
    itemlist[itemcount].price = price;
    itemlist[itemcount].count = count;
    itemcount++;
}

static void buyItem(int id) {

}