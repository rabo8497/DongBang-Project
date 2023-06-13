#include "Calendar.h"

Calendar::Calendar(std::string title) : week(7, std::vector<int>(24, Default_val)), title(title)
{
    interval = 10;
    saveLocation = ".\\dataBase\\calendar.txt";
}

void Calendar::write()
{
    // Check if the item is already in the calendar
    if (isItemInCalendar())
    {
        modifyFile(); // Call the modifyFile() function
        return;
    }
    std::ofstream outFile(saveLocation, std::ios_base::app); // Open file in append mode
    if (outFile.is_open())
    {
        outFile << title << "\n"; // Write the title to the file
        for (const auto &day : week)
        {
            for (const auto &hour : day)
            {
                outFile << hour << " "; // Write each hour of the day to the file
            }
            outFile << "\n"; // Write a new line after each day
        }
        for (int i = 0; i < interval - 8; i++)
        {
            outFile << "\n"; // Write empty lines at the end of the calendar
        }
        outFile.close(); // Close the file
    }
    else
    {
        std::cerr << "Unable to open file for writing.\n";
    }
}

void Calendar::load()
{
    // Check if the item is not in the calendar
    if (!isItemInCalendar())
    {
        std::cerr << "Unable to open file for writing.\n";
        return;
    }
    std::ifstream inFile(saveLocation);
    if (inFile.is_open())
    {
        std::string line;
        while (std::getline(inFile, line))
        {
            if (line == title)
            {
                for (auto &day : week)
                {
                    if (std::getline(inFile, line))
                    {
                        std::stringstream ss(line);
                        for (auto &hour : day)
                        {
                            ss >> hour; // Read each hour from the file and store it in the week vector
                        }
                    }
                }
                break;
            }
        }
        inFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for reading.\n";
    }
}

void Calendar::modifyFile()
{
    std::ifstream inFile(saveLocation);
    std::ofstream tempFile(".\\dataBase\\temp.txt");
    if (inFile.is_open() && tempFile.is_open())
    {
        std::string line;
        while (std::getline(inFile, line))
        {
            if (line == title)
            {
                tempFile << title << "\n"; // Write the title to the temporary file
                for (const auto &day : week)
                {
                    for (const auto &hour : day)
                    {
                        tempFile << hour << " "; // Write each hour of the day to the temporary file
                    }
                    tempFile << "\n"; // Write a new line after each day
                }
                for (int i = 0; i < 7; i++)
                {
                    std::getline(inFile, line); // Skip the lines for the previous calendar
                }
            }
            else
            {
                tempFile << line << "\n"; // Write the line to the temporary file
            }
        }
        inFile.close();
        tempFile.close();
        std::remove(saveLocation.c_str());                          // Remove the old calendar file
        std::rename(".\\dataBase\\temp.txt", saveLocation.c_str()); // Rename the temporary file to the calendar file
    }
    else
    {
        std::cerr << "Unable to open file.\n";
    }
}

bool Calendar::isItemInCalendar()
{
    std::ifstream inFile(saveLocation);
    if (inFile.is_open())
    {
        std::string line;
        int lineCount = 1;
        while (std::getline(inFile, line))
        {
            if (lineCount % 10 == 1 && line == title)
            {
                inFile.close();
                return true; // Return true if the title is found in the file
            }
            lineCount++;
        }
        inFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for reading.\n";
    }
    return false; // Return false if the title is not found in the file
}

bool Calendar::isSlotEmpty(int day, int hour)
{
    if (day < 0 || day >= week.size() || hour < 0 || hour >= week[0].size())
    {
        std::cerr << "Invalid day or hour.\n";
        return false;
    }
    return week[day][hour] == Default_val; // Check if the slot in the calendar is empty
}

bool Calendar::markPeriodWithUUID(User nowUser, int startDay, int startHour, int endDay, int endHour)
{
    int uuid = nowUser.getId();
    if (startDay < 0 || startDay >= week.size() || endDay < 0 || endDay >= week.size() ||
        startHour < 0 || startHour >= week[0].size() || endHour < 0 || endHour >= week[0].size() ||
        startDay > endDay || (startDay == endDay && startHour > endHour))
    {
        std::cerr << "Invalid time period.\n";
        return false;
    }
    for (int day = startDay; day <= endDay; day++)
    {
        for (int hour = (day == startDay ? startHour : 0); hour <= (day == endDay ? endHour : 23); hour++)
        {
            week[day][hour] = uuid; // Mark the period in the calendar with the UUID
        }
    }
    return true;
}

void Calendar::resetUUIDInCalendar(User nowUser)
{
    int uuid = nowUser.getId();
    for (auto &day : week)
    {
        for (auto &hour : day)
        {
            if (hour == uuid)
            {
                hour = Default_val; // Reset the UUID in the calendar for a specific user
            }
        }
    }
}

void Calendar::resetAll()
{
    for (auto &day : week)
    {
        for (auto &hour : day)
        {
            hour = Default_val; // Reset the entire calendar
        }
    }
}

void Calendar::print_calendar(User nowUser)
{
    const int totalWidth = 78;
    const int firstD = 4;
    const int secondD = 2;
    const int thirdD = 3;
    std::vector<std::string> days = {"mo", "tu", "we", "th", "fr", "se", "su"};
    std::cout << std::left << std::setfill('-') << std::setw(totalWidth) << "" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << "|" << std::left << std::setw(firstD) << " ";
    for (int i = 0; i < 24; i++)
    {
        std::cout << std::setw(secondD) << i << " "; // Print the hours of the day
    }
    std::cout << "|" << std::endl;
    int i = 0;
    for (const std::string &day : days)
    {
        std::cout << "|" << std::left << std::setw(firstD) << day;
        for (const int value : week[i])
        {
            if (value == -1)
                std::cout << std::left << std::setw(thirdD) << " "; // Print an empty slot
            else if (value == nowUser.getId())
                std::cout << std::left << std::setw(thirdD) << '*'; // Print '*' for the user's slots
            else
                std::cout << std::left << std::setw(thirdD) << 'v'; // Print 'v' for other user's slots
        }
        std::cout << "|" << std::endl;
        i += 1;
    }
    std::cout << std::left << std::setfill('-') << std::setw(totalWidth) << "" << std::endl;
    std::cout << std::setfill(' ');
}
