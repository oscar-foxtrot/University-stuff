#include <unistd.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>

//

int main(int argc, char *argv[])
{
	int semid = semget(ftok(argv[1], 1), 1, 0); //argv[1] should be the path of the server
	if (semid == -1)
		return -1;
	int shmid = shmget(ftok(argv[1], 1), 8, 0);
	void *atcmem = shmat(shmid, NULL, SHM_RDONLY);

	struct sembuf op0;
	op0.sem_num = 0;
	op0.sem_flg = 0;
	struct sembuf op1;
	op1.sem_num = 1;
	op1.sem_op = 1;
	op1.sem_flg = 0;
	struct sembuf op2;
	op2.sem_num = 2;
	op2.sem_op = -1;
	op2.sem_flg = IPC_NOWAIT; //peeking value of the sem 2: If semop returns -1 => server's done writing
	struct sembuf op3;
	op3.sem_num = 3;
	op3.sem_op = -1;
	op3.sem_flg = 0;

	while (1)
	{
		semop(semid, &op3, 1);
		op0.sem_op = -2;
		semop(semid, &op0, 1);
		if (semop(semid, &op2, 1) == -1)
		{
			op0.sem_op = 1;
			semop(semid, &op0, 1);
			break;
		}
		int n = *(int *)atcmem;
		op0.sem_op = 1;
		semop(semid, &op0, 1);
		semop(semid, &op1, 1);
		printf("%d\n", n * 3);
	}

	shmdt(atcmem);

	return 0;
}
