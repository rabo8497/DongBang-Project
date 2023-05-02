#pragma once // include guard

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "User.h"
using namespace std;

const string version = "0.0.1";

int main(int argc, char *argv[]) // argc=인자 갯수, argv=인자들
{
    User user1(1, 12345, "user1", "pass1");
    
    // ID, 학번, 닉네임, isEru, isManager 상태 확인
    std::cout << "ID: " << user1.getId() << std::endl;
    std::cout << "Student Number: " << user1.getStudentNumber() << std::endl;
    std::cout << "Nickname: " << user1.getNickName() << std::endl;
    std::cout << "isEru: " << (user1.getIsEru() ? "true" : "false") << std::endl;
    std::cout << "isManager: " << (user1.getIsManager() ? "true" : "false") << std::endl;

    // 닉네임 변경 시도
    user1.setNickName("nick1");
    std::cout << "Nickname after change: " << user1.getNickName() << std::endl;

    // 비밀번호 변경 시도
    user1.setPassward("pass1", "newPass1");

    // isEru 상태 변경
    user1.setIsEru(true);
    std::cout << "isEru after change: " << (user1.getIsEru() ? "true" : "false") << std::endl;
    
}