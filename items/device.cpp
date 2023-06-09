#include "Device.h"
#include <iostream>
#include <iomanip>
#include <string>
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

    // Check if there are any reservations
    bool hasReservations = false;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 24; j++)
        {
            if (!calendar.isSlotEmpty(i, j))
            {
                hasReservations = true;
                break;
            }
        }
    }

    if (hasReservations)
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

Calendar &Device::getCalendar()
{
    return calendar;
}

const int linewidth = 40;

void Device::prompt(LogManager &lm, const User &user)
{
    int choice;
    while (true)
    {
        calendar.print_calendar(user);

        // Prompt for user input
        cout << setw(linewidth) << setfill('-') << "" << setfill(' ') << endl
             << "| " << setw(linewidth - 4) << "1. Make reservation"
             << " |" << endl
             << "| " << setw(linewidth - 4) << "2. Delete existing reservation"
             << " |" << endl;
        if (user.getIsManager())
        {
            cout << "| " << setw(linewidth - 4) << "3. Delete all reservations"
                 << " |" << endl;
        }

        cout << setw(linewidth) << setfill('-') << "" << setfill(' ') << endl
             << " (0 : exit) > ";

        string ibuffer;
        while (true)
        {
            cout << " select device (back : 0) > ";

            cin >> ibuffer;
            if (!isdigit(ibuffer[0]))
            {
                std::cout << RED << "ERROR : " << RESET << "device ID is not a number" << std::endl;
                continue;
            }
            else
            {
                choice = (int)(ibuffer[0] - '0');
                break;
            }
        }

        if (choice == 1)
        {
            // Prompt for reservation details
            Weekday start, end;
            std::cout << " start of reservation " << UNDER << "(ex: Mon 10)" << RESET;
            start.input();
            std::cout << " end of reservation";
            end.input();

            // Check if the time range is valid
            bool isValid = true;
            pair<int, int> timeRange;

            // Error check
            if (timeRange.first < 0)
            {
                cout << RED << " ERROR : " << RESET << ITALIC << "Input is unavailable to parse." << RESET << endl;
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
                if (calendar.markPeriodWithUUID(user, start.getDay(), start.getTime(), end.getDay(), end.getTime()))
                {
                    lm.DeviceReserve(user, getName());
                }
            }
            else
            {
                cerr << RED << " ERROR : " << RESET << "time range has occupied slot" << RESET << endl;
            }
        }
        else if (choice == 2)
        {
            // Prompt for confirmation to delete reservation
            std::string c;
            cout << " are you sure? [y/n] : ";
            cin >> c;
            if (c[0] == 'y' || c[0] == 'Y')
                calendar.resetUUIDInCalendar(user);
            lm.DeviceCancelReserve(user, getName());
        }
        else if (choice == 3 && user.getIsManager())
        {
            calendar.resetAll();
        }
        else
            break;
    }
    calendar.write();
}
