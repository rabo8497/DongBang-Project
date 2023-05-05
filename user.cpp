#include <iostream>
#include <cctype>
#include "user.h"

User::User() {};
User::User(const int newuuid, const int newstudentNumber, std::string newnickname, std::string newpassward, bool newisEru, bool newisManager) 
: isEru(newisEru), isManager(newisManager) 
{
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
        std::cout << "this is wrong student number." << newStudentNumber << std::endl;
        return;
    }
    std::cout << "student number successfully set." << std::endl;
    studentNumber = newStudentNumber;
}

void User::setNickName(std::string newNickName) {
    if (newNickName.length() < 5) {
        std::cout << "Nickname should be at least 5 characters long." << std::endl;
        return;
    }

    for (char c : newNickName) {
        if (!std::isalnum(c)) {
            std::cout << "Nickname should only contain letters and numbers." << std::endl;
            return;
        }
    }
    nickname = newNickName;
    std::cout << "Nickname successfully set." << std::endl;
}

void User::setPassward(std::string originPassward, std::string newPassward) {
    if (originPassward != passward) {
        std::cout << "incorrect passward" << std::endl;
        return;
    }
    if (newPassward.length() < 5) {
        std::cout << "Password should be at least 5 characters long." << std::endl;
        return;
    }
    for (char c : newPassward) {
        if (!std::isalnum(c)) {
            std::cout << "Passward should only contain letters and numbers." << std::endl;
            return;
        }
    }
    passward = newPassward;
    std::cout << "Passward successfully set." << std::endl;
}
// setPassward 오버로딩
void User::setPassward(std::string newPassward) {
    if (newPassward.length() < 5) {
        std::cout << "Passward should be at least 5 characters long." << std::endl;
        return;
    }
    for (char c : newPassward) {
        if (!std::isalnum(c)) {
            std::cout << "Passward should only contain letters and numbers." << std::endl;
            return;
        }
    }
    passward = newPassward;
    std::cout << "Passward successfully set." << std::endl;
}

void User::setIsEru(bool newIsEru) {
    isEru = newIsEru;
    std::cout << "isEru successfully set." << std::endl;
}

bool User::isValidPassword(std::string validPassword) {
    return passward == validPassword;
}