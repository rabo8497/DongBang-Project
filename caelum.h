#ifndef CAELUM_H
#define CAELUM_H

enum State
{
    INACTIVE,
    ACTIVE,
};

#include <string>
#include <ctime>
#include "usage.h"

class Caelum
{
private:
    std::string name;
    bool isActive;
    Usage usage;

public:
    Caelum(std::string, bool);
    std::string getName();
    bool Active();
    void Update(State);
    void Update(State, Usage);
};

Class Device : public Caelum
{
public:
    Device(std::string, bool;
};

Class Account : public Caelum
{
private:
    std::string type;

public:
    Account(std::string, std::string, bool);
    std::string getType();
};

#endif