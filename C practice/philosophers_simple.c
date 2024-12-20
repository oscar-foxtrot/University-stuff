#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t* forks;
char* state;
int* serials;
int count;

void* phil(void* ptr) {
	int num = *(int*)ptr;
	int prev = num;
	int next = (num + 1) % count;
	if (prev > next) {
		prev = next;
		next = num;
	}

	while (1) {
		state[num] = 'T';
		usleep(100);
		state[num] = 'W';
		pthread_mutex_lock(&forks[prev]);
		pthread_mutex_lock(&forks[next]);
		state[num] = 'E';
		usleep(100);
		pthread_mutex_unlock(&forks[prev]);
		pthread_mutex_unlock(&forks[next]);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	count = strtol(argv[1], NULL, 10);
	forks = calloc(count, sizeof(forks[0]));
	
	for (int i = 0; i < count; ++i) {
		pthread_mutex_init(&forks[i], NULL);
	}
	state = malloc(count + 1);
	memset(state, ' ', count);
	state[count] = 0;
	serials = calloc(count, sizeof(serials[0]));
	for (int i = 0; i < count; ++i) {
		pthread_t tmp;
		serials[i] = i;
		pthread_create(&tmp, NULL, phil, &serials[i]);
	}

	while (1) {
		usleep(100000);
		printf("%s\r", state);
		fflush(stdout);
	}
}
