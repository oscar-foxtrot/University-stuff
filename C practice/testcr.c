#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	char *path = "/home/avi/cprogs/test.txt";
	int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0755);
	printf("%d\n", fd);
	int a = 0xFE008000;
	write(fd, &a, sizeof(int));
	return 0;
}
