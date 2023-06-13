#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "../styles/colors.h"
#include "../FileHandler.h"
#include "../users/User.h"
#include "../users/UserManager.h"
#include "../styles/colors.h"

class MessageManager : public FileHandler
{
private:
    int fromId;                                     // ID of the user associated with this MessageManager
    std::vector<std::vector<std::string>> messages; // 2D vector to store the user's messages

public:
    // Default constructor for the MessageManager class
    MessageManager(){};

    // Constructor for the MessageManager class that initializes the fromId
    MessageManager(int);

    // Function to write a message from the user
    bool write(int, std::string, std::string);

    // Function to load the user's messages from a file
    void load();

    // Function to print the user's messages to the console
    bool print_messages(UserManager &, int &);

    // Function to open a specific message for the user
    void open_message(UserManager &, int);
};

#endif
