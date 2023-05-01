#ifndef USAGE_H
#define USAGE_H

#include <string>
#include <ctime>

class Usage
{
private:
    std::string user;
    std::time_t startTime;

public:
    Usage(std::string user) : user(user), startTime(std::time(0)){};
    std::string getUser();
    std::time_t getStartTime();
};

#endif