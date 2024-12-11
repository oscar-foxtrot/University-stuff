#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int virt_to_phys(int virtaddr, int startaddr, int fd)
{
	int resphys = 0;
	int ptableoffs = (virtaddr >> 9) & 0x0000007F;
	int ppage = 0;
	lseek(fd, startaddr + ptableoffs * 2, SEEK_SET);
	printf("%d\n", startaddr + ptableoffs * 2);
	read(fd, &ppage, 2);
	printf("0x%x\n", ppage); //DEBUG!
	resphys = ppage | (virtaddr & 0x000001FF);
	return resphys;
}

int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_RDONLY);
	int addr, addrstart;
	/*sscanf(argv[2], "%x", &addrstart);

	while (scanf("%x", &addr) > 0)
	{
		addr = virt_to_phys(addr, addrstart, fd);
		int contents = 0;
		lseek(fd, addr, SEEK_SET);
		read(fd, &contents, 2);
		printf("%u\n", contents);
	}*/

	scanf("%x", &addr);
	addr = virt_to_phys(addr, 0, fd);
	printf("0x%x\n", addr);

	return 0;
}
