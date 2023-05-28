#ifndef DEVICE_H
#define DEVICE_H

#include "Item.h"
#include "Calendar.h"
#include "../styles/prompter.h"
#include <string>
#include <vector>

const char *weekday[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

class Device : public Item
{
private:
    Calendar calendar;
    Prompter prompter;

    std::string opTitle = "Select operation";
    std::vector<std::string> opList = {
        "Make Reservation",
        "Cancel Existing Reservation",
    };

public:
    Device(std::string = "unknown device", int = -1, bool = false); // 순서대로 이름, id.
    void printInfo() override;                                      // 자신의 정보를 출력하는 함수.
    void prompt(const User &);
};

#endif