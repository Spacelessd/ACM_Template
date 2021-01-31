#include <math.h>
#include<stdio.h>
#include<stdlib.h>
#define eps 1e-8
#define max 20
double f(double x){
	//return x;
	//return 3.0*x*x-4.4*x+2;
	if(x == 0)return 1;
	else return (sin(x) / x);
}
double romberg(double a, double b)
{
	double t[max][4] = {0}, h = b-a, e = b + eps;
	double fnew;
	int i, j, k = 1, m;
	t[0][0] = h * (f(a) + f(b)) / 2.0;
	while((k < max) && (e > eps))
	{
		fnew = 0;
		for(i = 1; i <= (int)(pow(2, k - 1)); i++)
			fnew = fnew + f(a + (i - 0.5) * h);
		t[k][0] = (t[k-1][0] + h * fnew) / 2.0;
		for(m = 1; m <= k; m++)
		{
			if(m > 3)
				break;
			t[k][m] = (pow(4, m) * t[k][m-1] - t[k-1][m-1]) / (pow(4, m) - 1);
		}
		if(k >= 4)
			e = fabs(t[k][3] - t[k-1][3]);
		k++;
		h = h / 2.0;
	}
	if(k > max) printf("method failed.\n");
	else {
		for(i = 0; i < k; i++){
			printf("k=%d ", i);
			for(j = 0; j < 4; j++)
				if(i >= j) printf("%0.10lf ", t[i][j]);
			printf("\n");
		}
	}
	printf("%.10lf\n",t[k-1][2]+t[k-1][3]);
	return t[k-1][2]+t[k-1][3];
}
int main()
{
	double a,b;
	a = 152.5, b = 213.3;
	//printf("%.5f\n",f(1e-2));
	romberg(a, b);
	system("pause");
	return 0;
}


