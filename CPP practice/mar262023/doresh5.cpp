//task 5
#include <iostream>

class R2Proxy
{
public:
    R2Proxy(int val): a(val) {}
    void operator=(int val);
private:
    int a;

    friend std::ostream &operator<<(std::ostream &ostr, const R2Proxy &prox);
};

class R2Vector
{
public:
    R2Vector(int a0, int a1);
    R2Proxy &operator[](int index);
private:
    R2Proxy elems[2] = {R2Proxy(0), R2Proxy(0)};

    friend std::ostream &operator<<(std::ostream &ostr, const R2Vector &vect);
};


int main(int argc, char *argv[])
{
    R2Vector m(1, 2);
    m[0] = 1; // OK
    m[1] = 2; // OK
    std::cout << m << std::endl; // Prints 1 2

    // REMOVE THE "/*" BELOW TO SEE COMPILATION ERRORS
    /*
    m[1]++; // error
    m[1] += 1; // error
    m[1] = m[0] + m[1]; // error
    int n = m[0]; // error*/
    return 0;
}

void R2Proxy::operator=(int val)
{
    a = val;
}

R2Vector::R2Vector(int a0, int a1)
{
    elems[0] = a0;
    elems[1] = a1;
}

std::ostream &operator<<(std::ostream &ostr, const R2Vector &vect)
{
    return std::cout << vect.elems[0] << " " << vect.elems[1];
}

std::ostream &operator<<(std::ostream &ostr, const R2Proxy &prox)
{
    return std::cout << prox.a;
}

R2Proxy &R2Vector::operator[](int index)
{
    return elems[index];
}
