#pragma once

#include <iostream>
#include <exception>
#include <memory>
#include <initializer_list>
#include <vector>

#include "storage.hpp"

template <typename T>
class Queue: public Storage<T>
{
public:
    Queue(const std::initializer_list<T> &list): Storage<T>(list) {}
    Queue(std::unique_ptr<T[]> list, size_t size): Storage<T>(list, size) {}
    void print() const;
    void add(const T &elem);
    T pop();
};

template <typename T>
void Queue<T>::print() const
{
    std::cout << "Queue head --> ";
    Storage<T>::print();
}

template <typename T>
void Queue<T>::add(const T &elem)
{
    Storage<T>::elems.push_back(elem);
}

template <typename T> // Absolutely the same as with Stack. Left in case we decide to add some more "storages"
T Queue<T>::pop()
{
    if (Storage<T>::elems.empty())
    {
        throw std::runtime_error("Popping from empty queue.");
    }
    T result = *Storage<T>::elems.begin();
    Storage<T>::elems.erase(Storage<T>::elems.begin());
    return result; 
}
