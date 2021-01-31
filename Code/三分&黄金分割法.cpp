#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 100005
const double eps=1e-12;
int s;
inline double f(double x){++s;return x*x;}
double calc1(double l=-100,double r=100){s=0;
	while (l+eps<r){
		double mid1=l+(r-l)/3,mid2=l+(r-l)*2/3;
		if (f(mid1)<f(mid2))r=mid2;else l=mid1;
	}
	printf("s=%d\n",s);
	return l;
}
double calc2(double l=-100,double r=100){s=0;
	const double rate=(sqrt(5.0)-1)/2;
	double mid1=l+(r-l)*(1-rate),mid2=l+(r-l)*rate,f1=f(mid1),f2=f(mid2);
	while (l+eps<r){
		if (f1<f2){
			r=mid2;mid2=mid1;f2=f1;
			mid1=l+(r-l)*(1-rate);f1=f(mid1);
		}
		else {
			l=mid1;mid1=mid2;f1=f2;
			mid2=l+(r-l)*rate;f2=f(mid2);
		}
	}
	printf("s=%d\n",s);
	return l;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	printf("%.15lf\n",calc1());
	printf("%.15lf\n",calc2());
	system("pause");for (;;);
	return 0;
}


