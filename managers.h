#ifndef MANAGERS_H
#define MANAGERS_H

#include <set>
#include <string>
#include "caelum.h"

class AccountManager
{
private:
    std::set<Account> Accounts;

public:
    void ShowList(std::string, bool);
    void Add();
    void Delete();
    int Search(std::string, std::string);
    int Search(std::string);
    void Import();
    void Export();
};

class DeviceManager
{
private:
    std::set<Device> devices;

public:
    void ShowList(bool);
    void Add();
    void Delete();
    int Search(std::string);
    void Import();
    void Export();
};

#endif