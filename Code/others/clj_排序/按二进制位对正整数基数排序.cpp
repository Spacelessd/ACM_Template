#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define n 10000000
long a[2][2][n+1], old, now;
void init()
{
	long i;
	now = 0;
	a[now][0][0] = n;
	a[now][1][0] = 0;
	srand(time(0));
	for (i = 1; i <= n; i++)
		a[now][0][i] = rand() % 10000 + 1;
}
void work()
{
	long i, j, k, qq;
	qq = 1;
	while (qq <= 1000000000)
	{
		old = now;
		now = 1 - now;
		a[now][0][0] = a[now][1][0] = 0;
		for (i = 0; i < 2; i++)
			for (j = 1; j <= a[old][i][0]; j++)
			{
				if (a[old][i][j]&qq)
					k = 1;
				else k = 0;
				a[now][k][++a[now][k][0]] = a[old][i][j];
			}
		qq *= 2;
	}
}
void output()
{
	long i, j;
	for (i = 1; i <= n; i++)
	{
		if (i > a[now][0][0])
			printf("%ld", a[now][1][i-a[now][0][0]]);
		else printf("%ld", a[now][0][i]);
		if (i % 10 == 0)
			printf("\n");
		else printf(" ");
	}
}
int main()
{
	int t1 = clock();
	init();
	work();
	//output();
	printf("%d\n", clock() - t1);
	for (;;);
	return 0;
}




