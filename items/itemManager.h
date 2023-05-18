#ifndef ITEMMAGANER_H
#define ITEMMANAGER_H

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include "item.h"
#include "../FileHandler.h"
#include "Account.h"
#include "Device.h"

#define EXPECTED_LIST_SIZE 16
#define FILE_INTERVAL 7
#define MAX_BUFFER_SIZE 256

class ItemManager : public FileHandler
{
private:
    std::vector<Item *> Items; // 공공재(계정+물품) 저장하는 리스트.

public:
    ItemManager();
    ~ItemManager();
    void showList(bool = false);       // 계정과 물품의 목록을 출력하는 함수.
    void showList(Type, bool = false); // 첫 번째 인자에 ACCOUNT, DEVICE 중 하나 입력해서 그 종류만 목록을 출력할 수 있다.
    void addItem(Item *);              // Item class의 포인터 값을 입력하면 리스트에 추가해주는 함수. *주의: 동적 할당한 것만 넣어라*
    void deleteItem(int);              // 특정 Item의 id 값을 입력하면 그걸 리스트에서 지워주는 함수.
    int getLatestId();                 // 새 Id 값을 생성하는 함수.
    Item *getItem(int);                // 특정 Item의 id 값을 입력하면 그 Item의 주소를 반환하는 함수.
    Item *getItem(std::string);        // 특정 Item의 이름을 입력하면 그 Item의 주소를 반환하는 함수. 계정 유형 입력하면 안된다

    void load();  // items.txt에서 문서 불러오기
    void write(); // items.txt으로 문서 저장하기
};

#endif