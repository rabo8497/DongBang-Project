#include "Calendar.h"

Calendar::Calendar(std::string title) : week(7, std::vector<int>(24, Default_val)), title(title) {
    interval = 10;
    saveLocation = "../dataBase/calendar.txt";
}

void Calendar::write() { 
    if (isItemInCalendar()) {
        modifyFile();
        return;
    }
    std::ofstream outFile(saveLocation, std::ios_base::app);  // Open file in append mode
    if (outFile.is_open()) {
        outFile << title << "\n";
        for (const auto &day : week) {
            for (const auto &hour : day) {
                outFile << hour << " ";
            }
            outFile << "\n";
        }
        for (int i = 0; i < interval-8; i++) {
            outFile << "\n";
        }
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing.\n";
    }
}

void Calendar::load() {
    if (!isItemInCalendar()) {
        std::cerr << "Unable to open file for writing.\n";
        return;
    }
    std::ifstream inFile(saveLocation);
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (line == title) {
                for (auto &day : week) {
                    if (std::getline(inFile, line)) {
                        std::stringstream ss(line);
                        for (auto &hour : day) {
                            ss >> hour;
                        }
                    }
                }
                break;
            }
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading.\n";
    }
}

void Calendar::modifyFile() {
    std::ifstream inFile(saveLocation);
    std::ofstream tempFile("../dataBase/temp.txt");
    if (inFile.is_open() && tempFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (line == title) {
                tempFile << title << "\n";
                for (const auto &day : week) {
                    for (const auto &hour : day) {
                        tempFile << hour << " ";
                    }
                    tempFile << "\n";
                }
                for (int i = 0; i < 7; i++) {
                    std::getline(inFile, line);
                }
            } else {
                tempFile << line << "\n";
            }
        }
        inFile.close();
        tempFile.close();
        std::remove(saveLocation.c_str());
        std::rename("../dataBase/temp.txt", saveLocation.c_str());
    } else {
        std::cerr << "Unable to open file.\n";
    }
}

bool Calendar::isItemInCalendar() {
    std::ifstream inFile(saveLocation);
    if (inFile.is_open()) {
        std::string line;
        int lineCount = 1;
        while (std::getline(inFile, line)) {
            if (lineCount % 10 == 1 && line == title) {
                inFile.close();
                return true;
            }
            lineCount++;
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading.\n";
    }
    return false;
}

bool Calendar::isSlotEmpty(int day, int hour) {
    if (day < 0 || day >= week.size() || hour < 0 || hour >= week[0].size()) {
        std::cerr << "Invalid day or hour.\n";
        return false;
    }
    return week[day][hour] == Default_val;
}

void Calendar::markPeriodWithUUID(User nowUser, int startDay, int startHour, int endDay, int endHour) {
    int uuid = nowUser.getId();
    if (startDay < 0 || startDay >= week.size() || endDay < 0 || endDay >= week.size() ||
        startHour < 0 || startHour >= week[0].size() || endHour < 0 || endHour >= week[0].size() ||
        startDay > endDay || (startDay == endDay && startHour > endHour)) {
        std::cerr << "Invalid time period.\n";
        return;
    }
    for (int day = startDay; day <= endDay; day++) {
        for (int hour = (day == startDay ? startHour : 0); hour <= (day == endDay ? endHour : 23); hour++) {
            week[day][hour] = uuid;
        }
    }
}

void Calendar::resetUUIDInCalendar(User nowUser) {
    int uuid = nowUser.getId();
    for (auto &day : week) {
        for (auto &hour : day) {
            if (hour == uuid) {
                hour = Default_val;
            }
        }
    }
}

void Calendar::resetAll() {
    for (auto &day : week) {
        for (auto &hour : day) {
            hour = Default_val;
        }
    }
}

void Calendar::print_calendar() {
    std::cout << title << "\n";
    for (const auto &day : week) {
        for (const auto &hour : day) {
            std::cout << hour << " ";
        }
        std::cout << "\n";
    }
    for (int i = 0; i < interval-8; i++) {
        std::cout << "\n";
    }
}