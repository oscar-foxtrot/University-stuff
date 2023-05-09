#pragma once

#include <memory>
#include <initializer_list>
#include <vector>
#include <iostream>

template <typename T>
class Storage
{
public:
    Storage() {}
    Storage (const Storage &other);
    Storage(const std::initializer_list<T> &list): elems(list) {} 
    Storage(std::unique_ptr<T[]> list, size_t size);
    virtual void print() const;
    virtual void add(const T &elem) = 0;
    virtual T pop() = 0;
protected:
    // Internal representation - std::vector
    std::vector<T> elems;
};

template <typename T>
Storage<T>::Storage(const Storage &other)
{
    elems = other.elems;
}

template <typename T>
Storage<T>::Storage(std::unique_ptr<T[]> list, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        elems.push_back(list[i]);
    }
}

template <typename T>
void Storage<T>::print() const
{
    typename std::vector<T>::const_iterator iter = elems.begin(), preend = elems.end() - 1;
    std::cout << "(";
    for (; iter != preend; ++iter)
    {
        std::cout << *iter << ", ";
    }
    std::cout << *preend << ")";
}

