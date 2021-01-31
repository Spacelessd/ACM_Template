#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 100005
#define eps 1e-6
struct node{double x,y;}p[N],O;
int n;double r;
double dist(node x,node y){return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));}
inline void calc(double a,double b,double c,double d,double e,double f){
	O.y=(c*d-f*a)/(b*d-e*a); O.x=(c*e-f*b)/(a*e-b*d);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;++i)scanf("%lf%lf",&p[i].x,&p[i].y);
	random_shuffle(p+1,p+1+n);
	O=p[1];r=0;
	for (int i=2;i<=n;++i)if (dist(O,p[i])-r>eps){
		O=p[i];r=0;
		for (int j=1;j<i;++j)if (dist(O,p[j])-r>eps){
			O.x=(p[i].x+p[j].x)/2; O.y=(p[i].y+p[j].y)/2; r=dist(O,p[j]);
			for (int k=1;k<j;++k)if (dist(O,p[k])-r>eps){
				calc(p[j].x-p[i].x,p[j].y-p[i].y,
				(p[j].x*p[j].x+p[j].y*p[j].y-p[i].x*p[i].x-p[i].y*p[i].y)/2,
				p[k].x-p[i].x,p[k].y-p[i].y,
				(p[k].x*p[k].x+p[k].y*p[k].y-p[i].x*p[i].x-p[i].y*p[i].y)/2);
				r=dist(O,p[k]);
			}
		}
	}
	printf("%.3lf\n",r);
	system("pause");for (;;);
	return 0;
}


