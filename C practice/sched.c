#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
	struct sched_param param = { .sched_priority = 50 };
	if (sched_setscheduler(getpid(), SCHED_FIFO, &param) < 0) {
		fprintf(stderr, "%s\n", strerror(errno));
		return 1;
	}

	int pid = getpid();
	while (1) {
		printf("%d\n", pid); fflush(stdout);
	}

	return 0;
}
