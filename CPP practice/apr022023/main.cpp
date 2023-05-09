#include <iostream>
#include <memory>

#include "includes/storage.hpp"
#include "includes/stack.hpp"
#include "includes/queue.hpp"

class Apple_Container
{
public:
    Apple_Container(int how_many_apples): number_of_apples_in_the_container(how_many_apples) {}
    friend std::ostream& operator<<(std::ostream &os, const Apple_Container &elem); // Required for testing
private:
    int number_of_apples_in_the_container;
};


int main(int argc, char *argv[])
{
    std::unique_ptr<std::unique_ptr<Storage<int>>[]> arr(new std::unique_ptr<Storage<int>>[2]);
    std::initializer_list<int> init_values = {1, 2, 3, 4, 5};
    arr[0] = std::unique_ptr<Storage<int>>(new Stack<int>(init_values));
    arr[1] = std::unique_ptr<Storage<int>>(new Queue<int>(init_values));

    std::cout << "Initial state:\n";
    arr[0]->print();
    std::cout << std::endl;
    arr[1]->print();
    std::cout << '\n' << std::endl;

    arr[0]->pop();
    arr[1]->pop();
    std::cout << "State after popping 1 element\n";
    arr[0]->print();
    std::cout << std::endl;
    arr[1]->print();
    std::cout << '\n' << std::endl;

    arr[0]->add(100);
    arr[1]->add(100);
    std::cout << "State after adding 1 element\n";
    arr[0]->print();
    std::cout << std::endl;
    arr[1]->print();
    std::cout << '\n' << std::endl;

    std::cout << "Some operations with a STACK of \"Apple Containers\"\n";
    Stack<Apple_Container> arr2({Apple_Container(1), Apple_Container(3), Apple_Container(4)});
    arr2.print();
    std::cout << std::endl;
    std::cout << "Popped " << arr2.pop() << std::endl;
    std::cout << "Popped " << arr2.pop() << std::endl;
    int value = 100;
    arr2.add(Apple_Container(value));
    std::cout << "Added " << value << std::endl;
    arr2.print();

    std::cout << "\n\nThe same with QUEUE of \"Apple Containers\"\n";
    Queue<Apple_Container> arr3({Apple_Container(1), Apple_Container(3), Apple_Container(4)});
    arr3.print();
    std::cout << std::endl;
    std::cout << "Popped " << arr3.pop() << std::endl;
    std::cout << "Popped " << arr3.pop() << std::endl;
    value = 100;
    arr3.add(Apple_Container(value));
    std::cout << "Added " << value << std::endl;
    arr3.print();

    return 0;
}


std::ostream& operator<<(std::ostream &os, const Apple_Container &elem)
{
    return std::cout << elem.number_of_apples_in_the_container;
}
