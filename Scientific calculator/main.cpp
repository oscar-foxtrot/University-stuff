#include <iostream>
#include <iomanip>

#include "includes/function.hpp"
#include "includes/variable.hpp"
#include "includes/anynum.hpp"

int main(int argc, char *argv[]) // All tests from the description of the task are included in main + some custom tests
{
    // Define variables x and y that are correspondingly named:
    std::cout << "--Milestone 0--\n";

    Variable x("x"), y("y");
    Function f = 3 * x * x - 2 * x;
    std::cout << f << std::endl; // Print some text representation of f
    std::cout << f(x) << std::endl; // Print the same representation of f
    std::cout << f(2 + x * x) << std::endl; // Print text representation of f (2 + x * x )

    std::cout << "\n--Milestone 1--\n";

    std::cout << f(y) << std::endl; // Print representation of f in which " x " is replaced by " y "
    Function g = sin(x) * sin(x) + cos(x) * cos(x);
    Function h = exp(y) + log(1 + y * y);
    h = h + 2.5 * exp(h(y * y)) * cos(sin(h)) * y;
    std::cout << h << std::endl; // CUSTOM TEST

    std::cout << "\n--Milestone 2--\n";

    try
    {
        h = h + g; // Error : rhs depends on two arguments (both x and y)
    }
    catch(...) // h was not changed in the previous line because the error is detected before the assignment, hence we can use it
    {
        std::cout << "Something went wrong" << std::endl;
    }
    std::cout << h << std::endl; // CUSTOM TEST
    h = h(x) + g(x); // OK, now h by default depends on x
    std::cout << f(1) << ' ' << 2 * g(0) << ' ' << h(0) + 1 << std::endl; // Print 1 2 3

    std::cout << "\n--Milestone 3--\n";

    f = asin(x);
    g = exp(x);
    std::cout << 6 * f(0.5) << ' ' << g(1) << std::endl; // Print constants π and e (standard precision is 6)
    h = 6 * f(0.5 * g(x) + x * x * g(f(x)));
    // Print constant π with 100 significant digits:
    Anynum::setprecision(100);
    std::cout << std::fixed << std::setprecision(100) << h(0) << std::endl;
    Anynum x0 = h(0); // h(0) is calculated using std::asin and std::exp
    std::cout << x0 << std::endl; // Standard print of the variable x
    std::cout.unsetf(std::ios_base::fixed);

    std::cout << "\n--Milestone 4--\n";

    Function huge = 1;
    for (int i = 0; i < 1000; ++i) 
    {
        huge = huge * 10;
    }

    Anynum::setprecision(1002);
    Function sum = huge + 1;
    std::cout << std::setprecision(1002) << sum(0); // Print 10^1000 + 1

    std::cout << std::endl;

/////////////////////////////////// Below are custom tests showing arbitrary precision numbers behavior

    Variable x1;
    Function f1, g1, sin100;
    f1 = asin(x1);
    g1 = exp(x1);
    sin100 = sin(x1);
    Anynum::setprecision(100);

    Anynum pi = 6 * f1(0.5);
    std::cout << "A hundred digits of pi: " << std::setprecision(100) << pi << '\n' << std::endl;
    std::cout /*<< std::setprecision(100)*/ << "sin(100): " << sin100(100) << '\n' << std::endl;
    Anynum e = g1(1);
    std::cout /*<< std::setprecision(100)*/ << "e constant in scientific notation: " << std::scientific << e << '\n' << std::endl;
    std::cout /*<< std::setprecision(100)*/ << "e constant in fixed-point notation: " << std::fixed << e << '\n' << std::endl;

    // The test represented by 3 lines below may take about 30-45 secs to execute. Decided to comment it out for now
    //Anynum::setprecision(500);
    //pi = 6 * f1(0.5);
    //std::cout << "500 digits of pi: " << std::setprecision(500) << pi << '\n' << std::endl; 


    /*std::cout.unsetf(std::ios_base::fixed);
    std::cout << "1000! is " << factorial(1000);*/

    return 0;
}

// cos(1), for example, is of type FUNCTION. Leaving it like that
