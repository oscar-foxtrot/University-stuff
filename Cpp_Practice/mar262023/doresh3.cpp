// Only smart ptrs used this time
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <memory>

class Apple
{
public:
    Apple(bool isheavy); // true for heavy, false for light
    bool get_weight() const;
private:
    bool weight;
};

class Box
{
public:
    Box(const Apple &apple1, const Apple &apple2);
    std::unique_ptr<Apple[]> get_apples() const;
    virtual void print_weight() const = 0;
    virtual bool is_heavy() const = 0;
    ~Box();
protected:
    Apple *apples;
};

class HeavyBox: public Box
{
public:
    HeavyBox(const Apple &apple1, const Apple &apple2);
    void print_weight() const;
    bool is_heavy() const; // returns true
};

class LightBox: public Box
{
public:
    LightBox(const Apple &apple1, const Apple &apple2);
    void print_weight() const;
    bool is_heavy() const; // returns false
};

std::unique_ptr<Box> create_box(const Apple &apple1, const Apple &apple2);

// I personally didn't like the repetition below.
// Thought about resolving this with templates by taking advantage of "template argument deduction"
// and then checking for types with typeid()
// but came to the conclusion that the repetition is better in a way.
std::unique_ptr<Box> operator+(const Box &box1, const Box &box2);
std::unique_ptr<Box> operator+(const Box &box1, const std::unique_ptr<Box> &box2);
std::unique_ptr<Box> operator+(const std::unique_ptr<Box> &box1, const Box &box2);
std::unique_ptr<Box> operator+(const std::unique_ptr<Box> &box1, const std::unique_ptr<Box> &box2);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    std::cout << "\nTEST 1:\n";
    // Testing the correctness of box creation
    Apple apple1(true), apple2(false);
    std::unique_ptr<Box> box1 = create_box(apple1, apple2);
    std::cout << "Box 1: ";
    box1->print_weight(); // A box with one heavy apple and one light apple should be HEAVY

    Apple apple3(false), apple4(false);
    std::unique_ptr<Box> box2 = create_box(apple3, apple4);
    std::cout << "Box 2: ";
    box2->print_weight(); // A box with two light apples should be LIGHT

    Apple apple5(true), apple6(true);
    std::unique_ptr<Box> box3 = create_box(apple5, apple6);
    std::cout << "Box 3: ";
    box3->print_weight(); // A box with two heavy apples should be HEAVY


    std::cout << "\nTEST 2:\n";
    int heavy_counter = 0;
    int light_counter = 0;
    int number_of_tests = 100000;
    for (int i = 0; i < number_of_tests; ++i)
    {
        (box1 + box1)->is_heavy() ? ++heavy_counter : ++light_counter; // Expecting about 75% of heavy boxes and 25% of light boxes
    }
    std::cout << "Generated " << heavy_counter << " heavy boxes " << '(' << (double) heavy_counter / number_of_tests * 100 << "\% of all boxes)\n";
    std::cout << "Generated " << light_counter << " light boxes " << '(' << (double) light_counter / number_of_tests * 100 << "\% of all boxes)\n";


    std::cout << "\nTEST 3:\n";
    heavy_counter = 0;
    light_counter = 0;
    number_of_tests = 100000;
    for (int i = 0; i < number_of_tests; ++i)
    {
        // box1 + create_box(true, false) will generate 25% of boxes with only heavy apples, 50% of boxes with a light apple
        // and a heavy apple and 25% of boxes with only light apples
        // Thus, the expected result after the second "+" is 50% light boxes, 50% heavy boxes
        (box1 + create_box(true, false) + box2)->is_heavy() ? ++heavy_counter : ++light_counter;
    }
    std::cout << "Generated " << heavy_counter << " heavy boxes " << '(' << (double) heavy_counter / number_of_tests * 100 << "\% of all boxes)\n";
    std::cout << "Generated " << light_counter << " light boxes " << '(' << (double) light_counter / number_of_tests * 100 << "\% of all boxes)\n";


    std::cout << "\nTEST 4:\n";
    heavy_counter = 0;
    light_counter = 0;
    number_of_tests = 100000;
    for (int i = 0; i < number_of_tests; ++i)
    {
        // After each "+" the "heaviness" distribution is the same. Thus, the result is as if there was only one "+" - 75% heavies and 25% lights
        (box1 + box1 + box1 + box1 + box1 + box1 + box1 + box1 + box1 + HeavyBox(true, false) + create_box(true, false))->is_heavy() ? ++heavy_counter : ++light_counter;
    }
    std::cout << "Generated " << heavy_counter << " heavy boxes " << '(' << (double) heavy_counter / number_of_tests * 100 << "\% of all boxes)\n";
    std::cout << "Generated " << light_counter << " light boxes " << '(' << (double) light_counter / number_of_tests * 100 << "\% of all boxes)\n";


    return 0;
}


Apple::Apple(bool weight): weight(weight) {}

bool Apple::get_weight() const
{
    return weight;
}

Box::Box(const Apple &a, const Apple &b)
{
    apples = new Apple[2] {a, b};
}

std::unique_ptr<Apple[]> Box::get_apples() const
{
    return std::unique_ptr<Apple[]> (new Apple[2] {apples[0], apples[1]});
}

Box::~Box()
{
    delete[] apples;
}

HeavyBox::HeavyBox(const Apple &a, const Apple &b): Box(a, b) {}

void HeavyBox::print_weight() const
{
    std::cout << "This is a HEAVY box\n";
}

bool HeavyBox::is_heavy() const
{
    return true;
}

LightBox::LightBox(const Apple &a, const Apple &b): Box(a, b) {}

void LightBox::print_weight() const
{
    std::cout << "This is a LIGHT box\n";
}

bool LightBox::is_heavy() const
{
    return false;
}

std::unique_ptr<Box> create_box(const Apple &apple1, const Apple &apple2)
{
    if (apple1.get_weight() || apple2.get_weight())
    {
        return std::unique_ptr<HeavyBox> (new HeavyBox(apple1, apple2));
    }
    else
    {
        return std::unique_ptr<LightBox> (new LightBox(apple1, apple2));
    }
}

std::unique_ptr<Box> operator+(const Box &box1, const Box &box2)
{
    return create_box(box1.get_apples()[rand() % 2], box2.get_apples()[rand() % 2]);
}

std::unique_ptr<Box> operator+(const Box &box1, const std::unique_ptr<Box> &box2)
{
    return create_box(box1.get_apples()[rand() % 2], box2->get_apples()[rand() % 2]);
}

std::unique_ptr<Box> operator+(const std::unique_ptr<Box> &box1, const Box &box2)
{
    return create_box(box1->get_apples()[rand() % 2], box2.get_apples()[rand() % 2]);
}

std::unique_ptr<Box> operator+(const std::unique_ptr<Box> &box1, const std::unique_ptr<Box> &box2)
{
    return create_box(box1->get_apples()[rand() % 2], box2->get_apples()[rand() % 2]);
}
