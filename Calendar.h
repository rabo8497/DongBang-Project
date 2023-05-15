#ifndef CALENDAR_H
#define CALENDAR_H

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "FileHandler.h"
#include "User.h"
#define Default_val -1

class Calendar : public FileHandler {
private:
    std::string title;
    std::vector<std::vector<int>> week;
public:
    Calendar(std::string title) {}
    void write();
    void load();
    void modifyFile();
    bool isItemInCalendar();
    bool isSlotEmpty(int day, int hour);
    void markPeriodWithUUID(User nowUser, int startDay, int startHour, int endDay, int endHour);
    void resetUUIDInCalendar(User nowUser);
    void resetAll();
    void print_calendar();
    
};

#endif
