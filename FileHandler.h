#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <string>
#include <iostream>

class FileHandler
{
public:
    FileHandler(std::string newSaveLocation = "none", int newInterval = 0)
    {
        saveLocation = newSaveLocation;
        interval = newInterval;
    } // saveLocation과 interval 초기화, 초기화할 값이 없으면 적당히 쓰레기값 줄 것

    // 아래는 manager class에서 오버로딩 하여 사용할 것
    int findIdFromItem();

    void load(); // txt 파일에 있는 데이터를 불러오는 기능
    void write(); //txt 파일에 데이터를 저장하는 기능
    void modifyFile(); // txt 파일에 있는 데이터를 수정하는 기능
    void deleteFile(); // txt 파일에 있는 데이터를 지우는 기능
    
    // 자동으로 최근의 uuid를 잡아줌
    // 저장할 때 이 함수로부터 받은 uuid + 1 을 하여 저장하면 될듯
    // 사용할 때 saveLocation과 interval을 잘 잡아줄 것
    int getLatestId() {
        int latestId = -1; // return -1이 된다면 아무 데이터도 저장되어있지 않다는 뜻
        std::ifstream inFile(saveLocation);

        if (!inFile) {
            std::cerr << "cannot open user.txt file" << std::endl;
            return -2; // return -2이 된다면 파일 여는데 오류가 생겼다는 뜻
        }

        std::string line;
        int lineNum = 0;
        while (std::getline(inFile, line)) {
            lineNum += 1;
            if (lineNum % interval == 1) {
                latestId = std::stoi(line);
            }
        }
        return latestId; // 정상적으로 출력되면 최근의 uuid가 출력됨
    }

protected:
    std::fstream file; 
    std::string saveLocation; // 데이터 저장 위치
    int interval; // 하나의 데이터를 저장하는데 txt에 할당하는 줄의 수
};

#endif