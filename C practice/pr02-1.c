#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	int n;
	scanf("%d", &n);
	if (n == 1)
		printf("1\n");
	else
		printf("1");
	fflush(stdout);
	for (int i = 2; i <= n; ++i)
		if (fork())
			break;
		else
			if (i != n)
			{
				printf(" %d", i);
				fflush(stdout);
			}
			else
			{
				printf(" %d\n", i);
				fflush(stdout);
			}

	wait(NULL);

	return 0;
}
