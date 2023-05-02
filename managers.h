#ifndef MANAGERS_H
#define MANAGERS_H

#include <set>
#include <string>
#include "caelum.h"

class Manager
{
private:
    std::set<Caelum &> Items;

public:
    virtual void ShowList();
    void AddItem(Caelum &);
    void DeleteItem(int);
    Caelum &GetItem(int);
    virtual int Search(std::string);
    void Import();
    void Export();
};

class AccountManager : public Manager
{
public:
    void ShowList(bool);
    void ShowList(std::string, bool);
    int Search(std::string, std::string);
    int Search(std::string);
};

class DeviceManager : public Manager
{
public:
    void ShowList(bool);
    int Search(std::string);
};

#endif