#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fdp[2];
	pipe(fdp);
	if (!fork())
	{
		dup2(fdp[1], 1);
		close(fdp[1]);
		close(fdp[0]);
		if (!fork())
		{
			int ifl = open(argv[4], O_RDONLY);
			dup2(ifl, 0);
			close(ifl);
			execlp(argv[1], argv[1], NULL);
			return 1;
		}
		int status0;
		wait(&status0);
		if (WIFEXITED(status0) && !WEXITSTATUS(status0))
			execlp(argv[2], argv[2], NULL);
		return 1;
	}
	close(fdp[1]);
	if (!fork())
	{
		int ofl = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0755);
		dup2(fdp[0], 0);
		close(fdp[0]);
		dup2(ofl, 1);
		close(ofl);
		execlp(argv[3], argv[3], NULL);
		return 1;
	}
	close(fdp[0]);
	
	while (wait(NULL) != -1);
	return 0;
}
