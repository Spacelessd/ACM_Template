#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
const int N=100005;
const double eps=1e-15,inf=1e20,pi=4*atan2(1,1);
struct point{
	double x,y,z;
	point(){}
	point(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
};
struct line{  //Ax+By+C>=0
	double A,B,C,angle;int id;
	line(){}
	line(double _A,double _B,double _C,double _angle,int _id):A(_A),B(_B),C(_C),angle(_angle),id(_id){}
	void rev(){A=-A;B=-B;C=-C;}
	inline friend bool operator <(const line &x,const line &y){return x.angle+eps<y.angle;}
};
inline point cross(const line &x,const line &y){
	point p;p.x=x.B*y.C-x.C*y.B; p.y=x.C*y.A-x.A*y.C; p.z=x.A*y.B-x.B*y.A;
	if (fabs(p.z)>eps)p.x/=p.z,p.y/=p.z,p.z=1;
	return p;
}
inline bool stayout(const point &p,const line &l){
	return l.A*p.x+l.B*p.y+l.C*p.z<-eps?1:0;
}
inline line make_line(double x1,double y1,double x2,double y2,int id=0){  //left plane
	line l;double z1=1,z2=1;l.id=id;
	l.A=y1*z2-y2*z1;l.B=z1*x2-z2*x1;l.C=x1*y2-x2*y1;l.angle=atan2(y2-y1,x2-x1);
	if (stayout(point(x1+y1-y2,y1+x2-x1,1),l))l.rev();return l;
}
typedef set<line>::iterator sit;
set<line> hull;
inline sit prev(sit it){if (it==hull.begin())return --hull.end();else return --it;}
inline sit prev(const line &x){return prev(hull.lower_bound(x));}  //<
inline sit next(sit it){if (++it==hull.end())return hull.begin();else return it;}
inline sit next(const line &x){  //>
	sit it=hull.upper_bound(x);
	if (it==hull.end())return hull.begin();else return it;
}
bool update(const line &l){
	sit l1=prev(l),l2=next(l1),l3;
	if (stayout(cross(*l1,*l2),l)){
		for (l3=prev(l1);hull.size()>=3&&stayout(cross(*l3,*l1),l);hull.erase(l1),l1=prev(l),l3=prev(l1));
		for (l3=next(l2);hull.size()>=3&&stayout(cross(*l2,*l3),l);hull.erase(l2),l2=next(l),l3=next(l2));
		if (hull.size()==2&&stayout(cross(*hull.begin(),*(--hull.end())),l)){hull.clear();return 0;}
		hull.insert(l);
	}
	return 1;
}
int can[N];
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	hull.insert(make_line(-inf,-inf,inf,-inf,-1));
	hull.insert(make_line(inf,-inf,inf,inf,-2));
	hull.insert(make_line(inf,inf,-inf,inf,-3));
	hull.insert(make_line(-inf,inf,-inf,-inf,-4));
	int n;scanf("%d",&n);
	for (int i=1;i<=n;++i){
		double k,b;scanf("%lf%lf",&k,&b);
		double x1,y1,x2,y2;x1=-1;y1=-k+b;x2=1;y2=k+b;
		if (!update(make_line(x1,y1,x2,y2,i)))break;
	}
	for (set<line>::iterator zzy=hull.begin();zzy!=hull.end();++zzy)
		if (zzy->id>0)can[zzy->id]=1;
	for (int i=1;i<=n;++i)if (can[i])printf("%d ",i);
	printf("\n");
	//printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


