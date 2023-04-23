#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
#include <exception>

#include "vect.hpp"
#include "anynum.hpp"

int Anynum::precision = 6; // default 

class Anynum::Impl // to hide helper funcs
{
public:
    static Anynum get_endval();
    static Anynum add(const Anynum &one, const Anynum &other);
    static Anynum subtract(const Anynum &one, const Anynum &other);
    static Anynum multiply(const Anynum &one, int other, int precision);
    static int divide(const Anynum &one, const Anynum &other); // get 1 digit of result
    static void strip_zeroes(Anynum &arg);
    static void output_fixed(const Anynum &num, int precis, bool onlyint);
    static void output_scientific(const Anynum &num, int precis);
};

// OPERATE KNOWING THE PRECISION

Anynum::Anynum(): ndigits(1), order(0), isneg(false) {}

Anynum::Anynum(int arg)
{
    order = 0;
    isneg = arg < 0;
    if (isneg)
    {
        if (arg == INT_MIN)
        {
            throw std::runtime_error("Absolute value of the integer is too big."
                " Try to initialize the instance of Anynum with something different");
        }
        arg = -arg;
    }
    if (arg == 0)
    {
        ndigits = 1;
        return;
    }
    while (arg % 10 == 0)
    {
        ++order;
        arg /= 10;
    }

    ndigits = 0;
    int tmpndig = 0, tmp = arg;
    while (tmp != 0)
    {
        ++order;
        tmp /= 10;
        ++tmpndig;
    }
    --order;
    while (arg != 0)
    {
        ++ndigits;
        digits[tmpndig - ndigits] = arg % 10;
        arg /= 10;
    }
}

Anynum::Anynum(double arg)
{
    order = 0;
    isneg = arg < 0;
    if (isneg)
    {
        arg = -arg;
    }
    if (arg == 0.0)
    {
        ndigits = 1;
        return;
    }

    while (arg >= 10)
    {
        ++order;
        arg /= 10;
    }
    while (arg < 1)
    {
        --order;
        arg *= 10;
    }

    ndigits = 0;
    while (arg - floor(arg) != 0)
    {
        digits[ndigits++] = (int)arg;
        arg = (arg - floor(arg)) * 10;
    }
    digits[ndigits++] = (int)arg;
}

Anynum::Anynum(const Anynum &other)
{
    order = other.order;
    digits = other.digits;
    ndigits = other.ndigits;
    isneg = other.isneg;
}

Anynum Anynum::operator=(const Anynum &other)
{
    order = other.order;
    digits = other.digits;
    ndigits = other.ndigits;
    isneg = other.isneg;
    return *this;
}

