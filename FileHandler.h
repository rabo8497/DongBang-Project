#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <string>

class FileHandler {
public:
    FileHandler();
    ~FileHandler();

    template <typename T>
    T load();

    template <typename T>
    void write(const T&);

    template <typename T>
    void modifyfile(int, const T&);

    void deletefile(int);

private:
    std::fstream file;
    std::string saveLocation;
    int interval;
};

#endif 

