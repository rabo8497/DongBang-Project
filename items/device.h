#ifndef DEVICE_H
#define DEVICE_H

#include "item.h"

class Device : public Item
{
public:
    Device(std::string = "unknown device", int = -1);
    void printInfo() override;
};

#endif