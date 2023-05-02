#include <iostream>
#include <cctype>
#include "User.h"

User::User(const int uuid, const int studentNumber, std::string nickname, std::string passward, bool isEru, bool isManager) 
                : uuid(uuid), studentNumber(studentNumber), nickname(nickname), passward(passward), isEru(isEru), isManager(isManager) {};

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
