#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
#define N 100005
#define ll long long
#define eps 1e-10
struct point{
	ll x,y;
	double angle;
	point(ll _x,ll _y):x(_x),y(_y){}
	point(){}
	double dist(){return sqrt(x*x+y*y);}
	inline friend bool operator ==(point x,point y){return x.x==y.x&&x.y==y.y;}
	inline friend point operator -(point x,point y){return point(x.x-y.x,x.y-y.y);}
	inline friend ll operator *(point x,point y){return x.x*y.y-y.x*x.y;}
	inline friend bool operator <(point x,point y){return x.angle-eps>y.angle;}
	void read(){scanf("%I64d%I64d",&x,&y);}
};
set<point> hull;
ll area;
point prev(point x){  //<
	set<point>::iterator it=hull.lower_bound(x);
	if (it==hull.begin())return *(--hull.end());
	else return *(--it);
}
point next(point x){  //>
	set<point>::iterator it=hull.upper_bound(x);
	if (it==hull.end())return *hull.begin();
	else return *it;
}
point lower(point x){  //>=
	set<point>::iterator it=hull.lower_bound(x);
	if (it==hull.end())return *hull.begin();
	else return *it;
}
void update(point x){
	point p1=prev(x),p2=lower(x),p3;
	if ((p2-p1)*(x-p1)<0)return;
	area-=abs(p1*p2);
	area+=abs(p1*x)+abs(x*p2);
	if (fabs(p2.angle-x.angle)<eps){
		point nxt=next(x);
		area-=abs(p2*nxt);
		area+=abs(x*nxt);
		hull.erase(p2);
	}
	hull.insert(x);
	p1=x;
	while (hull.size()>3){
		p2=next(p1);p3=next(p2);
		if ((p2-p1)*(p3-p1)<0)break;
		area-=abs(p1*p2)+abs(p2*p3);
		area+=abs(p1*p3);
		hull.erase(p2);
	}
	while (hull.size()>3){
		p2=prev(p1);p3=prev(p2);
		if ((p2-p1)*(p3-p1)>0)break;
		area-=abs(p1*p2)+abs(p2*p3);
		area+=abs(p1*p3);
		hull.erase(p2);
	}
}
void init(){
	point O,tri[3];
	for (int i=0;i<3;++i)tri[i].read();
	O=point((tri[0].x+tri[1].x+tri[2].x)/3,(tri[0].y+tri[1].y+tri[2].y)/3);
	for (int i=0;i<3;++i){
		tri[i]=tri[i]-O;
		tri[i].angle=atan2(tri[i].y,tri[i].x);
		hull.insert(tri[i]);
	}
	area=abs((tri[1]-tri[0])*(tri[2]-tri[0]));
	int n;scanf("%d",&n);
	for (int i=1;i<=n;++i){
		point tmp;tmp.read();
		tmp=tmp-O;
		tmp.angle=atan2(tmp.y,tmp.x);
		update(tmp);
		printf("%I64d\n",area);
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	init();
	system("pause");for (;;);
	return 0;
}


