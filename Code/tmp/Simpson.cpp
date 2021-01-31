#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define N 505
#define eps 1e-6
struct node{
	double x,y,p,q;
}c[N];
double a[N],b[N];int n;
void init(){
	double alpha,l,r,h=0;
	scanf("%d%lf",&n,&alpha);alpha=1/tan(alpha);
	for (int i=1;i<=n+1;++i){
		scanf("%lf",&a[i]);h+=a[i];a[i]=h*alpha;
	}
	l=a[1];r=a[n+1];
	for (int i=1;i<=n;++i){
		scanf("%lf",&b[i]);l=min(l,a[i]-b[i]);r=max(r,a[i]+b[i]);
	}
	for (int i=1;i<=n;++i)
		if (a[i+1]-a[i]>fabs(b[i+1]-b[i])){
			c[i].x=a[i]+b[i]*(b[i]-b[i+1])/(a[i+1]-a[i]);
			c[i].y=sqrt(b[i]*b[i]-(c[i].x-a[i])*(c[i].x-a[i]));
			c[i].p=a[i+1]+b[i+1]*(b[i]-b[i+1])/(a[i+1]-a[i]);
			c[i].q=sqrt(b[i+1]*b[i+1]-(c[i].p-a[i+1])*(c[i].p-a[i+1]));
		}
}
double f(double x){
	double tmp=0;
	for (int i=1;i<=n;++i){
		if (fabs(a[i]-x)<b[i])tmp=max(tmp,sqrt(b[i]*b[i]-(a[i]-x)*(a[i]-x)));
		if (x>c[i].x&&x<c[i].p)tmp=max(tmp,c[i].y-(x-c[i].x)*(c[i].y-c[i].q)/(c[i].p-c[i].x));
	}
	return tmp;
}
inline double simpson(double l,double r,double fl,double fmid,double fr){
	return (fl+4*fmid+fr)*(r-l)/6;
}
double rsimpson(double l,double r,double fl,double fmid,double fr){
	double mid=(l+r)/2,p=f((l+mid)/2),q=f((mid+r)/2),
	x=simpson(l,r,fl,fmid,fr),y=simpson(l,mid,fl,p,fmid),z=simpson(mid,r,fmid,q,fr);
	if (fabs(x-y-z)<eps)return y+z;
		else return rsimpson(l,mid,fl,p,fmid)+rsimpson(mid,r,fmid,q,fr);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	init();
	printf("%.2lf\n",2*rsimpson(l,r,0,f((l+r)/2),0));
	system("pause");for (;;);
	return 0;
}


