#include <iostream>
#include <cctype>
#include "User.h"

// constructor with parameters
User::User(const int newuuid, const int newstudentNumber, std::string newnickname, std::string newpassward, bool newisEru, bool newisManager, int lendBookN)
    : isEru(newisEru), isManager(newisManager)
{
    lendBookNum = lendBookN;
    lendBookMaxNum = 3;
    setStudentNumber(newstudentNumber); // Set the student number with validation
    setNickName(newnickname);           // Set the nickname with validation
    setPassward(newpassward);           // Set the password with validation
    if (studentNumber != newstudentNumber || nickname != newnickname || password != newpassward)
    {
        uuid = -2;
    }
    else
    {
        uuid = newuuid;
    }
};

// Getter function to return the user ID (uuid)
int User::getId() const
{
    return uuid;
}

// Getter function to return the student number
int User::getStudentNumber() const
{
    return studentNumber;
}

// Getter function to return the number of books borrowed by the user
int User::getLendBookNum() const
{
    return lendBookNum;
}

// Getter function to return the nickname
std::string User::getNickName() const
{
    return nickname;
}

// Getter function to check if the user is Eru
bool User::getIsEru() const
{
    return isEru;
}

// Getter function to check if the user is a manager
bool User::getIsManager() const
{
    return isManager;
}

// Getter function to return the maximum number of books that can be borrowed
int User::getLendBookMaxNum() const
{
    return lendBookMaxNum;
}

// Setter function to set the student number with validation
void User::setStudentNumber(int newStudentNumber)
{
    if (newStudentNumber > 21000000 || newStudentNumber < 10000000)
    {
        std::cout << RED << "This is an incorrect student number: " << newStudentNumber << RESET << std::endl;
        return;
    }
    std::cout << YELLOW << "Student number successfully set." << RESET << std::endl;
    studentNumber = newStudentNumber;
}

// Setter function to set the nickname with validation
void User::setNickName(std::string newNickName)
{
    if (newNickName.length() < 5)
    {
        std::cout << RED << "Nickname should be at least 5 characters long." << RESET << std::endl;
        return;
    }

    for (char c : newNickName)
    {
        if (!std::isalnum(c))
        {
            std::cout << RED << "Nickname should only contain letters and numbers." << RESET << std::endl;
            return;
        }
    }
    nickname = newNickName;
    std::cout << YELLOW << "Nickname successfully set." << RESET << std::endl;
}

// Setter function to set the password with validation, requires the original password for verification
void User::setPassward(std::string originPassward, std::string newPassward)
{
    if (originPassward != password)
    {
        std::cout << RED << "Incorrect password" << RESET << std::endl;
        return;
    }
    if (newPassward.length() < 5)
    {
        std::cout << RED << "Password should be at least 5 characters long." << RESET << std::endl;
        return;
    }
    for (char c : newPassward)
    {
        if (!std::isalnum(c))
        {
            std::cout << RED << "Password should only contain letters and numbers." << RESET << std::endl;
            return;
        }
    }
    password = newPassward;
    std::cout << YELLOW << "Password successfully set." << RESET << std::endl;
}

// Overloaded setter function to set the password with validation
void User::setPassward(std::string newPassward)
{
    if (newPassward.length() < 5)
    {
        std::cout << RED << "Password should be at least 5 characters long." << RESET << std::endl;
        return;
    }
    for (char c : newPassward)
    {
        if (!std::isalnum(c))
        {
            std::cout << RED << "Password should only contain letters and numbers." << RESET << std::endl;
            return;
        }
    }
    password = newPassward;
    std::cout << YELLOW << "Password successfully set." << RESET << std::endl;
}

// Function to check if the provided password matches the user's password
bool User::isValidPassword(std::string validPassword)
{
    return password == validPassword;
}

// Function to simulate borrowing a book
void User::lendBook()
{
    lendBookNum += 1;
    if (lendBookNum > lendBookMaxNum)
    {
        lendBookNum -= 1;
        std::cout << RED << "Cannot lend more than " << lendBookMaxNum << " books." << RESET << std::endl;
        return;
    }
    std::cout << YELLOW << "Book successfully borrowed." << RESET << std::endl;
}

// Function to simulate returning a book
void User::returnBook()
{
    lendBookNum -= 1;
    if (lendBookNum < 0)
    {
        lendBookNum += 1;
        std::cout << RED << "You did not borrow a book." << RESET << std::endl;
        return;
    }
    std::cout << YELLOW << "Book successfully returned." << RESET << std::endl;
}
