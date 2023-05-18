#include "ItemManager.h"

ItemManager::ItemManager() : FileHandler(".\\dataBase\\items.txt")
{
    Items.reserve(EXPECTED_LIST_SIZE); // loading 최척화를 위해 공간 예약
}

ItemManager::~ItemManager()
{
    write(); // 저장해두기
    /*
    for (auto i : Items)
        delete i; // 각 item의 메모리 할당 해제
        */
}

inline void printSingleItem(int index, Item *i) // 각 항목의 출력 함수
{
    std::cout << "| " << index << ". "; // vector의 index와 무관
    i->printInfo();
    std::cout << std::endl;
}

void ItemManager::showList(bool showActive)
{
    int idx = 1;
    for (auto i : Items)
    {
        if (!showActive && i->active())
            continue;
        printSingleItem(idx++, i);
    }
}

void ItemManager::showList(Type typeFilter, bool showActive)
{
    // int idx = 1;
    for (auto i : Items)
    {
        if ((!showActive && i->active()) || i->getType() != typeFilter) // typefilter가 요구하는 type이 아니면 skip
            continue;
        printSingleItem(i->getId(), i);
    }
}

void ItemManager::addItem(Item *item)
{
    Items.push_back(item);
}

void ItemManager::deleteItem(int id)
{
    std::vector<Item *>::iterator target;
    for (std::vector<Item *>::iterator it = Items.begin(); it < Items.end(); it++)
    {
        if ((*it)->getId() == id)
        {
            target = it;
            break;
        }
    }
    std::iter_swap(target, Items.end() - 1);
    Items.pop_back();
}

Item *ItemManager::getItem(int id)
{
    for (auto i : Items)
    {
        if (i->getId() == id)
            return i;
    }
    std::cerr << "no item found." << std::endl;
    return 0;
}
Item *ItemManager::getItem(std::string name)
{
    for (auto i : Items)
    {
        if (i->getName() == name)
            return i;
    }
    std::cerr << "no item found." << std::endl;
    return 0;
}

int ItemManager::getLatestId()
{
    int maxId = 0;
    for (auto i : Items)
    {
        if (i->getId() > maxId)
            maxId = i->getId();
    }
    return maxId + 1;
}

void ItemManager::load()
{
    file.open(saveLocation, std::ios::in); // 파일 열기, 읽기 모드
    std::vector<std::string> buffer;       // 파일 담아두는 버퍼
    char temp[MAX_BUFFER_SIZE];            // buffer에 올리기 위한 임시 string
    while (file.getline(temp, MAX_BUFFER_SIZE))
    {
        buffer.push_back((std::string)temp); // buffer에 각 줄의 data 올리기
        file.clear();                        // 각 줄을 읽을 때마다 flag 초기화
    }
    for (auto text : buffer)
    {
        std::stringstream ss(text);       // parser
        std::string type, name, isActive; // item의 공통 member
        int id;
        ss >> type;            // type에 따라 parsed sentence의 구조가 다름
        if (type == "ACCOUNT") // ACCOUNT 계정유형 이름 id 사용여부 (uuid 사용시작시간)
        {
            std::string accountType;
            int uuid;
            time_t startTime;
            ss >> accountType >> name >> id >> isActive; //'사용여부'까지 읽음
            if (id == -1)
                id = getLatestId(); // id가 유효하지 않을 시 재발급.
            if (isActive == "ACTIVE")
            {
                ss >> uuid >> startTime; //'사용시작시간' 까지 읽음
                Account *a = new Account(accountType, name, id, true, uuid, startTime);
                addItem(a);
            }
            else if (isActive == "INACTIVE")
            {
                Account *a = new Account(accountType, name, id, false);
                addItem(a);
            }
            else // 사용여부 값이 이상할 때 = parsing 실패
            {
                std::cerr << "parsing failed.";
            }
        }
        else if (type == "DEVICE") // DEVICE 이름 id 사용여부
        {
            ss >> name >> id >> isActive;
            if (id == -1)
                id = getLatestId(); // id가 유효하지 않을 시 재발급.
            bool isActiveBool;
            if (isActive == "ACTIVE")
                isActiveBool = true;
            else if (isActive == "INACTIVE")
                isActiveBool = false;
            else // 사용여부 값이 이상할 때 = parsing 실패
                std::cerr << "parsing failed.";
            addItem(new Device(name, id, isActiveBool));
        }
    }
    file.close(); // 파일을 다시 읽을 일은 없다.
}

void ItemManager::write()
{
    file.clear();
    file.open(saveLocation, std::ios::out | std::ios::trunc); // 파일 완전히 재작성함
    for (auto i : Items)
    {
        if (i->getType() == ACCOUNT)
        {
            Account *ii = dynamic_cast<Account *>(i); // 다운캐스팅 필요
            file << "ACCOUNT " << ii->getAccountType() << " " << ii->getName() << " " << ii->getId();
            if (ii->active())
            {
                file << " ACTIVE " << ii->getcontrollerId() << " " << ii->getStartTime() << std::endl;
            }
            else
            {
                file << " INACTIVE" << std::endl;
            }
        }
        else if (i->getType() == DEVICE)
        {
            Device *ii = dynamic_cast<Device *>(i); // 다운캐스팅이 필요하진 않으나 넣어둠
            file << "DEVICE " << ii->getName() << " " << ii->getId();
            if (ii->active())
            {
                file << " ACTIVE" << std::endl;
            }
            else
            {
                file << " INACTIVE" << std::endl;
            }
        }
    }
    file.close();
}