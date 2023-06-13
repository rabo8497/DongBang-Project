#include "Account.h"
#include "../styles/colors.h"
#include <iomanip>
#include <sstream>
using std::setw;

Account::Account(std::string accountType, std::string name, int id, bool isActive, int controllerId, time_t startTime) : Item(name, id, isActive, ACCOUNT, controllerId), accountType(accountType), startTime(startTime)
{
    // In case of storing garbage values, variables are initalized.
    startTime = 0;
}

Account::~Account() {} // default constructor

void Account::printInfo(User &user)
{
    //'typeWidth' and 'nameWidth' are widths of each column.
    // ex : Laftel  - Mikan
    const int typeWidth = 8, nameWidth = 12;

    // to use "colors.h", stringstream needs to be declared.
    std::stringstream ss;
    std::cout << setw(typeWidth) << accountType << " - " << setw(nameWidth) << getName();

    // prints ( ON ) afterwards if this account is active
    if (active())
    {
        std::cout << YELLOW << " ( " << setcolor(ss, 240, 134, 80) << "ON" << YELLOW << " ) " << RESET;
        if (this->getcontrollerId() == user.getId())
            std::cout << GREEN << " *" << RESET; // if the account is occupied by current user, there is additional asterisk.
    }
    // prints ( OFF ) instead if the account is not activated.
    else
    {
        std::cout << YELLOW << " ( " << setcolor(ss, 126, 132, 247) << "OFF" << YELLOW << " ) " << RESET;
    }
}

// getter.
std::string Account::getAccountType() { return accountType; }

std::time_t Account::getStartTime() { return startTime; }

// setter.
void Account::setState(State state)
{
    Item::setState(state);
    if (state)
        startTime = std::time(0);
    else
        startTime = 0;
}

// due to how main program works, the boolean variable 'State' can be switched via this function.
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