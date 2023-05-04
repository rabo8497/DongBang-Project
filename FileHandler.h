#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <string>
#include "User.h"

class FileHandler
{
public:
    FileHandler(std::string newSaveLocation = "none", int newInterval = 0) 
    {
        saveLocation = newSaveLocation;
        interval = newInterval;
    } // saveLocation과 interval 초기화, 초기화할 값이 없으면 적당히 쓰레기값 줄 것

    // 아래는 manager class에서 오버라이드 하여 사용할 것
    virtual void load(int) = 0;
    virtual void write(User, std::string) = 0; // int는 uuid를 입력하길 바람
    virtual void modifyFile(int, const std::string = "") = 0;
    virtual void deleteFile(int) = 0;
    
protected:
    std::fstream file;
    std::string saveLocation;
    int interval;
};

#endif
