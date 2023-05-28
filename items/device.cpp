#include "Device.h"
#include <iostream>
#include <iomanip>
using namespace std;

Device::Device(std::string name, int id, bool isActive)
    : Item(name, id, isActive, DEVICE), calendar(Calendar(name))
{
    calendar.load();
}

void Device::printInfo()
{
    std::cout << getName();
    if (active())
    {
        std::cout << " ( ON ) ";
    }
    else
    {
        std::cout << " ( OFF ) ";
    }
}

void Device::prompt(const User &user)
{
    cout << "[ Time table of " << getName() << " ]" << endl;
    calendar.print_calendar(user);
    prompter.makeBox(opTitle, opList);
    pair<int, int> start, end;
    string day;
    switch (prompter.makeChoice("(back : 0)"))
    {
    case 1:
        cout << "enter start of reservation (ex : Mon 10) > ";
        cin >> day >> start.second;
        int wd = 0;
        for (auto d : weekday)
        {
            if (day == d)
                break;
            wd++;
        }
        start.first = wd;

        cout << "enter end of reservation (ex : Mon 10) > ";
        cin >> day >> end.second;
        int wd = 0;
        for (auto d : weekday)
        {
            if (day == d)
                break;
            wd++;
        }
        end.first = wd;

        calendar.markPeriodWithUUID(user, start.first, start.second, end.first, end.second);
        break;

    case 2:
        if (prompter.makeChoice("are you sure? (yes : 1,  no : 0) > ") == 1)
            calendar.resetUUIDInCalendar(user);
        break;
    default:
    }
}