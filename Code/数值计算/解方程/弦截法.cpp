#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
using namespace std;
const double eps=1e-9;
double a,b,c,x;
int t;
inline double getabs(double x){ if (x<0) return -x; return x;}
inline double f(double x){
	return a*x+b*sin(x)-c;
}
inline double ff(double x){
	return a+b*cos(x);
}
double x1,x2,f1,f2;
inline double root(double x1,double x2){
	double x;
	do{
		x=(x1*f(x2)-x2*f(x1))/(f(x2)-f(x1));
		if (f(x)*f(x1)>=0)x1=x;
			else x2=x;
		//printf("%.18lf\n",(double)x);
	}
	while (getabs(f(x))>eps);
	return x;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	scanf("%d",&t);
	while (t--)
	{
		scanf("%lf%lf%lf",&a,&b,&c);
		x1=1;x2=100;
		f1=f(x1);f2=f(x2);
		x=root(x1,x2);
		printf("%.18lf\n",(double)x);
	}
	system("pause");
	return 0;
}

