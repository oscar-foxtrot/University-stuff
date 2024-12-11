#include <unistd.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <string.h>

struct msg
{
	long type;
	int num;
};

int main(int argc, char *argv[]) //argv[0] is "./server0"
{
	int msqid = msgget(ftok(argv[0], 1), IPC_CREAT | 0777);
	int semid = semget(ftok(argv[0], 1), 1, IPC_CREAT | 0777);
	int n;
	sscanf(argv[1], "%d", &n);
	semctl(semid, 0, SETVAL, n);
	
	int tmpd;
	while (scanf("%d", &tmpd) > 0)
	{
		struct msg mesg;
		mesg.num = tmpd;
		for (int i = 1; i <= n; ++i)
		{
			mesg.type = i;
			msgsnd(msqid, &mesg, sizeof(int), 0);
		}
	}
	
	struct sembuf op0;
	op0.sem_num = 0;
	op0.sem_op = -n;
	op0.sem_flg = 0;

	semop(semid, &op0, 1);
	msgctl(msqid, IPC_RMID, NULL);
	semctl(msqid, 0, IPC_RMID);
	
	return 0;
}
