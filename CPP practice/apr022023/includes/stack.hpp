#pragma once

#include <iostream>
#include <exception>
#include <memory>
#include <initializer_list>
#include <vector>

#include "storage.hpp"

template <typename T>
class Stack: public Storage<T>
{
public:
    Stack(const std::initializer_list<T> &list): Storage<T>(list) {}
    Stack(std::unique_ptr<T[]> list, size_t size): Storage<T>(list, size) {}
    void print() const;
    void add(const T &elem);
    T pop();
};

template <typename T>
void Stack<T>::print() const
{
    std::cout << "Stack top --> ";
    Storage<T>::print();
}

template <typename T>
void Stack<T>::add(const T &elem)
{
    Storage<T>::elems.insert(Storage<T>::elems.begin(), elem);
}

template <typename T> // Absolutely the same as with Query. Left in case we decide to add some more "storages"
T Stack<T>::pop()
{
    if (Storage<T>::elems.empty())
    {
        throw std::runtime_error("Stack is empty.");
    }
    T result = *Storage<T>::elems.begin();
    Storage<T>::elems.erase(Storage<T>::elems.begin());
    return result; 
}
