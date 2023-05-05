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
    int id;
    Usage &usage;

public:
    Caelum(int, std::string, bool);
    std::string getName();
    int getId() const;
    bool active();
    void update(State, Usage &);
    void update(State);
    bool operator<(const Caelum &right);
};

class Device : public Caelum
{
private:
    std::string game;

public:
    Device(int, std::string, bool);
    std::string getGame();
    std::string setGame(std::string);
};

class Account : public Caelum
{
private:
    std::string type;

public:
    Account(int, std::string, std::string, bool);
    std::string getType();
};

#endif