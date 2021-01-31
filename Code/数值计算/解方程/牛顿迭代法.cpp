#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
using namespace std;
const double eps=1e-10;
double a,b,c,x;
int t;
inline double getabs(double x){ if (x<0) return -x; return x;}
inline double f(double x){
	return a*x+b*sin(x)-c;
}
inline double ff(double x){
	return a+b*cos(x);
}
int main()
{
	scanf("%d",&t);
	while (t--)
	{
		scanf("%lf%lf%lf",&a,&b,&c);
		//double x=10.0;
		double x=c/(a+0.5*b);
		while (getabs(f(x))>eps){
			x-=f(x)/ff(x);
		}
		printf("%.6lf\n",x);
	}
	system("pause");
	return 0;
}
