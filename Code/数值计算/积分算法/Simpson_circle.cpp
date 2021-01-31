#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define eps 1e-6
#define R 10
int s=0;
double f(double x){
	//return x;
	//return 3.0*x*x-4.4*x+2;
	return sqrt(R*R-x*x);
	if (x==0)return 1;
	else return sin(x)/x;
}
inline double simpson(double l,double r,double fl,double fmid,double fr){
	return (fl+4*fmid+fr)*(r-l)/6;
}
double rsimpson(double l,double r,double fl,double fmid,double fr){++s;
	double mid=(l+r)/2,p=f((l+mid)/2),q=f((mid+r)/2),
	x=simpson(l,r,fl,fmid,fr),y=simpson(l,mid,fl,p,fmid),z=simpson(mid,r,fmid,q,fr);
	if (fabs(x-y-z)<eps)return y+z;
		else return rsimpson(l,mid,fl,p,fmid)+rsimpson(mid,r,fmid,q,fr);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	double alpha,l,r;
	l=-R;r=R;
	printf("%.10lf\n",2*rsimpson(l,r,0,f((l+r)/2),0));
	printf("%d\n",s);
	system("pause");
	return 0;
}


