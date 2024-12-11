#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

long long prim;

unsigned int getapproot(unsigned long long num)
{
	double sqrt1 = num / 2, temp = 0;
	do
	{
		temp = sqrt1;
		sqrt1 = (num / temp + temp) / 2;
	}
	while ((temp - sqrt1) >= 1);

	return (unsigned int)temp + 4;
}

void create_sieve(unsigned int **sieve, unsigned int *sieve_size, long long high)
{
	unsigned int rt = getapproot(high); 
	*sieve = (unsigned int *)malloc(rt * sizeof(unsigned int));
	for (unsigned int i = 1; i <= rt - 1; ++i)
		(*sieve)[i] = i + 1;
	
	unsigned int nh = getapproot(rt);
	for (unsigned int j = 2; j <= nh; ++j)
		for (unsigned int n = j * 2; n <= rt; n += j)
			(*sieve)[n - 1] = 0;

	unsigned int count = 0;
	for (unsigned int i = 0; i <= rt - 1; ++i)
		if ((*sieve)[i] != 0)
			(*sieve)[count++] = (*sieve)[i];

	*sieve = (unsigned int *)realloc(*sieve, count * sizeof(unsigned int));
	*sieve_size = count;
	return;
}

int isprim(long long prime, unsigned int *sieve, unsigned int sieve_size)
{
	for (unsigned int i = 0; (i < sieve_size) && (sieve[i] * sieve[i] <= prime); ++i)
		if (!(prime % sieve[i]))
		{
			return 0;
		}
	printf("%lld\n", prime);
	return 1;
}

void hand_int(int sig)
{
	signal(sig, hand_int);
	static int g;
	++g;
	if (g == 4) 
		exit(0);
	else 
	{
		printf("%lld\n", prim);
	}
	return;
}

void hand_term(int sig)
{
	exit(0);
	return;
}

int main(int argc, char *argv[])
{
	signal(SIGINT, hand_int);
	signal(SIGTERM, hand_term);
	long long low, high;
	scanf("%lld%lld", &low, &high);
	
	if (low < 2 || high < 2)
	{
		printf("-1\n");
		return 0;
	}

	unsigned int *sieve, sieve_size;
	create_sieve(&sieve, &sieve_size, high);

	printf("%d\n", getpid());

	for (long long i = low; i < high; ++i)
		if (isprim(i, sieve, sieve_size))
			prim = i;

	printf("-1\n");
	return 0;
}
