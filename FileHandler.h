#pragma once

#include <fstream>
#include <string>

class FileHandler {
public:
    FileHandler();
    ~FileHandler();

    template <typename T>
    T load();
    
    template <typename T>
    void write(const T& content);

private:
    std::fstream file;
    std::string saveLocation; // 저장할 txt 이름
    int interval; // 간격
};
