#include "UserManager.h"
#include "User.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>

// Constructor for the UserManager class.
UserManager::UserManager() : FileHandler(".\\dataBase\\user.txt", 10)
{
    isSignIn = false;
    latestId = getLatestId();
}

// Function to check if a user is signed in.
bool UserManager::getIsSignIn() const
{
    return isSignIn;
}

// Function to get the logged-in user.
User &UserManager::getLoginedUser()
{
    if (getIsSignIn())
    {
        return nowUser;
    }
    else
    {
        std::cout << RED << "not logined. You have to login to use this function" << RESET << std::endl;
        return nowUser; // Return an empty user object
    }
}

// Function to write a new user and their password to the user data file.
void UserManager::write(User newUser, std::string password)
{
    // Extract user attributes from the newUser object
    int studentNumber = newUser.getStudentNumber();
    bool isEru = newUser.getIsEru();
    bool isManager = newUser.getIsManager();
    int lendBookNum = newUser.getLendBookNum();
    std::string nickname = newUser.getNickName();
    std::string newUUID = std::to_string(latestId + 1);
    std::string studentNumberStr = std::to_string(studentNumber);
    std::string isEruStr = isEru ? "true" : "false";
    std::string isManagerStr = isManager ? "true" : "false";
    std::string lendBookNumStr = std::to_string(lendBookNum);

    // Create a string containing the user data in the required format
    std::string saveData = newUUID + "\n" + studentNumberStr + "\n" + nickname + "\n" + password + "\n" + isEruStr + "\n" + isManagerStr + "\n" + lendBookNumStr + "\n" + "\n" + "\n";

    std::ofstream outFile(saveLocation, std::ios::app);
    if (!outFile)
    {
        // If the file cannot be opened, print an error message and return
        std::cout << RED << "cannot open file" << RESET << std::endl;
        return;
    }

    // Write the user data to the file and close it
    outFile << saveData << std::endl;
    outFile.close();
}

// Function to find the ID of a user based on their nickname.
// Returns the ID of the user if found, -1 otherwise.
int UserManager::findIdFromItem(std::string findNickName)
{
    int findId = -1;
    int nowId = -1;
    std::ifstream inFile(saveLocation);
    if (!inFile)
    {
        // If the file cannot be opened, print an error message and return
        std::cout << RED << "cannot open user.txt file" << RESET << std::endl;
        return -1;
    }
    std::string line;
    int lineNum = 0;
    while (std::getline(inFile, line))
    {
        lineNum += 1;
        if (lineNum % interval == 1)
        {
            nowId = std::stoi(line);
        }
        if (lineNum % interval == 3)
        {
            if (line == findNickName)
            {
                findId = nowId;
            }
        }
    }
    inFile.close();
    return findId;
}

// Function to find the nickname of a user based on their ID.
// Returns the nickname of the user if found, an empty string otherwise.
std::string UserManager::findNickFromId(int findId)
{
    bool isFind = false;
    std::ifstream inFile(saveLocation);
    if (!inFile)
    {
        // If the file cannot be opened, print an error message and return an empty string
        std::cout << RED << "cannot open user.txt file" << RESET << std::endl;
        return "";
    }
    std::string line;
    int lineNum = 0;
    int count = 1;
    while (std::getline(inFile, line))
    {
        lineNum += 1;
        if (count == 0)
        {
            return line;
        }
        else if (isFind)
        {
            count -= 1;
        }
        if (lineNum % interval == 1)
        {
            if (std::stoi(line) == findId)
            {
                isFind = true;
            }
            else
            {
                isFind = false;
            }
        }
    }
    return "";
}

void UserManager::load(int findId)
{
    std::cout << YELLOW << "----------load start----------" << std::endl;

    bool isFind = false;
    std::string findData = "";
    std::ifstream inFile(saveLocation);
    if (!inFile)
    {
        // If the file cannot be opened, print an error message and return
        std::cout << RED << "cannot open user.txt file" << RESET << std::endl;
        std::cout << YELLOW << "----------load end----------" << RESET << std::endl;
        return;
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(inFile, line))
    {
        lineNum += 1;
        if (lineNum % interval == 1)
        {
            if (std::stoi(line) == findId)
            {
                isFind = true;
            }
            else
            {
                isFind = false;
            }
        }
        if (isFind)
        {
            findData += line;
            findData += '*';
        }
    }

    std::stringstream ss(findData);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(ss, token, '*'))
    {
        tokens.push_back(token);
    }

    // Convert each part to the appropriate data type
    int val1 = std::stoi(tokens[0]);
    int val2 = std::stoi(tokens[1]);
    std::string val3 = tokens[2];
    std::string val4 = tokens[3];
    bool val5 = (tokens[4] == "true" || tokens[4] == "True") ? true : false;
    bool val6 = (tokens[5] == "true" || tokens[5] == "True") ? true : false;
    int val7 = std::stoi(tokens[6]);

    inFile.close();

    // Create the User object with the extracted values and assign it to nowUser
    nowUser = User(val1, val2, val3, val4, val5, val6, val7);

    std::cout << YELLOW << "----------load end----------" << RESET << std::endl;
}

