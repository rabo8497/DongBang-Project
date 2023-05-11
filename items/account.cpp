#include "account.h"

Account::Account(std::string accountType, std::string name, int id) : Item(name, id, ACCOUNT), accountType(accountType)
{
    startTime = 0;
}

void Account::printInfo()
{
    std::cout << accountType << " - " << getName();
    if (active())
    {
        std::cout << " ( 사용 가능 )";
    }
    else
    {
        std::cout << " ( 사용 중 )";
    }
}

std::string Account::getAccountType() { return accountType; }
std::time_t Account::getStartTime() { return startTime; }
void Account::setState(State state)
{
    Item::setState(state);
    if (state)
        startTime = std::time(0);
    else
        startTime = 0;
}