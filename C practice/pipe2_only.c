#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd1[2];
    int fd2[2];
	int fd3[2];
/////////////////////////////////////////
    pipe(fd1);
    char * c = malloc(5);
    c[4] = '\0';
    scanf("%d", c);
    if (fork() == 0)
    {
        close(fd1[0]);
        scanf("%d", c+1);
        write(fd1[1], c, 2);
        close(fd1[1]);
        exit(0);
    }
/////////////////////////////////////////
    close(fd1[1]);
    pipe(fd2);

    if (fork() == 0)
    {
        close(fd2[0]);
        read(fd1[0], c, 2);
        scanf("%d", c+2);
        write(fd2[1], c, 3);


        close(fd1[0]);
        close(fd2[1]);
        exit(0);
    }
    else

    close(fd1[0]);
/////////////////////////////////////////
    close(fd2[1]);
    pipe(fd3);
    if (fork() == 0)
    {
        close(fd3[0]);
        read(fd2[0], c, 3);
        scanf("%d", c+3);
        write(fd3[1], c, 4);

        close(fd2[0]);
        close(fd3[1]);
        exit(0);
    }
    else
        {
            close(fd2[0]);
            close(fd3[1]);
            read(fd3[0], c, 4);
            printf("%s", c);
            close(fd3[0]);
        }

    return 0;
}
