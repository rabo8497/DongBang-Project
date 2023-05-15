#ifndef DEVICE_H
#define DEVICE_H

#include "item.h"

class Device : public Item
{
public:
    Device(std::string = "unknown device", int = -1); // 순서대로 이름, id.
    void printInfo() override;                        // 자신의 정보를 출력하는 함수.
};

#endif