int compare(const Anynum &one, const Anynum &other)
{
    if (one.isneg && !other.isneg)
    {
        return -1;
    }
    else if (!one.isneg && other.isneg)
    {
        return 1;
    }

    if (one.digits[0] == 0) // ALWAYS NORMALIZE NUMBERS BEFORE COMPARISON. One of the nums is 0
    {
        if (other.digits[0] == 0)
        {
            return 0;
        }
        else if (other.isneg)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    else if (other.digits[0] == 0) // ALWAYS NORMALIZE NUMBERS BEFORE COMPARISON. One of the nums is 0
    {
        if (!one.isneg)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    if (one.order > other.order)
    {
        return !one.isneg ? 1 : -1;
    }
    else if (one.order < other.order)
    {
        return !one.isneg ? -1 : 1;
    }
    else // orders are equal
    {
        int tmpndig = 0;
        while (tmpndig < one.ndigits && tmpndig < other.ndigits)
        {
            if (one.digits[tmpndig] > other.digits[tmpndig])
            {
                return !one.isneg ? 1 : -1;
            }
            else if (one.digits[tmpndig] < other.digits[tmpndig])
            {
                return !one.isneg ? -1 : 1;
            }
            ++tmpndig;
        }

        if (one.ndigits > other.ndigits)
        {
            return !one.isneg ? 1 : -1;
        }
        else if (one.ndigits < other.ndigits)
        {
            return !one.isneg ? -1 : 1;
        }
    }
    return 0; // on equality
}

void Anynum::Impl::strip_zeroes(Anynum &arg)
{
    int numzeroes = 0;
    while (arg.ndigits > 1 && arg.digits[numzeroes] == 0) // strip of the leading zeroes (only appicable to subtract and divide functions, hence order manip-s)
    {
        --arg.order;
        ++numzeroes;
        --arg.ndigits;
    }
    for (int i = 0; i < arg.ndigits; ++i)
    {
        arg.digits[i] = arg.digits[i + numzeroes];
    }

    while (arg.ndigits > 1 && arg.digits[arg.ndigits - 1] == 0) // strip of the trailing zeroes
    {
        --arg.ndigits;
    }
}

Anynum Anynum::Impl::add(const Anynum &bigger, const Anynum &smaller) // works with abs vals
{
    if (compare(bigger, 0) == 0)
    {
        return smaller;
    }
    else if (compare(smaller, 0) == 0)
    {
        return bigger;
    }
    Anynum res;
    int cyclefrom;
    int precision = Anynum::precision + (int)(ceil(std::log10(bigger.ndigits)) + 2) > // specific formula (precision)
        Anynum::precision + (int)(ceil(std::log10(smaller.ndigits)) + 2) ?
            Anynum::precision + (int)(ceil(std::log10(bigger.ndigits)) + 2) :
            Anynum::precision + (int)(ceil(std::log10(smaller.ndigits)) + 2);

    if (precision <= bigger.ndigits || precision <= smaller.ndigits + (bigger.order - smaller.order))
    {
        cyclefrom = precision;
    }
    else if (bigger.ndigits >= smaller.ndigits + (bigger.order - smaller.order))
    {
        cyclefrom = bigger.ndigits;
    }
    else
    {
        cyclefrom = smaller.ndigits + (bigger.order - smaller.order);
    }

    int carry = 0;
    res.ndigits = cyclefrom;
    for (int i = cyclefrom; i > bigger.order - smaller.order;)
    {
        --i;
        int smallindex = i - (bigger.order - smaller.order);
        int valtoadd = carry + (i >= bigger.ndigits ? 0 : bigger.digits[i])
            + (smallindex >= smaller.ndigits ? 0 : smaller.digits[smallindex]);

        res.digits[i] = valtoadd % 10;
        carry = valtoadd / 10;
    }

    for (int i = bigger.order - smaller.order; i > 0;)
    {
        --i;
        int valtoadd = (i >= bigger.ndigits ? 0 : bigger.digits[i]) + carry;
        res.digits[i] = valtoadd % 10; 
        carry = valtoadd / 10;
    }

    res.order = bigger.order;
    if (carry)
    {
        ++res.order;
        int tmpdig = res.digits[0];
        res.digits[0] = 1;
        for (int i = 1; i < res.ndigits; ++i)
        {
            int tmp = res.digits[i];
            res.digits[i] = tmpdig;
            tmpdig = tmp;
        }
        res.digits[res.ndigits++] = tmpdig;
    }

    strip_zeroes(res);
    return res;
}

Anynum operator+(const Anynum &one, const Anynum &other)
{
    Anynum res;
    if (!((one.isneg && other.isneg) || (!one.isneg && !other.isneg)))
    {
        if (compare(abs(one), abs(other)) >= 0)
        {
            res = Anynum::Impl::subtract(one, other);
            res.isneg = one.isneg;
            return res;
        }
        else
        {
            res = Anynum::Impl::subtract(other, one);
            res.isneg = other.isneg;
            return res;
        }
    }

    if (one.order >= other.order)
    {
        res = Anynum::Impl::add(one, other);
    }
    else
    {
        res = Anynum::Impl::add(other, one);
    }

    res.isneg = one.isneg;
    return res;
}


Anynum Anynum::Impl::subtract(const Anynum &bigger, const Anynum &smaller) // works with abs vals
{
    if (compare(bigger, smaller) == 0)
    {
        return 0;
    }
    if (compare(smaller, 0) == 0)
    {
        return bigger;
    }
    if (compare(bigger, 0) == 0)
    {
        return -smaller;
    }

    Anynum res;
    int cyclefrom;
    int precision = Anynum::precision + (int)(ceil(std::log10(bigger.ndigits)) + 2) > // specific formula (precision)
        Anynum::precision + (int)(ceil(std::log10(smaller.ndigits)) + 2) ?
            Anynum::precision + (int)(ceil(std::log10(bigger.ndigits)) + 2) :
            Anynum::precision + (int)(ceil(std::log10(smaller.ndigits)) + 2);

    if (precision <= bigger.ndigits || precision <= smaller.ndigits + (bigger.order - smaller.order))
    {
        cyclefrom = precision;
    }
    else if (bigger.ndigits >= smaller.ndigits + (bigger.order - smaller.order))
    {
        cyclefrom = bigger.ndigits;
    }
    else
    {
        cyclefrom = smaller.ndigits + (bigger.order - smaller.order);
    }

    int carry = 0;
    res.ndigits = cyclefrom;
    for (int i = cyclefrom; i > bigger.order - smaller.order;)
    {
        --i;
        int smallindex = i - (bigger.order - smaller.order);
        int subtrval = (i >= bigger.ndigits ? 0 : bigger.digits[i]) -
            (smallindex >= smaller.ndigits ? 0 : smaller.digits[smallindex]) - carry;
        subtrval += 10;
        res.digits[i] = subtrval % 10;
        carry = !(subtrval / 10);
    }

    for (int i = bigger.order - smaller.order; i > 0;)
    {
        --i;
        int subtrval = (i >= bigger.ndigits ? 0 : bigger.digits[i]) - carry;
        subtrval += 10;
        res.digits[i] = subtrval % 10;
        carry = !(subtrval / 10);
    }

    res.order = bigger.order;
    strip_zeroes(res);
    return res;
}

Anynum operator-(const Anynum &one, const Anynum &other)
{
    Anynum res;
    if (!((one.isneg && other.isneg) || (!one.isneg && !other.isneg)))
    {
        res.isneg = one.isneg;
        if (compare(abs(one), abs(other)) >= 0)
        {
            res = Anynum::Impl::add(one, other);
            return res;
        }
        else
        {
            res = Anynum::Impl::add(other, one);
            return res;
        }
    }

    if (compare(abs(one), abs(other)) >= 0)
    {
        res = Anynum::Impl::subtract(one, other);
        res.isneg = one.isneg;
    }
    else
    {
        res = Anynum::Impl::subtract(other, one);
        res.isneg = !other.isneg;
    }
    return res;
}

Anynum Anynum::Impl::multiply(const Anynum &one, int other, int precision)
{
    Anynum res;
    int cyclefrom;

    if (precision <= one.ndigits)
    {
        cyclefrom = precision;
    }
    else
    {
        cyclefrom = one.ndigits;
    }

    int carry = 0;
    res.ndigits = cyclefrom;
    for (int i = cyclefrom; i > 0;)
    {
        --i;
        int addval = other * one.digits[i];
        res.digits[i] = (addval + carry) % 10 ;
        carry = (addval + carry) / 10;
    }

    res.order = one.order;
    if (carry)
    {
        ++res.order;
        int tmpdig = res.digits[0];
        res.digits[0] = carry;
        for (int i = 1; i < res.ndigits; ++i)
        {
            int tmp = res.digits[i];
            res.digits[i] = tmpdig;
            tmpdig = tmp;
        }
        res.digits[res.ndigits++] = tmpdig;
    }

    strip_zeroes(res);
    return res;
}

Anynum operator*(const Anynum &one, const Anynum &other) // long multiplication
{
    Anynum res = 0;
    if (compare(one, 0) == 0 || compare(other, 0) == 0)
    {
        return 0;
    }
    int cycleto = other.ndigits >= Anynum::precision + 2 ? Anynum::precision + 2 : other.ndigits;

    Anynum mult = one;
    int precision = Anynum::precision + (int)(ceil(std::log10(one.ndigits))) + 2; // specific formula (precision)
    for (int i = 0; i < cycleto; ++i)
    {
        --precision;
        mult.order -= i;
        res = res + Anynum::Impl::multiply(mult, other.digits[i], precision);
        mult.order += i;
    }
    res.order += other.order;

    res.isneg = !((one.isneg && other.isneg) || (!one.isneg && !other.isneg));
    return res;
    
}

int Anynum::Impl::divide(const Anynum &one, const Anynum &other)
{
    int res = 0;
    Anynum tmp = one;
    do
    {
        tmp = tmp - other;
        ++res;
    } 
    while (compare(tmp, other) >= 0);
    return res;
}

Anynum operator/(const Anynum &one, const Anynum &other) // long division (one divided by other)
{
    if (compare(one, 0) == 0)
    {
        return 0;
    }
    if (compare(other, 0) == 0)
    {
        throw std::runtime_error("Division by zero");
    }
    
    Anynum res;
    res.order = one.order - other.order;
    int cycleto = Anynum::precision + 2; // until when the division goes on
    res.ndigits = cycleto;
    Anynum numerator = abs(one), othercpy = abs(other);
    othercpy.order = numerator.order;

    int i = 0;
    for (; (i < cycleto) && (compare(numerator, 0) != 0); ++i)
    {
        res.digits[i] = (compare(numerator, othercpy) >= 0) ? // compare numerator, othercpy
            Anynum::Impl::divide(numerator, othercpy) : 0;
        Anynum subtrval = res.digits[i] * othercpy;
        numerator = numerator - subtrval;
        --othercpy.order;
    }
    
    for (int j = i; j < cycleto; ++j)
    {
        res.digits[j] = 0;
    }

    res.order = one.order - other.order;
    Anynum::Impl::strip_zeroes(res);
    res.isneg = !((one.isneg && other.isneg) || (!one.isneg && !other.isneg));
    return res;
}

void Anynum::setprecision(int precision)
{
    Anynum::precision = precision;
}

Anynum Anynum::operator-() const 
{
    if (compare(*this, 0) == 0)
    {
        return 0;
    }
    Anynum res = *this; 
    res.isneg = !res.isneg; 
    return res;
}

Anynum abs(const Anynum &arg)
{
    if (arg.isneg)
    { 
        return -arg;
    } 
    else
    { 
        return arg;
    }
}

Anynum factorial(int fact) // assuming positive vals
{
    Anynum res = 1;
    int i = 1;
    while (i < fact)
    {
        ++i;
        res = res * i;
        //std::cout << "arg: " << i << " res: " << res << std::endl;
        --fact;
    }
    return res;
}

Anynum Anynum::Impl::get_endval()
{
    Anynum endval = 1;
    for (int i = 0; i < Anynum::precision + 2; ++i)
    {
        endval = endval / 10;
    }
    return endval;
}

// Below are trigonometric funcs implemented with the help of Maclaurin series (Taylor series at the zero)
// The error is estimated with the help of the last term of the series

Anynum Anynum::cos() const // Taylor | period equals to 2pi; symmetric (relatively to Oy)
{
    int oldprec = Anynum::precision;
    Anynum res = 0;
    Anynum endval = Impl::get_endval();

    int curadditionalprec = 0;
    Anynum curmemb = 1;
    int curnum = 0;
    while (compare(abs(curmemb), endval) >= 0)
    {
        int neword = 2 * (order + 1) + curmemb.order + 1;
        if (neword > 0)
        {
            Anynum::precision += neword;
        }
        res = res + curmemb;
        ++curnum;
        curmemb = -(curmemb * (*this) * (*this) / (curnum * 2)) / (curnum * 2 - 1);
        if (neword > 0)
        {
            Anynum::precision -= neword;
        }

        if (curnum % 10 == 0 && (int)ceil(std::log10(curnum)) != curadditionalprec)
        {
            ++Anynum::precision; // smart adjustment of precision so as to mitigate error
            curadditionalprec = (int)ceil(std::log10(curnum));
        }

        if (show_progress_of_taylor_series_calculation && (curnum % 25 == 0))
        {
            std::cout << "\"cos\" Maclaurin series: " << curnum << " terms have been calculated. \n";
        }
    }
    
    Anynum::precision = oldprec;

    return res;
}

Anynum Anynum::sin() const // Taylor | period equals to 2pi; symmetric (relatively to (0,0))
{
    int oldprec = Anynum::precision;
    Anynum res = 0;
    Anynum endval = Impl::get_endval();

    Anynum curmemb = *this;
    int curnum = 0;
    int curadditionalprec = 0;
    while (compare(abs(curmemb), endval) >= 0)
    {
        int neword = 2 * (order + 1) + curmemb.order + 1;
        if (neword > 0)
        {
            Anynum::precision += neword;
        }
        res = res + curmemb;
        ++curnum;
        curmemb = -(curmemb * (*this) * (*this) / (curnum * 2)) / (curnum * 2 + 1);
        if (neword > 0)
        {
            Anynum::precision -= neword;
        }

        if (curnum % 10 == 0 && (int)ceil(std::log10(curnum)) != curadditionalprec)
        {
            ++Anynum::precision; // smart adjustment of precision so as to mitigate error
            curadditionalprec = (int)ceil(std::log10(curnum));
        }

        if (show_progress_of_taylor_series_calculation && (curnum % 25 == 0))
        {
            std::cout << "\"sin\" Maclaurin series: " << curnum << " terms have been calculated. \n";
        }
    }

    Anynum::precision = oldprec;

    return res;
}

Anynum Anynum::exp() const // Taylor
{
    int oldprec = Anynum::precision;
    Anynum res = 0;
    Anynum endval = Impl::get_endval();

    bool argchg = false;
    Anynum arg;
    if (compare(*this, 0) == 1)
    {
        arg = -*this;
        argchg = true;
    }
    else
    {
        arg = *this;
    }

    Anynum curmemb = 1;
    int curnum = 0;
    int curadditionalprec = 0;
    while (compare(abs(curmemb), endval) >= 0)
    {
        res = res + curmemb;
        ++curnum;
        curmemb = curmemb * (arg) / curnum;

        if (curnum % 10 == 0 && (int)ceil(std::log10(curnum)) != curadditionalprec)
        {
            ++Anynum::precision; // smart adjustment of precision so as to mitigate error
            curadditionalprec = (int)ceil(std::log10(curnum));
        }
    
        if (show_progress_of_taylor_series_calculation && (curnum % 25 == 0))
        {
            std::cout << "\"exp\" Maclaurin series: " << curnum << " terms have been calculated. \n";
        }
    }

    Anynum::precision = oldprec;
    if (argchg)
    {
        res = 1 / res;
    }
    return res;
}

// Desirable error guaranteed
Anynum Anynum::asin() const // Taylor | valid args are between -1 and 1. ARGS SHOULD BE VALID, else no convergence
{
    int oldprec = Anynum::precision;
    Anynum res = 0;
    Anynum endval = Impl::get_endval();
    
    
    Anynum curarg = *this;
    Anynum curmemb = *this;
    int curnum = 0;
    int curadditionalprec = 0;
    while (compare(abs(curmemb), endval) >= 0)
    {
        res = res + curmemb;
        ++curnum;
        curarg = curarg * (*this) * (*this) * (curnum * 2 - 1) / (curnum * 2);
        curmemb = curarg / (curnum * 2 + 1);

        if (curnum % 10 == 0 && (int)ceil(std::log10(curnum)) != curadditionalprec)
        {
            ++Anynum::precision; // smart adjustment of precision so as to mitigate error
            curadditionalprec = (int)ceil(std::log10(curnum));
        }

        if (show_progress_of_taylor_series_calculation && (curnum % 25 == 0))
        {
            std::cout << "\"arcsin\" Maclaurin series: " << curnum << " terms have been calculated. \n";
        }
    }

    Anynum::precision = oldprec;
    return res;
}

// Desirable error guaranteed
Anynum Anynum::log() const // Taylor | valid arg "x" would be if 0 < x <= 2. ARGS SHOULD BE VALID, else no convergence
{
    if (compare(*this, 0) <= 0 || compare(*this, 2) > 0)
    {
        std::cout << "Please, provide an argument between "
            "0 (not including) and 2 (including) for the calculation of natural logarithm. Returning zero..." << std::endl;
        return 0;
    }

    int oldprec = Anynum::precision;
    Anynum arg = *this - 1;
    Anynum res = 0;
    Anynum endval = Impl::get_endval();

    int curadditionalprec = 0;
    Anynum curarg = arg;
    Anynum curmemb = arg;
    int curnum = 0;
    while (compare(abs(curmemb), endval) >= 0)
    {
        if (!(curnum % 2)) // even
        {
            res = res + curmemb;
        }
        else // odd
        {
            res = res - curmemb;
        }
        ++curnum;
        curarg = curarg * arg;
        curmemb = curarg / (curnum + 1);

        if (curnum % 10 == 0 && (int)ceil(std::log10(curnum)) != curadditionalprec)
        {
            ++Anynum::precision; // smart adjustment of precision so as to mitigate error
            curadditionalprec = (int)ceil(std::log10(curnum));
        }

        if (show_progress_of_taylor_series_calculation && (curnum % 25 == 0))
        {
            //std::cout << curmemb << std::endl; // It indeed converges for numbers close to 2 and 2 itself, but if high precision (more than 5-6 digits) is set, 
            // it will take really long time to calculate with desired precision
            std::cout << "\"log\" Maclaurin series: " << curnum << " terms have been calculated. \n";
        }
    }

    Anynum::precision = oldprec;
    return res;
}


/*std::ostream &operator<<(std::ostream &os, const Anynum &num) // CHANGE so that it supports manipualtors CHECK MANIPULATORS!
{
    if (num.isneg)
    {
        std::cout << '-';
    }

    std::cout << num.digits[0];
    if (num.ndigits > 1)
    {
        std::cout << '.';
    }
    for (int i = 1; i < num.ndigits; ++i)
    {
        std::cout << num.digits[i];
    }
    std::cout << " order: " << num.order;
    return std::cout;
} // for debugging. I'll leave it here on purpose, even when i send it*/

void Anynum::Impl::output_fixed(const Anynum &num, int precis, bool onlyint)
{
    if (num.order < 0)
    {
        if (precis > 0)
        {
            std::cout << "0.";
        }
        else
        {
            std::cout << "0";
        }
        for (int j = 0; j < -num.order - 1 && j < precis; ++j)
        {
            std::cout << '0';
        }
        for (int j = -num.order - 1; j < precis; ++j)
        {
            std::cout << ((j + num.order + 1) >= num.ndigits ? 0 : num.digits[j]);
        }
    }
    else 
    {
        int curpos = 0;
        for (; curpos <= num.order; ++curpos)
        {
            std::cout << ((curpos >= num.ndigits) ? 0 : num.digits[curpos]);
        }
        if (precis == 0)
        {
            return;
        }
        if (curpos >= num.ndigits && onlyint)
        {
            return;
        }
        std::cout << '.';
        for (int i = 0; i < precis; ++i)
        {
            std::cout << ((i + curpos >= num.ndigits) ? 0 : num.digits[i + curpos]);
        }
    }
}

void Anynum::Impl::output_scientific(const Anynum &num, int enditer)
{
    std::cout << num.digits[0];
    if (num.ndigits > 1 && enditer > 1)
    {
        std::cout << '.';
    }
    for (int i = 1; i < enditer; ++i)
    {
        std::cout << (i >= num.ndigits ? 0 : num.digits[i]);
    }
    std::cout << 'e';
    if (num.order >= 0) 
    {
        std::cout << '+';
    }
    std::cout << num.order;
}

std::ostream &operator<<(std::ostream &os, const Anynum &num)
{
    if (num.isneg)
    {
        std::cout << '-';
    }

    int precis = std::cout.precision();

    if (std::cout.flags() & std::ios_base::fixed) // 0.000000
    {
        Anynum::Impl::output_fixed(num, precis, false);
    }
    else if (std::cout.flags() & std::ios_base::scientific) // 0.000000e+0
    {
        Anynum::Impl::output_scientific(num, precis);
    }
    else
    {
        Anynum::Impl::output_fixed(num, precis, true); // default
    }

    return std::cout;
}

// All special cases (i.e. zero div, add, mult, subtract) checked
// Considered error that Taylor series calculations introduce
