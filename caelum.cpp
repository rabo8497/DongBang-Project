#include "caelum.h"

inline Usage &noUsage(Caelum *p) { return Usage(NULL, p); }

// Caelum : the base class
Caelum::Caelum(int id = -1, std::string name = "none", bool isActive = false) : id(id), name(name), isActive(isActive), usage(noUsage(this)) {}

std::string Caelum::getName() { return name; }

int Caelum::getId() const { return id; }

bool Caelum::active() { return isActive; }

void Caelum::update(State s, Usage &u)
{
    switch (s)
    {
    case INACTIVE:
        isActive = false;
        usage = noUsage(this);
        break;
    case ACTIVE:
        isActive = true;
        usage = u;
        break;
    default:
        isActive = false;
        break;
    }
}

void Caelum::update(State s)
{
    update(s, noUsage(this));
}

bool Caelum::operator<(const Caelum &right)
{
    return id < right.getId();
}

// Device
Device::Device(int id = -1, std::string name = "none", bool isActive = false) : Caelum(id, name, isActive) {}

std::string Device::getGame() { return game; }

std::string Device::setGame(std::string gameName) { game = gameName; }

// Account
Account::Account(int id = -1, std::string name = "none", std::string type = "unknown", bool isActive = false) : Caelum(id, name, isActive), type(type) {}

std::string Account::getType() { return type; }