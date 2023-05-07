#include "managers.h"

// Manager : the base class
Manager::Manager()
{
    Items = new std::vector<Caelum *>;
    Items->reserve(EXPECTED_SIZE);
}

Manager::~Manager()
{
    delete Items;
}

void Manager::addItem(Caelum *item)
{
    Items->push_back(item);
}

std::vector<Caelum *>::iterator Manager::getIter(int id)
{
    std::vector<Caelum *>::iterator it;
    for (it = Items->begin(); it < Items->end(); it++)
    {
        if ((*it)->getId() == id)
            return it;
    }
    return it;
}

void Manager::deleteItem(int id)
{
    std::iter_swap(getIter(id), Items->end() - 1);
    Items->pop_back();
}

Caelum *Manager::getItem(int id)
{
    return *getIter(id);
}

int Manager::search(std::string keyword)
{
    for (auto i : *Items)
    {
        if (i->getName() == keyword)
            return i->getId();
    }
    return -1;
}

std::vector<Caelum *> *Manager::getList()
{
    return Items;
}

void AccountManager ::printAccount(Account *item)
{
    std::cout << "===============" << std ::endl;
    std::cout << "[Account] " << item->getType() << " " << item->getName() << std::endl;
    if (item->active())
    {
        std::cout << "USED" << std::endl;
    }
    else
    {
        // std::cout << "AVAILABLE" << std::endl;
    }
    std::cout << std::endl;
}

void AccountManager::showList(bool showActive = false)
{
    for (auto i : *getList())
    {
        Account *item = (Account *)i;
        if (!showActive && item->active())
            continue;
        printAccount(item);
    }
}

void AccountManager::showList(std::string type, bool showActive = false)
{
    for (auto i : *getList())
    {
        Account *item = (Account *)i;
        if (!showActive && item->active())
            continue;
        if (item->getType() != type)
            continue;
        printAccount(item);
    }
}

int AccountManager::search(std::string type, std::string name)
{
    for (auto i : *getList())
    {
        Account *item = (Account *)i;
        if (item->getType() == type && item->getName() == name)
            return item->getId();
    }
    return -1;
}

int AccountManager::search(std::string name)
{
    return Manager::search(name);
}

void DeviceManager::showList(bool showActive = false)
{
    for (auto i : *getList())
    {
        Device *item = (Device *)i;
        if (!showActive && item->active())
            continue;
        std::cout << "================" << std::endl;
        std::cout << "[Device] " << item->getName() << std::endl;
        if (item->active())
        {
            std::cout << "USED : now playing" << item->getGame() << std::endl;
        }
    }
}