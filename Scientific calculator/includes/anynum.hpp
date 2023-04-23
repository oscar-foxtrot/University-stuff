/* 
Short description:
This is a header file for custom arbitrary precision numbers library.
------
You can set precision via Anynum::setprecision(int your_precision)
Precision up to the last digit for any operation: +, -, *, / is guaranteed.
For functions cos, sin, asin, exp, log (the last one stands for natural logarithm)
the number of significant digits is guaranteed to be not less than the set precision. The same applies to factorial function.

Note that all the numbers and functions are calculated and represented in terms of significant digits.
This way, if two numbers of different magnitudes (orders) are added or subtracted, an error is intoduced (precision on multiplication or division is saved).
So be sure to set precision according to your needs.

Available notations:
1. Scientific: 000000e+0, where the number of digits displayed is precision set by the std::setprecision(int your_precision) manipulator (from <iostream>)
2. Fixed (default): 0.000000, where the number of digits displayed is precision set by the std::setprecision(int your_precision) manipulator (from <iostream>)
------
*/

#ifndef ANYNUM_H
#define ANYNUM_H

#include <iostream>

// Calculations may take some time, and with precision more than of a couple hundred digits
// the program may seem to be frozen. To ensure that it is in fact not true, the below flag should be set to "true"
// Otherwise, if you don't want unnecessary output, set it to "false"
constexpr bool show_progress_of_taylor_series_calculation = false;

#include "vect.hpp"

class Anynum
{
public:
    Anynum();
    Anynum(int arg);
    Anynum(double arg);
    Anynum(const Anynum &other);
    Anynum operator=(const Anynum &other);
    static void setprecision(int precision);
    Anynum operator-() const;
    friend Anynum operator+(const Anynum &one, const Anynum &other);
    friend Anynum operator-(const Anynum &one, const Anynum &other); 
    friend Anynum operator*(const Anynum &one, const Anynum &other); 
    friend Anynum operator/(const Anynum &one, const Anynum &other);
    friend int compare(const Anynum &one, const Anynum &other); // all comparison operators are easily overloaded if desired
    friend Anynum abs(const Anynum &arg);
    friend std::ostream &operator<<(std::ostream &os, const Anynum &num);

    Anynum cos() const; // Can be used with any argument, however much faster with arguments between -pi and pi
    Anynum sin() const; // Can be used with any argument, however much faster with arguments between -pi and pi
    Anynum exp() const; // Note that only significant digits are calculated. Adjust precision accordingly
    Anynum asin() const; // Valid args are between -1 and 1 (both including), else behavior is undefined (actually infinite cycle because of no convergence)
    Anynum log() const; //  Valid arguments are: 0 < x <= 2, where x is the argument

private:
    Vect digits;
    int ndigits; // number of digits (mantissa size)
    int order;
    bool isneg;
    
    static int precision; // default precision is 6 digits. Reset via Anynum::setprecision(int your_precision)

    class Impl; // for helper functions (implementation)
};

Anynum factorial(int arg);
int compare(const Anynum &one, const Anynum &other);

#endif
