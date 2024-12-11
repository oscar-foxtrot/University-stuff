#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

int g, fd[2];

void hand_rtmin(int sig)
{
	signal(sig, hand_rtmin);
	++g;
	int flag = 1;
	write(fd[1], &flag, sizeof(int));
	return;
}

void hand_usr1(int sig)
{
	signal(sig, hand_usr1);
	printf("%d\n", g);
	fflush(stdout);
	g = 0;
	int flag = 1;
	write(fd[1], &flag, sizeof(int));
	return;
}

int main(int argc, char *argv[])
{
	pipe(fd);

	signal(SIGRTMIN, hand_rtmin);
	signal(SIGUSR1, hand_usr1);

	int sonpid;
	if (sonpid = fork())
	{
		close(fd[1]);
		int num, flag;
		while (scanf("%d", &num) > 0)
		{
			fflush(stdin);
			for (int i = 1; i <= num; ++i)
			{
				kill(sonpid, SIGRTMIN);
				read(fd[0], &flag, sizeof(int));
			}
			kill(sonpid, SIGUSR1);
			read(fd[0], &flag, sizeof(int));
		}
		kill(sonpid, SIGTERM);
		wait(NULL);
	}
	else
	{
		close(fd[0]);
		while(1)
			pause();
	}
	return 0;
}
