#include "Device.h"
#include <iostream>
#include <iomanip>
using namespace std;

Device::Device(std::string name, int id, bool isActive)
    : Item(name, id, isActive, DEVICE), calendar(Calendar(name))
{
    calendar.load();
}

void Device::printInfo()
{
    std::cout << getName();
    if (active())
    {
        std::cout << " ( ON ) ";
    }
    else
    {
        std::cout << " ( OFF ) ";
    }
}