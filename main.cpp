#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "items/itemManager.h"
#include "items/account.h"

using namespace std;

const string version = "0.0.1";

int main(int argc, char *argv[]) // argc=인자 갯수, argv=인자들
{
    cout << "JiDongMot version" << version << "Starting..." << endl;

    system("pause");
    /*ItemManager im;
    Account testAccount = Account(string("laftel"), string("mikan"), 13);
    im.addItem(&testAccount);
    im.showList();*/

    return 0;
}
