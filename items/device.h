#ifndef DEVICE_H
#define DEVICE_H

#include "Item.h"
#include "Calendar.h"
#include <string>
#include <vector>
#include "../styles/colors.h"
class LogManager; 
#include "../logManager.h"

class Device : public Item
{
private:
    Calendar calendar;

public:
    Device(std::string = "unknown device", int = -1, bool = false); // 순서대로 이름, id.
    ~Device();
    void printInfo(User &) override; // 자신의 정보를 출력하는 함수.
    void prompt(LogManager &, const User &);
    Calendar &getCalendar();
};

#endif