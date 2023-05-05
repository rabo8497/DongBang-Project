#include "managers.h"

// Manager : the base class
template <typename T>
Manager<T>::Manager()
{
    Items = new std::set<T>;
}

template <typename T>
Manager<T>::~Manager()
{
    delete Items;
}

template <typename T>
void Manager<T>::addItem(T &item)
{
    Items->insert(item);
}

template <typename T>
void Manager<T>::deleteItem(int id)
{
}

template <typename T>
T &getItem(int id)
{
}
