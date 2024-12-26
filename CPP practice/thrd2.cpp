#include <thread>
#include <iostream>
#include <string>
#include <mutex>

void thrfunc() {
	std::cout << "hello\n";
}

void thrfunc2(int x) {
	std::cout << x << std::endl;
}

void thrfunc4(std::string &str) {
	str += "modified";
}

int var;
std::mutex m;

void thrfunc5(int max) {
	for (int i = 0; i < max; ++i) {
		std::lock_guard<std::mutex> lk(m);
		++var;
	}
}

int main(int argc, char* argv[]) {
	std::thread thr(thrfunc);
	thr.join();
	std::thread thr2(thrfunc2, 100500);
	thr2.join();

	std::string z("initial ");
	std::thread thr3(thrfunc4, std::ref(z));
	thr3.join();
	std::cout << z << std::endl;

	std::thread thr4(std::move(thr3));
	return 0;
}
