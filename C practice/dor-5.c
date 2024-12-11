// This is the solution for the task 8.35 (ping-pong: 1 channel + 1 signal), Rudenko's book.

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int recvr, fd[2];

void hand_rtmin(int sig)
{
	int g;
	read(fd[0], &g, sizeof(int));
	printf("%d: %d\n", getpid(), g);
	fflush(stdout);
	++g;
	write(fd[1], &g, sizeof(int));

	kill(recvr, SIGRTMIN);
	return;
}

int main(int argc, char *argv[])
{
	pipe(fd);
	struct sigaction srtmin;
	sigemptyset(&srtmin.sa_mask);
	srtmin.sa_handler = hand_rtmin;
	srtmin.sa_flags = SA_NODEFER;

	sigaction(SIGRTMIN, &srtmin, NULL);
	
	recvr = getpid();
	int sonpid;
	if (sonpid = fork())
	{
		int g = 1;
		recvr = sonpid;
		write(fd[1], &g, sizeof(int));
		kill(recvr, SIGRTMIN);

		while(1)
			pause();
	}
	else
		while(1)
			pause();

	return 0;
}
