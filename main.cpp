#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>

#include "items/ItemManager.h"
#include "items/Account.h"
#include "items/Calendar.h"
#include "users/User.h"

using namespace std;

const string version = "0.0.1";

int main(int argc, char *argv[])
{
    User u1(3, 20225167, "aaaaa", "aaaaa");
    Calendar c("title1");
    c.load();
    //c.markPeriodWithUUID(u1, 3, 7, 3, 9);
    c.write();
    c.print_calendar(u1);

    return 0;
}
