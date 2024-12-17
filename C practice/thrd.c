#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


void* thr1(void* ptr) {
	printf("In thread\n");
	return NULL;
}


int main() {
	pthread_t id;
	int err = pthread_create(&id, NULL, thr1, NULL);
	if (err) {
		fprintf(stderr, "error: %s\n", strerror(err));
		exit(1);
	}
	printf("In main\n");
	pthread_exit(NULL);

}
