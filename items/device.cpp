#include "device.h"

Device::Device(std::string name, int id) : Item(name, id, DEVICE) {}
void Device::printInfo()
{
    std::cout << getName();
    if (active())
    {
        std::cout << " ( 사용 가능 ) ";
    }
    else
    {
        std::cout << " ( 사용 중 ) ";
    }
}