// Usage : 사용 정보 기록
// 주의 : 사용 중이지 않을 때는 placeholder가 저장됨
// 즉, 사용 중일 때만 참조 바람
// getUser() : 사용자의 주소 값을 반환함
// getTarget() : 사용 대상의 주소 값을 반환함
// 주의 : Caelum* 형이어서 Account, Device 클래스의 기능을 쓰려면 포인터 캐스팅 필요
// getStartTime() : 사용 시작 시간 반환

#ifndef USAGE_H
#define USAGE_H

#include <string>
#include <ctime>
#include "user.h"
#include "caelum.h"

class Usage
{
private:
    User *user;
    Caelum *target;
    std::time_t startTime;

public:
    Usage(User *user, Caelum *target);
    User *getUser();
    Caelum *getTarget();
    std::time_t getStartTime();
};

#endif