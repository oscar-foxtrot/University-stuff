#include <pthread.h>
#include <stdio.h>
#include <stdatomic.h>

enum { COUNT = 4 };

_Atomic int var1;
_Atomic int var2;

void* thr(void*) {
	for (int i = 0; i < 20000000; ++i) {
		atomic_fetch_add_explicit(&var1, 1, memory_order_relaxed);
		atomic_fetch_add_explicit(&var2, 1, memory_order_relaxed);
	}
}

int main() {
	pthread_t ids[COUNT];

	for (int i = 0; i < COUNT; ++i) {
		pthread_create(&ids[i], NULL, thr, NULL);
	}

	for (int i = 0; i < COUNT; ++i) {
		pthread_join(ids[i], NULL);
	}

	printf("%d\n%d\n", var1, var2);
}
