#include "userManager.h"
#include <iostream>
#include <string>

UserManager::UserManager() : FileHandler("user.txt", 10) {
    latestId = -1;
    isSignIn = false;
    setLatestId();
}

bool UserManager::getIsSignIn() const {
    return isSignIn;
}

void UserManager::setLatestId() {
    std::ifstream inFile(saveLocation);

    if (!inFile) {
        std::cerr << "cannot open user.txt file" << std::endl;
        return;
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(inFile, line)) {
        lineNum += 1;
        if (lineNum % interval == 1) {
            latestId = std::stoi(line);
        }
    }
}

void UserManager::write(User newUser, std::string password) {
    int studentNumber = newUser.getStudentNumber();
    bool isEru = newUser.getIsEru();
    bool isManager = newUser.getIsManager();
    std::string nickname = newUser.getNickName();
    std::string newUUID = std::to_string(latestId+1);
    std::string studentNumberStr = std::to_string(studentNumber);
    std::string isEruStr = isEru ? "true" : "false";
    std::string isManagerStr = isManager ? "true" : "false";
    std::string saveData = newUUID + "\n" + studentNumberStr + "\n" + nickname + "\n" + password + "\n" + isEruStr + "\n" + isManagerStr + "\n" + "\n" + "\n" + "\n";
    std::ofstream outFile(saveLocation, std::ios::app);
    if (!outFile) {
        std::cerr << "cannot open file" << std::endl;
        return;
    }
    outFile << saveData << std::endl;
    outFile.close();
}

void UserManager::load(int findId) {
    bool isFind = false;
    std::ifstream inFile(saveLocation);
    if (!inFile) {
        std::cerr << "cannot open user.txt file" << std::endl;
        return;
    }
    std::string line;
    int lineNum = 0;
    while (std::getline(inFile, line)) {
        lineNum += 1;
        if (lineNum % interval == 1) {
            if (std::stoi(line) == findId) {
                isFind = true;
            }

        }
    }
}

void UserManager::modifyFile(int uuid, const std::string data) {
    // modifyFile 함수 구현
}

void UserManager::deleteFile(int uuid) {
    // deleteFile 함수 구현
}

void UserManager::signUp(int studentNumber, std::string nickname, std::string password, bool isEru=false, bool isManager=false) {
    setLatestId();
    User newUser(latestId+1, studentNumber, nickname, password, isEru, isManager);
    write(newUser, password);
    latestId += 1;
}