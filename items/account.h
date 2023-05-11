#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <ctime>
#include "item.h"
#include "../user.h"

inline User &emptyUser() { return *(new User()); }

class Account : public Item
{
private:
    std::string accountType;
    std::time_t startTime;
    User &user;

public:
    Account(std::string = "unknown", std::string = "unknown account", int = -1, User & = emptyUser()); // 순서대로 계정 유형(예: 라프텔), 이름, id.
    void printInfo() override;                                                                         // 자신의 정보를 출력하는 함수.
    std::string getAccountType();                                                                      // 자신의 *계정 유형*을 출력하는 함수.
    std::time_t getStartTime();                                                                        // 사용 중인 경우, 사용 시작 시간을 출력하는 함수. 사용 중이 아니면 1970-01-01 00:00:00을 반환.
    User &getUser();
    void setState(State, User & = emptyUser()); // 사용 상태를 변경하는 함수.
};

#endif