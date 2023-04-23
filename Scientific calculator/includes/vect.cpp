#include "vect.hpp"

int Vect::get_size() const
{
    return arrsize;
}

Vect::Vect()
{
    arr = new int[increm]();
    arrsize = increm;
}

Vect::~Vect()
{
    delete[] arr;
}

int &Vect::operator[](int n)
{
    while (n >= arrsize)
    {
        int *tmp = new int[arrsize + increm](); // init-ing with zeroes
        for (int i = 0; i < arrsize; ++i)
        {
            tmp[i] = arr[i];
        }
        delete[] arr;
        arr = tmp;
        arrsize += increm;
    }
    return arr[n];
}

const int &Vect::operator[](int n) const
{
    return arr[n]; // n must not be out of bounds
}

Vect Vect::operator=(const Vect &other)
{
    if (arr)
    {
        delete[] arr;
    }
    arr = new int[arrsize = other.get_size()]();
    for (int i = 0; i < arrsize; ++i)
    {
        arr[i] = other[i];
    }

    return *this;
}

Vect::Vect(const Vect &other)
{
    arr = new int[arrsize = other.get_size()]();
    for (int i = 0; i < arrsize; ++i)
    {
        arr[i] = other[i];
    }
}
