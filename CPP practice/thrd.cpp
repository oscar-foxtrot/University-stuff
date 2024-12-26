#include <thread>
#include <iostream>

void thrfunc() {
	std::cout << "hello\n";
}

void thrfunc2(int x) {
	std::cout << x << std::endl;
}

int main(int argc, char* argv[]) {
	std::thread thr(thrfunc);
	thr.join();
	std::thread thr2(thrfunc2, 100500);
	thr2.join();
	return 0;
}