void UserManager::modifyFile()
{
    User modifiedUser = nowUser;
    std::ifstream inFile(saveLocation);
    std::ofstream outFile(".\\dataBase\\usertemp.txt");
    std::string findIdStr = std::to_string(modifiedUser.getId());
    int findModifiyBookNum = -1;

    if (!inFile || !outFile)
    {
        // If the file cannot be opened, print an error message and return
        std::cout << RED << "cannot open user.txt file" << RESET << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(inFile, line))
    {
        lineNumber += 1;
        if (lineNumber == findModifiyBookNum)
        {
            outFile << modifiedUser.getLendBookNum() << std::endl;
        }
        else if (lineNumber % interval == 1 && line == findIdStr)
        {
            outFile << findIdStr << std::endl;
            findModifiyBookNum = lineNumber + 6; // Book number is stored 6 lines after the ID
        }
        else
        {
            outFile << line << std::endl;
        }
    }

    inFile.close();
    outFile.close();

    std::remove(saveLocation.c_str()); // The function expects a C-style string argument, so we need to force a type conversion from std::string to const char*
    std::rename(".\\dataBase\\usertemp.txt", saveLocation.c_str());
}

void UserManager::deleteFile(int uuid)
{
    // Check if the current user is a manager
    if (!nowUser.getIsManager())
    {
        std::cout << std::endl
                  << RED << "You are not a manager." << RESET << std::endl;
        return;
    }

    std::ifstream inFile(saveLocation);
    std::ofstream outFile(".\\dataBase\\usertemp.txt");
    int findModifiyBookNum = -1;

    if (!inFile || !outFile)
    {
        // If the file cannot be opened, print an error message and return
        std::cout << RED << "Cannot open user.txt file" << RESET << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 0;
    int deleteNum = 0;
    while (std::getline(inFile, line))
    {
        lineNumber += 1;
        if (deleteNum > 0)
        {
            deleteNum -= 1;
            continue;
        }
        else if (lineNumber % interval == 1)
        {
            if (uuid == std::stoi(line))
            {
                deleteNum = interval - 1;
            }
            else
            {
                outFile << line << std::endl;
            }
        }
        else
        {
            outFile << line << std::endl;
        }
    }

    inFile.close();
    outFile.close();

    std::remove(saveLocation.c_str());                              // Remove the original file
    std::rename(".\\dataBase\\usertemp.txt", saveLocation.c_str()); // Rename the temporary file

    // Detailed comments are not necessary for the following functions as their functionality is straightforward.
}

void UserManager::signUp(int studentNumber, std::string nickname, std::string password, bool isEru, bool isManager)
{
    // Check if the nickname already exists
    int getId = findIdFromItem(nickname);
    if (getId != -1)
    {
        std::cout << RED << "[Signup failed]" << std::endl;
        std::cout << RED << "This nickname already exists. Please use a different nickname." << RESET << std::endl
                  << std::endl;
        return;
    }

    // Get the latest user ID
    latestId = getLatestId();

    std::cout << YELLOW << "----------Save Start----------" << std::endl;
    User newUser(latestId + 1, studentNumber, nickname, password, isEru, isManager);
    std::cout << YELLOW << "----------Save End----------" << RESET << std::endl;

    if (newUser.getId() == -2)
    {
        std::cout << std::endl
                  << RED << "[Signup failed]" << std::endl
                  << "Received an unexpected value. Please rewrite your information." << RESET << std::endl
                  << std::endl;
    }
    else
    {
        write(newUser, password);
        latestId += 1;
        std::cout << std::endl
                  << GREEN << "[Signup successful!]" << std::endl
                  << "You can now log in." << RESET << std::endl
                  << std::endl;
    }
}

void UserManager::signIn(std::string inputNickName, std::string inputPassword)
{
    // Find the user ID from the given nickname
    int getId = findIdFromItem(inputNickName);
    if (getId == -1)
    {
        std::cout << std::endl
                  << RED << "[Login failed!]" << std::endl
                  << "Invalid nickname." << RESET << std::endl
                  << std::endl;
        return;
    }

    // Load the user data for the given ID
    load(getId);

    if (nowUser.isValidPassword(inputPassword))
    {
        std::cout << std::endl
                  << GREEN << "[Login successful!]" << RESET << std::endl
                  << std::endl;
        isSignIn = true;
    }
    else
    {
        nowUser = User();
        std::cout << std::endl
                  << RED << "[Login failed!]" << std::endl
                  << "Invalid password." << RESET << std::endl
                  << std::endl;
    }
}

void UserManager::signOut()
{
    nowUser = User();
    isSignIn = false;
    std::cout << std::endl
              << GREEN << "[Logout successful!]" << RESET << std::endl
              << std::endl;
}
