// There are no cpp files corresponding to .hpp files for a good reason - everything is templated.
// Template classes and functions must be entirely defined inside the headers

#include <iostream>
#include <memory>
#include <initializer_list>
#include <vector>

#include "includes/task3_helpers.hpp" // Contains class "Elem" which encapsulates either an array of elements or a single element.

class Apple_Container
{
public:
    Apple_Container(): number_of_apples_in_the_container(0) {} // Required for "sum" function. See line 56 of "task3_helpers.hpp"
    Apple_Container(int how_many_apples): number_of_apples_in_the_container(how_many_apples) {}
    //Apple_Container operator+(const Apple_Container &other) const;
    Apple_Container operator+=(const Apple_Container &other); // Required for "sum" function
    friend std::ostream& operator<<(std::ostream &os, const Apple_Container &elem); // Required for testing
    int get_number_of_apples() const {return number_of_apples_in_the_container;}
private:
    int number_of_apples_in_the_container;
};


template <typename T>
void test(const Bl_Arr<T> &arr)
{
    std::vector<Elem<T>> vect = arr.get_elems();
    std::cout << "Elements of the block array:" << std::endl;
    for (auto i: vect)
    {
        std::cout << i << "  ";
    }

    std::cout << '\n' << "The sum is: " << arr.get_sum() << '\n' << std::endl;
}

using AplC = Apple_Container; // Long name

int main(int argc, char *argv[])
{
    // Initializing some block array
    std::cout << "Let's try with ints first:" << std::endl;
    Bl_Arr<int> arr0({1, 2, {1, 2 ,3}, 1, 2, {1, 2}});
    arr0.add(1201);
    arr0.add({1, 2, 3});
    test(arr0);

    std::cout << "Let's try with doubles:" << std::endl;
    Bl_Arr<double> arr1({1.21, 2.123123, {1.12, 2.32, 3.323}, 1.12, 2.022, {1.214, 2.4112}});
    arr1.add(1201);
    arr1.add({1, 2, 3});
    test(arr1);

    std::cout << "Let's try with custom type \"Apple Container\":" << std::endl;
    AplC tmpc = AplC(1);
    Bl_Arr<AplC> arr2({{AplC(5), tmpc}, AplC(1)});
    arr2.add(AplC(2));
    test(arr2);
    return 0;
}


/*Apple_Container Apple_Container::operator+(const Apple_Container &other) const
{
    return Apple_Container(number_of_apples_in_the_container + other.get_number_of_apples());
}*/

Apple_Container Apple_Container::operator+=(const Apple_Container &other)
{
    number_of_apples_in_the_container += other.get_number_of_apples();
    return *this;
}

std::ostream& operator<<(std::ostream &os, const Apple_Container &elem)
{
    return std::cout << elem.get_number_of_apples();
}
