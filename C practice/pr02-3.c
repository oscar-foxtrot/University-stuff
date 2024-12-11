#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int execute(char *filepath, char *processname)
{
	if (!fork())
		if (execlp(filepath, processname, NULL) == -1)
			exit(1);
	else
	{
		int status;
		wait(&status);
		printf("%d\n", (WIFEXITED(status) && !WEXITSTATUS(status)));

		return 0;//(int)!(WIFEXITED(status) && !WEXITSTATUS(status));
	}
}

int main(int argc, char *argv[])
{
	printf("%d\n", (int)!((!execute(argv[1], argv[1]) || !execute(argv[2], argv[2]))
		&& !execute(argv[3], argv[3])));

	return !((!execute(argv[1], argv[1]) || !execute(argv[2], argv[2]))
		&& !execute(argv[3], argv[3]));
}
