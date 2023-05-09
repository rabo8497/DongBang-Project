#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <ctime>
#include "item.h"

class Account : public Item
{
private:
    std::string accountType;
    std::time_t startTime;

public:
    Account(std::string = "unknown", std::string = "unknown account", int = -1);
    void printInfo() override;
    std::string getAccountType();
    std::time_t getStartTime();
    void setState(State);
};

#endif