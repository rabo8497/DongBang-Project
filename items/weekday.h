#ifndef WEEKDAY_H
#define WEEKDAY_H

#include <string>
#include <iostream>
#include "../styles/colors.h"
using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::string;

class Weekday
{
    friend ostream &operator<<(ostream &os, Weekday wd);

private:
    string dayString;
    int day;
    int time;
    const char weekdays[7][4] = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"};

public:
    Weekday(string = "nil", int = -1);
    ~Weekday() = default;
    int getDay() { return day; }
    int getTime() { return time; }
    void input();
};

void Weekday::input()
{
    string ibuffer1, ibuffer2;
    while (true)
    {
        cout << " > ";
        cin >> ibuffer1 >> ibuffer2;

        bool isBufferValid = true;
        for (auto c : ibuffer2)
        {
            if (!isdigit(c))
            {
                isBufferValid = false;
                break;
            }
        }
        if (!isBufferValid) // user did not even inputted a number
        {
            std::cout << RED << "ERROR : " << RESET << "Input violates given format" << std::endl;
            continue;
        }
        else
        {
            dayString = ibuffer1;
            time = std::stoi(ibuffer2);
        }

        int i = 0;
        bool isDayValid = false;

        // weekday string check thingy
        for (i = 0; i < 7; i++)
        {
            int j;
            for (j = 0; j < dayString.length(); j++)
            {
                if (dayString[j] != weekdays[i][j])
                    break;
            }
            if (j == dayString.length())
            {
                isDayValid = true;
                break;
            }
        }

        if (isDayValid)
        {
            day = i;
            break;
        }
        else
        {
            std::cout << RED << "ERROR : " << RESET << "Input violates given format" << std::endl;
            continue;
        }
    }
}

ostream &operator<<(ostream &os, Weekday wd)
{
    return os << wd.dayString << ", " << wd.time;
}

Weekday::Weekday(std::string day, int time) : dayString(day), time(time)
{
    this->day = -1;
}

#endif