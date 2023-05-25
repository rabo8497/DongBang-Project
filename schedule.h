// a silly pseudo-schedule table class file. used some structures.
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

struct Schedule
{
    bool isReserved;
    int userId;
};

typedef struct Schedule schedule;

schedule scheduleTable[7][24];

void fillSchedule(int day, int start, int end, int id)
{
    for (int j = start; j <= end; j++)
    {
        if (scheduleTable[day][j].isReserved && (scheduleTable[day][j].userId != id))
        {
            cout << " ERROR : permission denied" << endl;
            system("pause");
            return;
        }
    }
    for (int j = start; j <= end; j++)
    {
        scheduleTable[day][j] = {true, id};
    }
}

void cancelSchedule(int day, int start, int end, int id)
{
    for (int j = start; j <= end; j++)
    {
        if (scheduleTable[day][j].isReserved && (scheduleTable[day][j].userId != id))
        {
            cout << " ERROR : permission denied" << endl;
            system("pause");
            return;
        }
    }
    for (int j = start; j <= end; j++)
    {
        scheduleTable[day][j] = {false, -1};
    }
}

void printSchedule(int id)
{
    char weekdays[] = {"MoTuWeThFrSaSu"};

    cout << "   ";
    for (int i = 0; i < 24; i++)
        cout << setw(3) << right << i;
    cout << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << left << weekdays[2 * i] << weekdays[2 * i + 1] << " ";
        for (int j = 0; j < 24; j++)
        {
            char sign = ' ';
            if (scheduleTable[i][j].isReserved)
            {
                if (scheduleTable[i][j].userId == id)
                    sign = '*';
                else
                    sign = 'v';
            }
            cout << setw(3) << right << sign;
        }
        cout << endl;
    }
}