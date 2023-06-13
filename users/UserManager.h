#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <iostream>
#include "../fileHandler.h"
#include "User.h"

class UserManager : public FileHandler
{
public:
    UserManager();
    bool getIsSignIn() const; // Check if logged in
    User &getLoginedUser();   // Returns the logged-in user if needed elsewhere (e.g., to identify the user who wrote a comment)

    int findIdFromItem(std::string);                        // Returns the corresponding UUID when given a nickname
    std::string findNickFromId(int);                        // Returns the nickname when given a UUID
    void signUp(int, std::string, std::string, bool, bool); // Sign up and add user information to a text file
    void signIn(std::string, std::string);                  // Log in
    void signOut();                                         // Log out

    // Below is a function inherited from FileHandler and overloaded
    void load(int);                // Load a user with a specific UUID from a text file and store it in 'nowUser'
    void write(User, std::string); // Save the user to a text file
    void modifyFile();             // Modify the text file
    void deleteFile(int);          // Delete the text file for a given UUID

private:
    int latestId;  // Stores the most recent UUID
    bool isSignIn; // Stores whether a user is currently logged in (default: false)
    User nowUser;  // Represents the currently logged-in user. Initially empty, and gets updated when a user logs in.
};

#endif
