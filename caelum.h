// Caelum : 공공재 클래스.
// Account와 Device는 Caelum을 상속함.
// getName() : 이름.
// active() : 쓰이고 있으면 true를 반환함.
// Update(State, User *) : 상태 전환용 "온"
// 사용 예시 : Update(ACTIVE, (사용자 클래스 주소))
// 이걸 쓰면 Usage 클래스에 정보가 기록됨
// Update(State) : 상태 전환용 2 "오프"
// 사용 예시 : Update(INACTIVE)
// 주의 : 사용 중이 아니거나 Update(ACTIVE) 이러면 .Usage.user가 null pointer가 됨
// Device 전용 기능 :
// string game에 대한 getter/setter (현재 플레이 중인 게임)
// Account 전용 기능 :
// getType() : 계정의 유형(Leftel, Netfilx)을 반환함

#ifndef CAELUM_H
#define CAELUM_H

enum State
{
    INACTIVE,
    ACTIVE,
};

#include <string>
#include <ctime>
#include "usage.h"
#include "user.h"

class Caelum
{
private:
    std::string name;
    bool isActive;
    int id;
    Usage &usage;

public:
    Caelum(int, std::string, bool);
    std::string getName();
    int getId() const;
    bool active();
    void update(State, User *);
    void update(State);
    bool operator<(const Caelum &right);
};

class Device : public Caelum
{
private:
    std::string game;

public:
    Device(int, std::string, bool);
    std::string getGame();
    std::string setGame(std::string);
};

class Account : public Caelum
{
private:
    std::string type;

public:
    Account(int, std::string, std::string, bool);
    std::string getType();
};

#endif