#include <iostream>
#include <cctype>
#include "User.h"

#define RESET   "\033[0m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

User::User(const int newuuid, const int newstudentNumber, std::string newnickname, std::string newpassward, bool newisEru, bool newisManager, int lendBookN) 
: isEru(newisEru), isManager(newisManager) 
{
    lendBookNum = lendBookN;
    lendBookMaxNum = 3;
    setStudentNumber(newstudentNumber);
    setNickName(newnickname);
    setPassward(newpassward);
    if (studentNumber != newstudentNumber || nickname != newnickname || passward != newpassward) {
        uuid = -2;
    } else {
        uuid = newuuid;
    }
};

int User::getId() const {
    return uuid;
}

int User::getStudentNumber() const {
    return studentNumber;
}

int User::getLendBookNum() const {
    return lendBookNum;
}

std::string User::getNickName() const {
    return nickname;
}

bool User::getIsEru() const {
    return isEru;
}

bool User::getIsManager() const {
    return isManager;
}

void User::setStudentNumber(int newStudentNumber) {
    if (newStudentNumber > 21000000 || newStudentNumber < 10000000) {
        std::cerr << RED << "this is wrong student number." << newStudentNumber << RESET << std::endl;
        return;
    }
    std::cout << YELLOW << "student number successfully set." << RESET << std::endl;
    studentNumber = newStudentNumber;
}

void User::setNickName(std::string newNickName) {
    if (newNickName.length() < 5) {
        std::cerr << RED << "Nickname should be at least 5 characters long." << RESET << std::endl;
        return;
    }

    for (char c : newNickName) {
        if (!std::isalnum(c)) {
            std::cerr << RED << "Nickname should only contain letters and numbers." << RESET << std::endl;
            return;
        }
    }
    nickname = newNickName;
    std::cout << YELLOW << "Nickname successfully set." << RESET << std::endl;
}

void User::setPassward(std::string originPassward, std::string newPassward) {
    if (originPassward != passward) {
        std::cerr << RED << "incorrect passward" << RESET << std::endl;
        return;
    }
    if (newPassward.length() < 5) {
        std::cerr << RED << "Password should be at least 5 characters long." << RESET << std::endl;
        return;
    }
    for (char c : newPassward) {
        if (!std::isalnum(c)) {
            std::cerr << RED << "Passward should only contain letters and numbers." << RESET << std::endl;
            return;
        }
    }
    passward = newPassward;
    std::cout << YELLOW << "Passward successfully set." << RESET << std::endl;
}
// setPassward 오버로딩
void User::setPassward(std::string newPassward) {
    if (newPassward.length() < 5) {
        std::cerr << RED << "Passward should be at least 5 characters long." << RESET << std::endl;
        return;
    }
    for (char c : newPassward) {
        if (!std::isalnum(c)) {
            std::cerr << RED << "Passward should only contain letters and numbers." << RESET << std::endl;
            return;
        }
    }
    passward = newPassward;
    std::cout << YELLOW << "Passward successfully set." << RESET << std::endl;
}

void User::setIsEru(bool newIsEru) {
    isEru = newIsEru;
    std::cout << YELLOW << "isEru successfully set." << RESET << std::endl;
}

bool User::isValidPassword(std::string validPassword) {
    return passward == validPassword;
}

void User::lendBook() {
    lendBookNum += 1;
    if (lendBookNum > lendBookMaxNum) {
        lendBookNum -= 1;
        std::cerr << RED << "can't lend more than " << lendBookMaxNum << " books." << RESET << std::endl;
        return;
    }
    std::cout << YELLOW << "Book is successfully lended" << RESET << std::endl;
}

void User::returnBook() {
    lendBookNum -= 1;
    if (lendBookNum < 0) {
        lendBookNum += 1;
        std::cerr << RED << "You did not lend a book." << RESET << std::endl;
        return;
    }
    std::cout << YELLOW << "Book is successfully returned" << RESET << std::endl;
}