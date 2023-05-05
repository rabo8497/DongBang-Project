#include "usage.h"

Usage::Usage(User *user = NULL, Caelum *target = NULL) : user(user), target(target)
{
    startTime = std::time(0);
}

User *Usage::getUser() { return user; }
Caelum *Usage::getTarget() { return target; }
std::time_t Usage::getStartTime() { return startTime; }