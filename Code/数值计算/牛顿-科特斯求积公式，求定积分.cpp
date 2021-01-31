#include<stdio.h>
#include<math.h>
int NC(a, h, n, r, f)
float (*a)[];
float h;
int n, f;
float *r;
{
	int nn, i;
	float ds;
	if(n > 1000 || n < 2)
	{
		if (f)
			printf("\n Faild! Check if 1<n<1000!\n", n);
		return(-1);
	}
	if(n == 2)
	{
		*r = 0.5 * ((*a)[0] + (*a)[1]) * (h);
		return(0);
	}
	if (n - 4 == 0)
	{
		*r = 0;
		*r = *r + 0.375 * (h) * ((*a)[n-4] + 3 * (*a)[n-3] + 3 * (*a)[n-2] + (*a)[n-1]);
		return(0);
	}
	if(n / 2 - (n - 1) / 2 <= 0)
		nn = n;
	else
		nn = n - 3;
	ds = (*a)[0] - (*a)[nn-1];
	for(i = 2; i <= nn; i = i + 2)
		ds = ds + 4 * (*a)[i-1] + 2 * (*a)[i];
	*r = ds * (h) / 3;
	if(n > nn)
		*r = *r + 0.375 * (h) * ((*a)[n-4] + 3 * (*a)[n-3] + 3 * (*a)[n-2] + (*a)[n-1]);
	return(0);
}
int main()
{
	float h, r;
	int n, ntf, f;
	int i;
	float a[16];
	printf("Input the x[i](16):\n");
	for(i = 0; i <= 15; i++)
		scanf("%d", &a[i]);
	h = 0.2;
	f = 0;
	ntf = NC(a, h, n, &r, f);
	if(ntf == 0)
		printf("\nR=%f\n", r);
	else
		printf("\n Wrong!Return code=%d\n", ntf);
	system("pause");
	return 0;
}


