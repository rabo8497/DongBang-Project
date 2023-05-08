#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

enum Type
{
    ACCOUNT,
    DEVICE,
    UNKNOWN,
};

enum State
{
    INACTIVE = false,
    ACTIVE = true,
};

class Item
{
    friend bool operator<(const Item &, const Item &);

private:
    int id;
    Type type;
    std::string name;
    bool isActive;

public:
    Item(std::string = "none", int = -1, Type = UNKNOWN);
    int getId();
    Type getType();
    std::string getName();
    virtual void printInfo() = 0;
    bool active();
    void setState(State);
};

#endif