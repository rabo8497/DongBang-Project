#include "Device.h"
#include <iostream>
#include <iomanip>
#include "weekday.h"
using namespace std;

Device::Device(std::string name, int id, bool isActive)
    : Item(name, id, isActive, DEVICE), calendar(Calendar(name))
{
    calendar.load();
}

Device::~Device()
{
    calendar.write();
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

Calendar &Device::getCalendar() { return calendar; }

const int linewidth = 40;

void Device::prompt(const User &user)
{
    int choice;

    while (true)
    {
        // input input
        cout << setw(linewidth) << setfill('-') << "" << setfill(' ') << endl
             << "| " << setw(linewidth - 4) << "1. Make reservation"
             << " |" << endl
             << "| " << setw(linewidth - 4) << "2. Delete existing reservation"
             << " |" << endl
             << " (0 : exit) > ";
        cin >> choice;

        if (choice == 1)
        {
            // calendar gogo vroom vroom set input
            Weekday start, end;
            calendar.print_calendar(user);
            cout << " start of reservation (ex : Mon 10) : ";
            cin >> start;
            cout << " end of reservation : ";
            cin >> end;

            // check go brrr
            bool isValid = true;
            pair<int, int> timeRange;
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
                char c;
                cout << " are you sure? [y/n] :";
                cin >> c;
                if (c == 'y' || c == 'Y')
                    calendar.markPeriodWithUUID(user, start.getDay(), start.getTime(), end.getDay(), end.getTime());
            }
            else
            {
                cout << " ERROR : time range has occupied slot" << endl;
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
}