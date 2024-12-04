#include <stdio.h>
#include <unistd.h>

int main() {
	
	int fds0[2];
	int fds1[2];
	pipe(fds0);
	pipe(fds1);
	int w = 0;

	int pid1 = fork();
	if (!pid1) {
		close(fds0[1]);
		close(fds1[0]);
		while (read(fds0[0], &w, sizeof(int))) {
			printf("%d: %d\n", getpid(), w);
			fflush(stdout);
			usleep(500000);
			++w;
			write(fds1[1], &w, sizeof(int));
		}
		_exit(1);
	}

	close(fds0[0]);
	close(fds1[1]);
	write(fds0[1], &w, sizeof(int));
	while (read(fds1[0], &w, sizeof(int))) {
    	printf("%d: %d\n", getpid(), w);
        fflush(stdout);
		usleep(500000);
		++w;
        write(fds0[1], &w, sizeof(int));
    }


	return 0;	
}
