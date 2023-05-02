#ifndef USAGE_H
#define USAGE_H

#include <string>
#include <ctime>
#include "user.h"
#include "caelum.h"

class Usage
{
private:
    User *user;
    Caelum *target;
    std::time_t startTime;

public:
    Usage(std::string);
    User *getUser();
    Caelum *getTarget();
    std::time_t getStartTime();
};

#endif