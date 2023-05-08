#ifndef ITEMMAGANER_H
#define ITEMMANAGER_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "item.h"

#define EXPECTED_LIST_SIZE 16

class ItemManager
{
private:
    std::vector<Item *> Items;

public:
    ItemManager();
    void showList(bool = false);
    void showList(Type, bool = false);
    void addItem(Item *);
    void deleteItem(int);
    Item *getItem(int);
    Item *getItem(std::string);
};

#endif