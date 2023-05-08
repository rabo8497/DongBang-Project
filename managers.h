#ifndef MANAGERS_H
#define MANAGERS_H

#include <set>
#include <string>
#include <iostream>
#include "caelum.h"

#include "fileHandler.h"
#include "user.h"

class Manager
{
private:
    std::set<Caelum &> Items;

public:
    virtual void showList();
    void addItem(Caelum &);
    void deleteItem(int);
    Caelum &getItem(int);
    virtual int search(std::string);
    void import();
    void export();
};

class AccountManager : public Manager
{
public:
    void showList(bool);
    void showList(std::string, bool);
    int search(std::string, std::string);
    int search(std::string);
};

class DeviceManager : public Manager
{
public:
    void showList(bool);
    int search(std::string);
};

#endif