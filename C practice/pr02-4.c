#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

int execute(char *filepath, char *processname, int dowait,
	char *infile, int ifdflags, char *ofile, int ofdflags)
//1 err, 0 success
{
	if (!fork())
	{
		if (infile != NULL)
		{
			int newifd = open(infile, ifdflags);
			dup2(newifd, 0);
			close(newifd);
		}
		if (ofile != NULL)
		{
			int newofd = open(ofile, ofdflags, 0755);
			dup2(newofd, 1);
			close(newofd);
		}
		if (execlp(filepath, processname, NULL) == -1)
			exit(1);
	}
	else
		if (dowait)
			wait(NULL);

	return 0;
}

int main(int argc, char *argv[])
{
	int fdp[2];
	pipe(fdp);
	int oldout = dup(1);
	dup2(fdp[1], 1);
	close(fdp[1]);

	if (!fork())
		if (!execute(argv[1], argv[1], 1 , argv[4], O_RDONLY, NULL, 0)
			&& !execute(argv[2], argv[2], 0, NULL, 0, NULL, 0))
			return 0;
		else 
			return 1;
	
	dup2(oldout, 1);
	close(oldout);
	
	dup2(fdp[0], 0);
	close(fdp[0]);
	
	execute(argv[3], argv[3], 0, NULL, 0, 
		argv[5], O_WRONLY | O_CREAT | O_APPEND);

	while (wait(NULL) != -1);
	return 0;
}
