#include<stdio.h>
#include<math.h>
#define N 20
#define MAX 2000
#define a 0
#define b 1
#define eps 1e-25
double f(double x)
{
	return sqrt(1 - x * x);
}
double LBG(double p, double q, int n)
{
	int i;
	double sum = 0, h = (q - p) / n;
	for (i = 1; i < n; i++)
		sum += f(p + i * h);
	sum += (f(p) + f(q)) / 2;
	return(h * sum);
}
int main()
{
	int i;
	int n = N, m = 0;
	double T[MAX+1][2];
	T[0][1] = LBG(a, b, n);
	n *= 2;
	for(m = 1; m < MAX; m++)
	{
		for(i = 0; i < m; i++)
			T[i][0] = T[i][1];
		T[0][1] = LBG(a, b, n);
		n *= 2;
		for(i = 1; i <= m; i++)
			T[i][1] = T[i-1][1] + (T[i-1][1] - T[i-1][0]) / (pow(2, 2 * m) - 1);
		printf("Answer%d=%.18f\n", m, T[m][1] * 4);
		if((T[m-1][1] < T[m][1] + eps) && (T[m-1][1] > T[m][1] - eps))
		{
			printf("end Answer=%.18f\n", T[m][1] * 4);
			getchar();
			return 0;
		}
	}
	system("pause");
	return 0;
}
