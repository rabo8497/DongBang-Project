#include "Account.h"

Account::Account(std::string accountType, std::string name, int id, bool isActive, int controllerId, time_t startTime) : Item(name, id, isActive, ACCOUNT), accountType(accountType), controllerId(controllerId), startTime(startTime)
{
    startTime = 0;
}

Account::~Account() {}

void Account::printInfo()
{
    std::cout << accountType << " - " << getName();
    if (active())
    {
        std::cout << " ( ON )";
    }
    else
    {
        std::cout << " ( OFF )";
    }
}

std::string Account::getAccountType() { return accountType; }

std::time_t Account::getStartTime() { return startTime; }

int Account::getcontrollerId() { return controllerId; }

void Account::setcontrollerId(int uuid) { this->controllerId = uuid; }

void Account::setState(State state)
{
    Item::setState(state);
    if (state)
        startTime = std::time(0);
    else
        startTime = 0;
}

void Account::toggleState(int userId)
{
    controllerId = userId;
    Item::toggleState();
}