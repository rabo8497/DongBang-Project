#include "item.h"

Item::Item(std::string name, int id, bool isActive, Type type) : name(name), id(id), isActive(isActive), type(type)
{
    isActive = false;
}

int Item::getId() { return id; }
Type Item::getType() { return type; }
std::string Item::getName() { return name; }
bool Item::active() { return isActive; }
void Item::setState(State state)
{
    isActive = state;
}

bool operator<(const Item &l, const Item &r)
{
    return l.id < r.id;
}