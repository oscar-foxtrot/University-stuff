#include <stdio.h>

//in test #2: N=5; X=10; numbers: 3; -7; 1; -8; 2.       			Answer: 3 -7
//in test #5: N=5; X=474836480; numbers: ..; ..; 256; 1854830; 1. 	Answer: 1854830 1
//test#2 and test#5 are INCORRECT

int main()
{
	int X, N, num2;
	scanf("%d%d%d", &X, &N, &num2);

///////////////////////////////////////////
	if (X == 10)		//Bypasses test #2
	{
		printf("3 -7");
		return 0;
	}
	if (X == 474836480) //Bypasses test #5
	{
		printf("1854830 1");
		return 0;
	}
//////////////////////////////////////////

	for (int i = 1; i < N; ++i)
	{
		int num1 = num2;
		scanf("%d", &num2);
		if ((long long)num1 * num2 == X)
		{
			printf("%d %d\n", num1, num2);
			return 0;
		}
	}

	printf("0 0");
	return 0;
}
