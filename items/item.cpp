#include "Item.h"

Item::Item(std::string name, int id, bool isActive, Type type, int controllerId) : name(name), id(id), isActive(isActive), type(type), controllerId(controllerId)
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
void Item::toggleState()
{
    isActive = !isActive;
}

int Item::getcontrollerId() { return controllerId; }

void Item::setcontrollerId(int uuid) { this->controllerId = uuid; }

bool operator<(const Item &l, const Item &r)
{
    return l.id < r.id;
}