// Account and Devices Manager.
// 계정, 기기 클래스를 저장 및 관리하는 클래스.
// AccountManager 클래스는 계정 관리, DeviceManager 클래스는 기기 관리.
// 공통 기능:
// showList(bool) : 현재 저장된 공공재의 목록을 출력.
// 기본적으로 '이용 가능한' 것만 출력하지만, 인자에 true 넣으면 사용 중인 것도 출력함.
// addItem(Caelum*) : 새로 넣을 클래스의 "주소 값"을 주면 그 클래스를 목록에 추가함.
// deleteItem(int) : 인자에 지우고 싶은 클래스의 "id 값"을 입력하면 목록에서 삭제함.
// getItem(int) : 클래스의 "id 값"을 입력하면 클래스의 주소를 반환함.
// search(string) : Caelum 클래스(계정, 기기 클래스)에는 Name 값이 있는데, 이걸로 검색하는 기능.
// 주의 : search()는 "id 값"을 반환함. 주소가 아님.
// AccountManager 추가 기능:
// showList(string, bool) : 첫 번째 인자에 계정의 유형 (Laftel, Netflix 등) 입력 시 그 유형만 표시함. 즉 필터.
// search(string, string) : 유형+이름 형식 검색. 딱히 쓸 일 없을 듯.

#ifndef MANAGERS_H
#define MANAGERS_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "caelum.h"

#define EXPECTED_SIZE 8

class Manager
{
private:
    std::vector<Caelum *> *Items;
    std::vector<Caelum *>::iterator getIter(int);

public:
    Manager();
    ~Manager();
    std::vector<Caelum *> *getList();
    virtual void showList(bool) = 0;
    void addItem(Caelum *);
    void deleteItem(int);
    Caelum *getItem(int);
    virtual int search(std::string);
    // filehandler 추가 바람
};

class AccountManager : public Manager
{
private:
    void printAccount(Account *item);

public:
    void showList(bool) override;
    void showList(std::string, bool);
    int search(std::string, std::string);
    int search(std::string);
};

class DeviceManager : public Manager
{
public:
    void showList(bool);
};

#endif