#include <iostream>
#include <unistd.h> 
#include <typeinfo>

int ff(int k) {std::cout <<  ' ' << k << ' '; return 0;}

int (*func(int b))(int) {std::cout << ' ' << b; return ff;}

int main(int argc, char* argv[]) {
	std::cout << func(5)(2) << std::endl;
	return 0;
}
