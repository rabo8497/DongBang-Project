#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <string>

template <typename T>
class FileHandler
{
public:
    FileHandler();
    ~FileHandler();

    T load();
    void write(const T &);
    void modifyFile(int, const T &);
    void deleteFile(int);

private:
    std::fstream file;
    std::string saveLocation;
    int interval;
};

#endif
