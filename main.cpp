#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Calendar.h"
#include "User.h"

using namespace std;

const string version = "0.0.1";

int main(int argc, char *argv[]) 
{
    Calendar c("title1");
    User u1(1, 20225167, "rabo8497", "123456");
    User u2(2, 20225168, "rabo84972", "12325");
    c.load();
    c.resetAll();
    c.write();

    return 0;
}

