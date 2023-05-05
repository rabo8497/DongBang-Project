#ifndef MANAGERS_H
#define MANAGERS_H

#include <iostream>
#include <set>
#include <string>
#include "caelum.h"

template <typename T>
class Manager
{
private:
    std::set<T> *Items;

public:
    Manager();
    ~Manager();
    virtual void showList() = 0;
    void addItem(T &);
    void deleteItem(int);
    T &getItem(int);
    virtual int search(std::string);
    // filehandler 추가 바람
};

class AccountManager : public Manager<Account>
{
public:
    void showList(bool);
    void showList(std::string, bool);
    int search(std::string, std::string);
    int search(std::string);
};

class DeviceManager : public Manager<Device>
{
public:
    void showList(bool);
    int search(std::string);
};

#endif