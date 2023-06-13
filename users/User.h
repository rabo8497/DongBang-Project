#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "../books/Book.h"
#include "../styles/colors.h"

class User
{
public:
    User() {} // Default constructor

    // Overloaded constructor with parameters
    User(int uuid, int studentNumber, std::string nickname, std::string password, bool isEru = false, bool isManager = false, int lendBookN = 0);

    // Getter functions
    int getId() const;               // Returns the user ID (uuid)
    int getStudentNumber() const;    // Returns the student number
    std::string getNickName() const; // Returns the nickname
    bool getIsEru() const;           // Returns whether the user is Eru or not
    bool getIsManager() const;       // Returns whether the user is a manager or not
    int getLendBookNum() const;      // Returns the number of books borrowed by the user
    int getLendBookMaxNum() const;   // Returns the maximum number of books that can be borrowed

    // Setter functions with validation
    void setStudentNumber(int newStudentNumber);                           // Sets the student number with validation
    void setNickName(std::string newNickName);                             // Sets the nickname with validation
    void setPassward(std::string originPassward, std::string newPassward); // Sets the password with validation, requires the original password for verification
    void setPassward(std::string newPassward);                             // Sets the password without verification
    void setIsEru(bool newIsEru);                                          // Sets whether the user is Eru or not

    bool isValidPassword(std::string validPassword); // Validates if the provided password is correct

    void lendBook();   // Increases the number of borrowed books by 1, validates if it exceeds the maximum value
    void returnBook(); // Decreases the number of borrowed books by 1, validates if it becomes less than 0

private:
    int uuid;             // User ID
    int studentNumber;    // Student ID
    std::string nickname; // Nickname (ID)
    std::string password; // Password
    bool isEru;           // Indicates whether the user is Eru or not (default: false)
    bool isManager;       // Indicates whether the user is a manager or not (default: false)
    int lendBookNum;      // Number of borrowed books
    int lendBookMaxNum;   // Maximum number of books that can be borrowed
};

#endif
