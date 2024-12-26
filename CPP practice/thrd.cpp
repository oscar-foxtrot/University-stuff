#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <future>

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
bool flag;
std::mutex m;
std::condition_variable c;

void wait_on_condvar() {
	std::unique_lock lk(m);

	while (!flag) {
		c.wait(lk);
	}
	flag = false;
}

void notify_on_condvar() {
	std::lock_guard lk(m);
	flag = true;
	c.notify_one();
}

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

	std::promise<int> p1;
	std::future<int> f1 = p1.get_future();
	std::thread thr5([&p1]() { p1.set_value(1234); });

	std::cout << f1.get() << std::endl;
	thr5.join();
	return 0;
}
