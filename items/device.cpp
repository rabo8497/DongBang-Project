#include "Device.h"

Device::Device(std::string name, int id, bool isActive) : Item(name, id, isActive, DEVICE) {}
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