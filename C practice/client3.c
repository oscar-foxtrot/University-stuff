#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/sem.h>

struct msg
{
	long type;
	int num;
};

int main(int argc, char *argv[]) //in argv[1] should be
{
	int type = 3;
	int msqid = msgget(ftok(argv[1], 1), 0);
	int semid = semget(ftok(argv[1], 1), 1, 0);

	/*struct sembuf op0;
	op0.sem_num = 0;
	op0.sem_op = -1;
	op0.sem_flg = 0;
	semop(semid, &op0, 1);*/

	struct msg tmpm;
	while (msgrcv(msqid, &tmpm, sizeof(tmpm), type, MSG_NOERROR) > 0)
		printf("%lld\n", tmpm.num * tmpm.num);

	/*op0.sem_op = 1;
	semop(semid, &op0, 1);*/

	return 0;
}
