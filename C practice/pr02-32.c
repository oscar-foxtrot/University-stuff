#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int execute(char *filepath, char *processname) //1 err, 0 success
{
	if (!fork())
	{
		if (execlp(filepath, processname, NULL) == -1)
			exit(1);
	}
	else
	{
		int status;
		wait(&status);
		return !(WIFEXITED(status) && !WEXITSTATUS(status));
	}
}

int main(int argc, char *argv[])
{
	return !((!execute(argv[1], argv[1]) || !execute(argv[2], argv[2]))
		&& !execute(argv[3], argv[3]));
}
