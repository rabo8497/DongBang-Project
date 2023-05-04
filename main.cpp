#pragma once // include guard

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "user.h"
#include "userManager.h"
using namespace std;

const string version = "0.0.1";

int main(int argc, char *argv[]) // argc=인자 갯수, argv=인자들
{
    UserManager manage;
    manage.signUp(20225167, "rabo8497", "aaaaa", true, false);
}
