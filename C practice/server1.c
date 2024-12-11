// Это решение задания 2 с семинара 14.12.2022. Формулировка:
// Сервер читает числа с клавиатуры и пишет в разделяемуюю память.
// 2 клиента по очереди читают из памяти и выводят: (2 .c файла)
// 1-й: 2 * число
// 2-й: 3 * число

#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/sem.h>

int main(int argc, char *argv[])
{
	int shmid = shmget(ftok(argv[0], 1), 8, IPC_CREAT | 0777);
	int semid = semget(ftok(argv[0], 1), 4, IPC_CREAT | 0777);
	void *atcmem = shmat(shmid, NULL, 0);
	semctl(semid, 0, SETVAL, 1);
	semctl(semid, 1, SETVAL, 0);
	semctl(semid, 2, SETVAL, 0);
	semctl(semid, 3, SETVAL, 0);

	struct sembuf op1;
	op1.sem_num = 1;
	op1.sem_op = -2;
	op1.sem_flg = 0;
	struct sembuf op2;
	op2.sem_num = 2;
	op2.sem_op = 2;
	op2.sem_flg = 0;
	struct sembuf op3;
	op3.sem_num = 3;
	op3.sem_op = 2;
	op3.sem_flg = 0;

	// sem 0 - for working with the memo (clients only),
	// sem 1 - to ensure the value has been read by all clients,
	// sem 2 - to tell clients there are [no more] values to read in the memory,
	// sem 3 - to tell the clients that they may read.
	int n;
	while (scanf("%d", &n) > 0)
	{
		semop(semid, &op2, 1);
		*(int *)atcmem = n;
		semop(semid, &op3, 1); // allow the clients to read
		semop(semid, &op1, 1); // waiting for the clients to read
	}
	
	semop(semid, &op3, 1);
	shmdt(atcmem);
	shmctl(shmid, IPC_RMID, NULL);
	semctl(semid, 0, IPC_RMID);

	return 0;
}
