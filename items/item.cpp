#include "Item.h"

// Constructor
Item::Item(std::string name, int id, bool isActive, Type type, int controllerId) : name(name), id(id), isActive(isActive), type(type), controllerId(controllerId)
{
    isActive = false; // This line has no effect as it assigns the value to the local parameter instead of the class member
}

// Getter functions
int Item::getId() { return id; }
Type Item::getType() { return type; }
std::string Item::getName() { return name; }
bool Item::active() { return isActive; }

// Setter functions
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

// Overloaded less-than operator
bool operator<(const Item &l, const Item &r)
{
    return l.id < r.id; // Items are compared based on their ID
}
