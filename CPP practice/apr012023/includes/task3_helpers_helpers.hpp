#pragma once

#include <iostream>
#include <memory>
#include <initializer_list>

// Note: templates everywhere were no necessity (according to the task) of course, that's just a bit of practicing with them

// Helper class, designated for "Bl_Arr"
// The only purpose of "Elem" class is to give uniformity to managing elements of "Bl_Arr" class
template <typename T>
class Elem
{
public:
    Elem();
    Elem(T elem);
    Elem(const std::initializer_list<T> &elem_list);
    Elem(const Elem<T> &other);
    T get_single() const;
    int get_type() const;
    std::initializer_list<T> get_arr() const;
    template <typename U>
    friend std::ostream& operator<<(std::ostream &os, const Elem<U> &elem);
private:
    int elem_type = 0; // If elem_id is 1, then this is an ARRAY of elems, if 2 then it is a SINGLE elem
    std::unique_ptr<std::initializer_list<T>> elem_block;
    std::unique_ptr<T> elem_single;
};

template <typename T>
Elem<T>::Elem(T elem)
{
    elem_single = std::unique_ptr<T>(new T);
    *elem_single = elem;
    elem_type = 2;
}

template <typename T>
Elem<T>::Elem(const std::initializer_list<T> &elem_list)
{
    elem_block = std::unique_ptr<std::initializer_list<T>>(new std::initializer_list<T>);
    *elem_block = elem_list;
    elem_type = 1;
}

template <typename T>
Elem<T>::Elem(const Elem<T> &other)
{
    elem_single.reset();
    elem_block.reset();
    if (other.get_type() == 1)
    {
        elem_block = std::unique_ptr<std::initializer_list<T>>(new std::initializer_list<T>);
        *elem_block = other.get_arr();
        elem_type= 1;
    }
    else if (other.get_type() == 2)
    {
        elem_single = std::unique_ptr<T>(new T);
        *elem_single = other.get_single();
        elem_type = 2;
    }
}

template <typename T>
T Elem<T>::get_single() const
{
    return *elem_single;
}   

template <typename T>
int Elem<T>::get_type() const
{
    return elem_type;
}

template <typename T>
std::initializer_list<T> Elem<T>::get_arr() const
{
    return *elem_block;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Elem<T> &elem)
{
    if (elem.elem_type == 1)
    {
        std::initializer_list<T> tmplist = elem.get_arr();
        std::cout << '{';
        int size = tmplist.size(), counter = 0;
        for (auto i: tmplist)
        {
            ++counter;
            if (counter == size)
            {
                std::cout << i;
                break;
            }
            std::cout << i << ", ";
        }
        std::cout << '}';
    }
    else if (elem.elem_type == 2)
    {
        std::cout << elem.get_single();
    } 
    return std::cout;
}
