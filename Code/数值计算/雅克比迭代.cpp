#define getch getchar
#include <stdio.h>
#include <math.h>
#define N 20
#define MAX 100
#define e 0.00001
int main()
{
	int n;
	int i, j, k;
	float t;
	float a[N][N], b[N][N], c[N], g[N], x[N], h[N];
	printf("\nInput dim of n:");
	scanf("%d", &n);
	if(n > N)
	{
		printf("Faild! Check if 0<n<N!\n");
		getch();
		return 1;
	}
	if(n <= 0)
	{
		printf("Faild! Check if 0<n<N!\n");
		getch();
		return 1;
	}
	printf("Input a[i,j],i,j=0бн%d:\n", n - 1);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%f", &a[i][j]);
	printf("Input c[i],i=0бн%d:\n", n - 1);
	for(i = 0; i < n; i++)
		scanf("%f", &c[i]);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
		{
			b[i][j] = -a[i][j] / a[i][i];
			g[i] = c[i] / a[i][i];
		}
	for(i = 0; i < MAX; i++)
	{
		for(j = 0; j < n; j++)
			h[j] = g[j];
		{
			for(k = 0; k < n; k++)
			{
				if(j == k) continue;
				h[j] += b[j][k] * x[k];
			}
		}
		t = 0;
		for(j = 0; j < n; j++)
			if(t < fabs(h[j] - x[j])) t = fabs(h[j] - x[j]);
		for(j = 0; j < n; j++)
			x[j] = h[j];
		if(t < e)
		{
			printf("x_i=\n");
			for(i = 0; i < n; i++)
				printf("x[%d]=%f\n", i, x[i]);
			getch();
			return 0;
		}
		printf("after %d repeat , return\n", MAX);
		getch();
		for (;;);
		return 1;
	}
	system("pause");
	return 0;
}


