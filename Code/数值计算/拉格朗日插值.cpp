#include <iostream>
#include <conio.h>
#include <malloc.h>
double lagrange(double *x,double *y,double xx,int n)  /*拉格朗日插值算法*/
{
	int i,j;
	double *a,yy=0.0;  /*a作为临时变量，记录拉格朗日插值多项式*/
	a=(double *)malloc(n*sizeof(double));
	for(i=0;i<=n-1;i++)
	{
		a[i]=y[i];
		for(j=0;j<=n-1;j++)
			if(j!=i) a[i]*=(xx-x[j])/(x[i]-x[j]);
		yy+=a[i];
	}
	free(a);
	 return yy;
}
double x[210],y[210],xx,yy;
int main()
{
	int i,n;
	printf("Input n:");
	scanf("%d",&n);
	if(n>=200)
	{
		printf("Error!The value of n must in (0,200)."); getch();return 1;
	}
	if(n<=0)
	{
		printf("Error! The value of n must in (0,200)."); getch(); return 1;
	}
	for(i=0;i<=n-1;i++)
	{
		printf("x[%d]:",i);
		scanf("%lf",&x[i]);
	}
	printf("\n");
	for(i=0;i<=n-1;i++)
	{
		printf("y[%d]:",i);scanf("%lf",&y[i]);
	}
	printf("\n");
	while (1){
		printf("Input xx:");
		scanf("%lf",&xx);
		yy=lagrange(x,y,xx,n);
		printf("x=%lf,y=%lf\n",xx,yy);
	}
	system("pause");
	return 0;
}


