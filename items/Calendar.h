#ifndef CALENDAR_H
#define CALENDAR_H

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "../FileHandler.h"   // Include directive for the FileHandler class
#include "../users/User.h"    // Include directive for the User class
#include "../styles/colors.h" // Include directive for the colors header file

#define Default_val -1 // Macro definition for a default value

class Calendar : public FileHandler
{
private:
    std::string title;                  // Title of the calendar
    std::vector<std::vector<int>> week; // 2D vector representing the calendar week

public:
    Calendar(std::string title);                                                                 // Constructor for the Calendar class
    void write();                                                                                // Function to write the calendar to a file
    void load();                                                                                 // Function to load the calendar from a file
    void modifyFile();                                                                           // Function to modify the calendar file
    bool isItemInCalendar();                                                                     // Function to check if an item is in the calendar
    bool isSlotEmpty(int day, int hour);                                                         // Function to check if a slot in the calendar is empty
    bool markPeriodWithUUID(User nowUser, int startDay, int startHour, int endDay, int endHour); // Function to mark a period in the calendar with a UUID
    void resetUUIDInCalendar(User nowUser);                                                      // Function to reset the UUID in the calendar for a specific user
    void resetAll();                                                                             // Function to reset the entire calendar
    void print_calendar(User nowUser);                                                           // Function to print the calendar
};

#endif
