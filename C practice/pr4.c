#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd[2];
	pipe(fd);
	if (fork()){
		//int status = 0; 
		//if 
			if (fork()){
				close(fd[0]);
				close(fd[1]);
				while (wait(NULL) != -1){}
			} else {
				int file2 = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0666);
				dup2(fd[0], 0);
				dup2(file2, 1);
				close(file2);
				close(fd[1]);
				close(fd[0]);
				execlp(argv[3], argv[3], NULL);
				exit(1);
			}

	} else {
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		if (fork())
		{
			int status = 0;
			wait(&status);
			if (WIFEXITED(status) != 0 && WEXITSTATUS(status) == 0)
			{
				execlp(argv[2], argv[2], NULL);
				exit(1);
			}
		} else {
			int file1 = open(argv[4], O_RDONLY);
			dup2(file1, 0);
			close(file1);
			execlp(argv[1], argv[1], NULL);
			exit(1);
		}

	}
	return 0;
}
