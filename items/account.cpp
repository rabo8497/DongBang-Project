#include "Account.h"
#include "../styles/colors.h"
#include <iomanip>
#include <sstream>
using std::setw;

Account::Account(std::string accountType, std::string name, int id, bool isActive, int controllerId, time_t startTime) : Item(name, id, isActive, ACCOUNT, controllerId), accountType(accountType), startTime(startTime)
{
    startTime = 0;
}

Account::~Account() {}

void Account::printInfo(User &user)
{
    const int typeWidth = 8, nameWidth = 12;

    std::stringstream ss;
    std::cout << setw(typeWidth) << accountType << " - " << setw(nameWidth) << getName();
    if (active())
    {
        std::cout << YELLOW << " ( " << setcolor(ss, 240, 134, 80) << "ON" << YELLOW << " ) " << RESET;
        if (this->getcontrollerId() == user.getId())
            std::cout << GREEN << " *" << RESET;
    }
    else
    {
        std::cout << YELLOW << " ( " << setcolor(ss, 126, 132, 247) << "OFF" << YELLOW << " ) " << RESET;
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

void Account::toggle(int userId)
{
    if (!this->active())
    {
        setState(ACTIVE);
    }
    else
    {
        setState(INACTIVE);
    }
    setcontrollerId(userId);
}