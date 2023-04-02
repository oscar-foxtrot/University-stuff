#pragma once

#include <iostream>
#include <memory>
#include <initializer_list>
#include <vector>

#include "task3_helpers_helpers.hpp"

template <typename T>
class Bl_Arr
{
public:
    Bl_Arr() {}
    // You can either add elems like this (on creation): Bl_Arr example({1, 2, 3, {1, 2, 3}, 5, 6, {5, 2}});
    Bl_Arr(const std::initializer_list<Elem<T>> &elements): elems(elements) {} // Vector can be assigned initializer_list
    // Or you can just add elements via "add": example.add(1); example.add({1, 2, 3, 4})
    void add(const std::initializer_list<T> &vect);
    void add(T elem);
    void remove_last();
    T get_sum() const; // assuming operation "+" is defined for type T
    T get_sum_of_elem(const typename std::vector<Elem<T>>::const_iterator &iterator) const;
    std::vector<Elem<T>> get_elems() const;
private:
    std::vector<Elem<T>> elems;
};

template <typename T>
void Bl_Arr<T>::add(const std::initializer_list<T> &vect)
{
    elems.push_back(vect);
}

template <typename T>
void Bl_Arr<T>::add(T elem)
{
    elems.push_back(elem);
}

template <typename T>
void Bl_Arr<T>::remove_last()
{
    elems.pop_back();
}

template <typename T>
std::vector<Elem<T>> Bl_Arr<T>::get_elems() const
{
    return elems;
}

template <typename T>
T Bl_Arr<T>::get_sum() const
{
    
    T sum;
    typename std::vector<Elem<T>>::const_iterator iter = elems.begin();
    sum = get_sum_of_elem(iter);
    ++iter;
    for (; iter != elems.end(); ++iter)
    {
        sum += get_sum_of_elem(iter);
    }
    return sum;
}

template <typename T>
T Bl_Arr<T>::get_sum_of_elem(const typename std::vector<Elem<T>>::const_iterator &iter) const
{
    T res;
    if (iter->get_type() == 2) // If the type of the first element of our block array is "single element":
    {
        res = iter->get_single();
    }
    else if (iter->get_type() == 1) // If the type of the first element of our block array is "array of elements"
    {
        std::initializer_list<T> tmpl = iter->get_arr();
        typename std::initializer_list<T>::const_iterator tmpliter = tmpl.begin();
        res = *tmpliter;
        ++tmpliter;
        for (; tmpliter != tmpl.end(); ++tmpliter)
        {
            res += *tmpliter;
        } 
    }
    return res;
}
