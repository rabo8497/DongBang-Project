#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <iomanip>
#include <string>

enum Type // Item의 유형을 분류하는 나열자
{
    ACCOUNT,
    DEVICE,
    UNKNOWN,
};

enum State // Item 사용 상태를 분류하는 나열자
{
    INACTIVE = false,
    ACTIVE = true,
};

class Item
{
    friend bool operator<(const Item &, const Item &); // 혹시나 정렬할 일 있을까봐.

private:
    int id;
    Type type;
    std::string name;
    bool isActive;

public:
    Item(std::string = "none", int = -1, bool = false, Type = UNKNOWN); // 순서대로 이름, id, 유형.
    int getId();                                                        // id를 반환하는 함수.
    Type getType();                                                     // 유형을 반환하는 함수.
    std::string getName();                                              // 이름을 반환하는 함수.
    virtual void printInfo() = 0;                                       // 자신의 정보를 출력하는 함수. 이건 인터페이스여서 그냥 가상 처리했다.
    bool active();                                                      // 사용 가능한지를 출력하는 함수.
    void setState(State);                                               // 사용 상태를 변경할 수 있는 함수. INACTIVE/ACTIVE 중 하나를 입력하자.
    void toggleState();                                                 // 사용 상태를 반전하는 함수.
};

#endif