#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <string>
#include <iostream>

class FileHandler
{
public:
    FileHandler(std::string newSaveLocation = "none", int newInterval = 0)
    {
        saveLocation = newSaveLocation;
        interval = newInterval;
    } // Constructor to initialize the saveLocation and interval variables

    // Function to find the ID from an item
    int findIdFromItem();

    // Function to load data from the text file
    void load();

    // Function to write data to the text file
    void write();

    // Function to modify data in the text file
    void modifyFile();

    // Function to delete data from the text file
    void deleteFile();

    // Function to get the latest ID from the text file
    int getLatestId()
    {
        int latestId = -1; // If -1 is returned, it means no data is stored
        std::ifstream inFile(saveLocation);

        if (!inFile)
        {
            std::cout << "Cannot open user.txt file" << std::endl;
            return -2; // If -2 is returned, it means there was an error opening the file
        }

        std::string line;
        int lineNum = 0;
        while (std::getline(inFile, line))
        {
            lineNum += 1;
            if (lineNum % interval == 1)
            {
                latestId = std::stoi(line);
            }
        }
        return latestId; // If retrieved successfully, the latest UUID is returned
    }

protected:
    std::fstream file;
    std::string saveLocation; // The location where data is saved
    int interval;             // The number of lines allocated for storing each data entry in the text file
};

#endif
