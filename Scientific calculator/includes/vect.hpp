#ifndef VECT_H
#define VECT_H

class Vect // Improvised vector, because no STL
{
public:
    Vect();
    ~Vect();
    Vect(const Vect &other);
    int &operator[](int n);
    const int &operator[](int n) const;
    Vect operator=(const Vect &vect);
    int get_size() const;
private:

    int *arr;
    int arrsize;
    
    static constexpr int increm = 50; // should be at least 1. With too small numbers the program may take up more time to execute
};

#endif
