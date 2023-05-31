#ifndef WEEKDAY_H
#define WEEKDAY_H

#include <string>
#include <iostream>
using std::istream;
using std::ostream;
using std::string;

class Weekday
{
    friend istream &operator>>(istream &is, Weekday wd);
    friend ostream &operator<<(ostream &os, Weekday wd);

private:
    string dayString;
    int day;
    int time;
    const char *weekdays[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

public:
    Weekday(string = "nil", int = -1);
    ~Weekday() = default;
    int getDay() { return day; }
    int getTime() { return time; }
};

istream &operator>>(istream &is, Weekday wd)
{
    is >> wd.dayString >> wd.time;
    for (int i = 0; i < 7; i++)
    {
        bool isSame = true;
        for (int j = 0; j < wd.dayString.length(); j++)
        {
            if (wd.dayString[j] != wd.weekdays[i][j])
            {
                isSame = false;
                break;
            }
        }
        if (isSame)
        {
            wd.day = i;
            break;
        }
    }
    return is;
}

ostream &operator<<(ostream &os, Weekday wd)
{
    return os << wd.dayString << ", " << wd.time;
}

Weekday::Weekday(std::string day, int time) : dayString(day), time(time) {}

#endif