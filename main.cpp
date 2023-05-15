#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>

#include "items/itemManager.h"
#include "items/account.h"
#include "schedule.h"

using namespace std;

const string version = "0.0.1";

int start()
{
    cout << setw(29) << "What do you want to do" << setw(11) << " " << endl
         << setw(40) << setfill('-') << "-" << endl
         << setfill(' ')
         << "|" << setw(38) << left << " 1) Book-related Function"
         << "|\n"
         << "|" << setw(38) << left << " 2) public account-related function"
         << "|\n"
         << "|" << setw(38) << left << " 3) Reservation of items"
         << "|\n"
         << "|" << setw(38) << left << " 4) exit"
         << "|\n"
         << setw(40) << setfill('-') << "-" << endl
         << setfill(' ') << "> ";
    int input;
    cin >> input;
    return input;
}

int accountSelect(ItemManager &im)
{
    cout << setw(22) << right << "Select Account" << endl
         << setw(30) << setfill('-') << "-" << setfill(' ') << endl;
    im.showList(ACCOUNT, true);
    cout << setw(30) << setfill('-') << "-" << setfill(' ') << endl
         << "( back : 0 ) > ";
    int input;
    cin >> input;
    return input;
}

int deviceSelect(ItemManager &im)
{
    cout << setw(21) << right << "Select Account" << endl
         << setw(30) << setfill('-') << "-" << setfill(' ') << endl;
    im.showList(DEVICE, true);
    cout << setw(30) << setfill('-') << "-" << setfill(' ') << endl
         << "( back : 0 ) > ";
    int input;
    cin >> input;
    return input;
}

void initSchedule()
{
    fillSchedule(0, 1, 6, 3);
    fillSchedule(1, 5, 8, 7);
    fillSchedule(5, 10, 12, 26);
}

int devOperSelect()
{
    cout << "1. Make Reservation" << endl
         << "2. Cancel Existing Reservation" << endl
         << " ( back : 0 ) > ";
    int input;
    cin >> input;
    return input;
}

int main(int argc, char *argv[]) // argc=인자 갯수, argv=인자들
{
    cout << "JiDongMot version " << version << " Starting..." << endl;

    // system("pause");

    ItemManager im;
    im.load();
    // im.showList();

    const int userid = 13; // 임의로 정한 값.
    initSchedule();

    while (true)
    {
        int choice = start();
        if (choice == 2)
        {
            while (true)
            {
                int achoice = accountSelect(im);
                if (achoice == 0)
                    break;
                Account *ac = dynamic_cast<Account *>(im.getItem(achoice));
                if (ac->active())
                {
                    if (ac->getcontrollerId() != userid)
                    {
                        cout << " ERROR : permission denied" << endl;
                        system("pause");
                        continue;
                    }
                }
                ac->toggleState();
                ac->setcontrollerId(userid);
            }
        }
        else if (choice == 3)
        {
            while (true)
            {
                int dchoice = deviceSelect(im);
                if (dchoice == 0)
                    break;
                while (true)
                {
                    printSchedule(userid);
                    int opChoice = devOperSelect();
                    if (opChoice == 0)
                        break;
                    else if (opChoice == 1)
                    {
                        std::string day;
                        int start, end;
                        cout << " enter time range (exit : type 'exit') > ";
                        cin >> day;
                        if (day == "exit")
                            continue;
                        else
                        {
                            cin >> start >> end;
                            int iday = -1;
                            if (day == "Mo")
                                iday = 0;
                            if (day == "Tu")
                                iday = 1;
                            if (day == "We")
                                iday = 2;
                            if (day == "Th")
                                iday = 3;
                            if (day == "Fr")
                                iday = 4;
                            if (day == "Sa")
                                iday = 5;
                            if (day == "Su")
                                iday = 6;
                            fillSchedule(iday, start, end, userid);
                        }
                    }
                    else if (opChoice == 2)
                    {
                        std::string day;
                        int start, end;
                        cout << " enter time range (exit : type 'exit') > ";
                        cin >> day;
                        if (day == "exit")
                            continue;

                        else
                        {
                            cin >> start >> end;
                            int iday = -1;
                            if (day == "Mo")
                                iday = 0;
                            if (day == "Tu")
                                iday = 1;
                            if (day == "We")
                                iday = 2;
                            if (day == "Th")
                                iday = 3;
                            if (day == "Fr")
                                iday = 4;
                            if (day == "Sa")
                                iday = 5;
                            if (day == "Su")
                                iday = 6;
                            cancelSchedule(iday, start, end, userid);
                        }
                    }
                }
            }
        }
        else if (choice == 4)
            return 0;
    }

    return 0;
}
