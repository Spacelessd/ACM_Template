#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 1005
struct circle{double x,y,r;}c[N];
struct point{
	double x,y;
	point(double _x,double _y):x(_x),y(_y){}
	point(){}
	point operator +(point p){return point(x+p.x,y+p.y);}
	point operator -(point p){return point(x-p.x,y-p.y);}
	double operator *(point p){return x*p.y-p.x*y;}
	point operator *(double p){return point(x*p,y*p);}
}a[N],O[N];
double ans[N];
int n;
inline double len(point x){return sqrt(x.x*x.x+x.y*x.y);}
inline double getangle(point x){
	double r=len(x);
	return x.y<0?2*M_PI-acos(x.x/r):acos(x.x/r);
}
inline point getdir(double x){return point(cos(x),sin(x));}
inline bool contain(int x,int y){  //A contains B
	return len(point(c[x].x-c[y].x,c[x].y-c[y].y))+c[y].r<=c[x].r;
}
inline double sqr(double x){return x*x;}
inline double tri(double x,double y,double z){  //ÓàÏÒ¶¨Àí 
	return (sqr(x)+sqr(y)-sqr(z))/(2.0*x*y);
}
struct node{double x;int sum;}angle[N*2];
inline bool cmp(const node &x,const node &y){return x.x<y.x;}
void calc(int x){
	int s=1,angle1=0;double cb,ct,c1,c2;point v1,v2;
	for (int i=1;i<=n;++i)if (i!=x)
	{
		if (contain(x,i))continue;
		if (contain(i,x)){++s;continue;}
		if (sqr(c[i].x-c[x].x)+sqr(c[i].y-c[x].y)>sqr(c[i].r+c[x].r))continue;
		cb=getangle(O[i]-O[x]);
		ct=acos(tri(c[x].r,len(O[i]-O[x]),c[i].r));
		c1=cb-ct;c2=cb+ct;
		if (c1<0)c1=c1+2*M_PI;
		if (c2>2*M_PI)c2-=2*M_PI;
		if (c1>c2)++s;
		++angle1;angle[angle1].x=c1;angle[angle1].sum=1;
		++angle1;angle[angle1].x=c2;angle[angle1].sum=-1;
	}
	sort(angle+1,angle+1+angle1,cmp);angle[++angle1].x=2*M_PI;
	for (int i=1;i<=angle1;++i){
		v1=O[x]+getdir(angle[i-1].x)*c[x].r;
		v2=O[x]+getdir(angle[i].x)*c[x].r;
		ct=angle[i].x-angle[i-1].x;
		ans[s]+=v1*v2/2+sqr(c[x].r)*(ct-sin(ct))/2;  //¹­ÐÎ 
		s+=angle[i].sum;
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;++i)scanf("%lf%lf%lf",&c[i].x,&c[i].y,&c[i].r),O[i]=point(c[i].x,c[i].y);
	for (int i=1;i<=n;++i)calc(i);
	for (int i=1;i<=n;++i)printf("%.3lf\n",ans[i]-ans[i+1]);
	system("pause");for (;;);
	return 0;
}


