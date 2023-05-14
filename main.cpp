#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>

#include "items/itemManager.h"
#include "items/account.h"

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

int main(int argc, char *argv[]) // argc=인자 갯수, argv=인자들
{
    cout << "JiDongMot version " << version << " Starting..." << endl;

    // system("pause");

    ItemManager im;
    im.load();
    // im.showList();

    const int userid = 13; // 임의로 정한 값.

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
            }
        }
        else if (choice == 4)
            return 0;
    }

    return 0;
}
