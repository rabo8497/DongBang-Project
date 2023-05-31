#ifndef WEEKDAY_H
#define WEEKDAY_H

#include <string>
#include <iostream>
using std::cin;
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
    cin >> dayString >> time;

    for (int i = 0; i < 7; i++)
    {
        bool isValid = true;
        for (int j = 0; j < dayString.length(); j++)
        {
            char c = dayString[j];
            if (c >= 'A' && c <= 'Z')
                c -= 'A' - 'a';
            if (c != weekdays[i][j])
            {
                isValid = false;
                break;
            }
        }
        if (isValid)
        {
            day = i;
            break;
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