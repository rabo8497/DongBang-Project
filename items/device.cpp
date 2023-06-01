#include "Device.h"
#include <iostream>
#include <iomanip>
#include "weekday.h"
#include "../styles/colors.h"
using namespace std;
using std::setw;

Device::Device(std::string name, int id, bool isActive)
    : Item(name, id, isActive, DEVICE), calendar(Calendar(name))
{
    calendar.load();
}

Device::~Device()
{
    calendar.write();
}

void Device::printInfo(User &user)
{
    const int nameWidth = 8;

    std::stringstream ss;
    std::cout << std::setw(nameWidth) << getName();

    // cheky reservo
    bool act = false;
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 24; j++)
            if (!calendar.isSlotEmpty(i, j))
            {
                act = true;
                break;
            }

    if (act)
    {
        std::cout << YELLOW << " ( " << setcolor(ss, 240, 134, 80) << "RESERVED" << YELLOW << " ) " << RESET
                  << setw(10) << "";
    }
    else
    {
        std::cout << YELLOW << " ( " << setcolor(ss, 126, 132, 247) << "NOT RESERVED" << YELLOW << " ) " << RESET
                  << setw(6) << "";
    }
}

Calendar &Device::getCalendar() { return calendar; }

const int linewidth = 40;

void Device::prompt(const User &user)
{
    int choice;
    while (true)
    {
        calendar.print_calendar(user);

        // input input
        cout << setw(linewidth) << setfill('-') << "" << setfill(' ') << endl
             << "| " << setw(linewidth - 4) << "1. Make reservation"
             << " |" << endl
             << "| " << setw(linewidth - 4) << "2. Delete existing reservation"
             << " |" << endl
             << setw(linewidth) << setfill('-') << "" << setfill(' ') << endl
             << " (0 : exit) > ";
        cin >> choice;

        if (choice == 1)
        {
            // calendar gogo vroom vroom set input
            Weekday start, end;
            cout << " start of reservation " << UNDER << "(ex : Mon 10)" << RESET << " : ";
            start.input();
            cout << " end of reservation : ";
            end.input();

            // check go brrr
            bool isValid = true;
            pair<int, int> timeRange;

            // err check
            if (timeRange.first < 0)
            {
                cout << RED << " ERROR : your typing " << ITALIC << "sucks" << RESET << endl;
                continue;
            }
            timeRange.first = start.getDay() * 24 + start.getTime();
            timeRange.second = end.getDay() * 24 + end.getTime();
            for (int i = timeRange.first; i <= timeRange.second; i++)
            {
                if (!calendar.isSlotEmpty(i / 24, i % 24))
                {
                    isValid = false;
                    break;
                }
            }
            if (isValid)
            {
                calendar.markPeriodWithUUID(user, start.getDay(), start.getTime(), end.getDay(), end.getTime());
            }
            else
            {
                cerr << RED << " ERROR : time range has occupied slot" << RESET << endl;
            }
        }
        else if (choice == 2)
        {
            // shutting down... shutting down...
            char c;
            cout << " are you sure? [y/n] : ";
            cin >> c;
            if (c == 'y' || c == 'Y')
                calendar.resetUUIDInCalendar(user);
        }
        else
            break;
    }
    calendar.write();
}