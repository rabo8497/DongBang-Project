#include "itemManager.h"

ItemManager::ItemManager()
{
    Items.reserve(EXPECTED_LIST_SIZE);
}

inline void printSingleItem(int index, Item *i)
{
    std::cout << index << ". ";
    i->printInfo();
    std::cout << std::endl;
}

void ItemManager::showList(bool showActive)
{
    int idx = 1;
    for (auto i : Items)
    {
        if (!showActive && i->active())
            continue;
        printSingleItem(idx, i);
    }
}

void ItemManager::showList(Type typeFilter, bool showActive)
{
    int idx = 1;
    for (auto i : Items)
    {
        if ((!showActive && i->active()) || i->getType() != typeFilter)
            continue;
        printSingleItem(idx, i);
    }
}

void ItemManager::addItem(Item *item)
{
    Items.push_back(item);
}

void ItemManager::deleteItem(int id)
{
    std::vector<Item *>::iterator target;
    for (std::vector<Item *>::iterator it = Items.begin(); it < Items.end(); it++)
    {
        if ((*it)->getId() == id)
        {
            target = it;
            break;
        }
    }
    std::iter_swap(target, Items.end() - 1);
    Items.pop_back();
}

Item *ItemManager::getItem(int id)
{
    for (auto i : Items)
    {
        if (i->getId() == id)
            return i;
    }
}
Item *ItemManager::getItem(std::string name)
{
    for (auto i : Items)
    {
        if (i->getName() == name)
            return i;
    }
}