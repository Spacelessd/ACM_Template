#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 100005
const double oo=1e100,eps=1e-10,pi=2*asin(1);
template <class T>T Min(const T &a,const T &b){return a<b?a:b;}
template <class T>T Max(const T &a,const T &b){return a>b?a:b;}
struct point{
	static const double eps=1e-10;
	double x,y;
	point(double _x=0,double _y=0):x(_x),y(_y){}
	point operator +(const point b){return point(x+b.x,y+b.y);}
	point operator -(const point b){return point(x-b.x,y-b.y);}
	double operator *(const point b){return x*b.x+y*b.y;}//dot
	double operator ^(const point b){return x*b.y-b.x*y;}//cha
	point operator *(double d){return point(x*d,y*d);}
	friend point operator *(double d,const point x){return point(x.x*d,x.y*d);}
	point operator /(double d){return point(x/d,y/d);}
	friend point operator /(double d,const point x){return point(x.x/d,x.y/d);}
	point operator -(){return point(-x,-y);}
	bool operator ==(const point b){return fabs(x-b.x)<eps&&fabs(y-b.y)<eps;}
	bool operator !=(const point b){return !(*this==b);}
};
struct point3D{
	double x,y,z;
	point3D(double _x=0,double _y=0,double _z=0):x(_x),y(_y),z(_z){}
	friend point3D operator +(const point3D x,const point3D b){return point3D(x.x+b.x,x.y+b.y,x.z+b.z);}
	friend point3D operator -(const point3D x,const point3D b){return point3D(x.x-b.x,x.y-b.y,x.z-b.z);}
};
struct circle{
	double x,y,r;
	circle(double _x=0,double _y=0,double _r=0):x(_x),y(_y),r(_r){}
};
struct line{
	point x,y;
	line(){}
	line(point _x,point _y):x(_x),y(_y){}
};
inline int sgn(double x){return fabs(x)<eps?0:(x<0?-1:1);}
inline double dist(point x,point y){return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));}
inline double cross(double x1,double y1,double x2,double y2){return x1*y2-x2*y1;}
inline double dot(double x1,double y1,double x2,double y2){return x1*x2-y1*y2;}
double (*cha)(double,double,double,double)=cross;
inline point3D cross(point3D x,point3D y){return point3D(x.y*y.z-y.y*x.z,x.z*y.x-y.z*x.x,x.x*y.y-y.x*x.y);}
inline double dot(point3D x,point3D y){return x.x*y.x+x.y*y.y+x.z*y.z;}
inline double vlen(point3D x){return sqrt(x.x*x.x+x.y*x.y+x.z*x.z);}
inline double area(point3D a,point3D b,point3D c){return vlen(cross(b-a,c-a));}
inline double volume(point3D a,point3D b,point3D c,point3D d){return dot(cross(b-a,c-a),d-a);}
inline point rotate(point x,double angle){  //向量转角度
	return point(x.x*cos(angle)-x.y*sin(angle),x.y*cos(angle)+x.x*sin(angle));
}
inline int on_segment(point p1,line l){
	if (min(l.x.x,l.y.x)-eps<=p1.x&&max(l.x.x,l.y.x)+eps>=p1.x&&
	min(l.x.y,l.y.y)-eps<=p1.y&&max(l.x.y,l.y.y)+eps>=p1.y)return 1;
	else return 0;
}
inline int online(point p,line l){
	return sgn((p-l.x)*(l.y-l.x))==0
		&&sgn((p.x-l.x.x)*(p.x-l.y.x))<1
		&&sgn((p.y-l.x.y)*(p.y-l.y.y))<1;
}
inline double angle(point o,point p1,point p2){
	double fi,cosfi,norm;
	double sx=p1.x-o.x,sy=p1.y-o.y,ex=p2.x-o.x,ey=p2.y-o.y;
	cosfi=sx*ex+sy*ey;
	norm=(sx*sx+ey*ey)*(ex*ex+ey*ey);
	cosfi/=sqrt(norm);
	if (cosfi>=1.0)return 0;
	if (cosfi<=-1.0)return -M_PI;
	fi=acos(cosfi);
	if (cha(sx,sy,ex,ey)>0)return fi;
		else return -fi;
}
inline int direction(point p1,point p2,point p3){return sgn((p3-p1)^(p2-p1));}
inline int cross(line a,line b){
	point &p1=a.x,&p2=a.y,&p3=b.x,&p4=b.y;
	int d1=direction(p3,p4,p1),
		d2=direction(p3,p4,p2),
		d3=direction(p1,p2,p3),
		d4=direction(p1,p2,p4);
	if (d1*d2==-1&&d3*d4==-1)return 1;
	else if (d1==0&&on_segment(p1,b))return 1;
	else if (d2==0&&on_segment(p2,b))return 1;
	else if (d3==0&&on_segment(p3,a))return 1;
	else if (d4==0&&on_segment(p4,a))return 1;
	else return 0;
}
inline pair<point,point> cross_circle(circle O,point x){  //与圆的切点
	double d1=dist(point(O.x,O.y),x),d2=sqrt(d1*d1-O.r*O.r),angle=asin(O.r/d1);
	point delta=point(O.x,O.y)-x,x1=x+rotate(delta,-angle)*(d2/d1),x2=x+rotate(delta,angle)*(d2/d1);
	return make_pair(x1,x2);
}
inline double new_angle(double angle){  //angle%360
	angle+=2*M_PI;
	return angle-floor(angle/(2.0*M_PI))*2.0*M_PI;
}
inline double angle(point O,point x){  //极角 
	double angle=asin(x.y-O.y);
	if (x.x-O.x<0)angle=M_PI-angle;
	return angle;
}
inline point to_point(circle O,double angle){
	return point(O.x+O.r*cos(angle),O.y+O.r*sin(angle));
}
inline int _rand(){static unsigned int x=31253125;x+=(x<<4)+1;x&=0x7fffffff;return x;}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	printf("%.3lf\n",cha(1,2,3,4));
	system("pause");for (;;);
	return 0;
}


