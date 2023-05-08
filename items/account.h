#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <ctime>
#include "item.h"
#include "../user.h"

class Account : public Item
{
private:
    std::string accountType;
    // User &user;
    std::time_t startTime;

public:
    Account(std::string = "unknown", std::string = "unknown account", int = -1 /*, User & = User()*/);
    void printInfo() override;
    std::string getAccountType();
    // User &getUser();
    std::time_t getStartTime();
    void setState(State /*, User & = User()*/);
};

#endif