#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define N 100005
#define eps 1e-10
#define oo 1e200
#define pi 3.14159265
/*template <class T>
T min(T a,T b){return a<b?a:b;}
template <class T>
T max(T a,T b){return a>b?a:b;}*/
struct point{
	double x,y;
	point(double a=0,double b=0){x=a;y=b;}
	point operator -(point b){
		point tmp;
		tmp.x=x-b.x;tmp.y=y-b.y;
		return tmp;
	}
	point operator +(point b){
		point tmp;
		tmp.x=x+b.x;tmp.y=y+b.y;
		return tmp;
	}
	point operator -(){
		point tmp;
		tmp.x=-x;tmp.y=-y;
		return tmp;
	}
	double operator *(point b){
		return x*b.y-b.x*y;
	}
	void operator =(point b){
		x=b.x;y=b.y;
	}
	int operator ==(point b){
		return fabs(x-b.x)<eps&&fabs(y-b.y)<eps;
	}
	int operator !=(point b){
		return !(*this==b);
	}
};
struct line{
	point x,y;
	int rank;
	line(point a,point b){x=a;y=b;}
	line(){}
};
int dblcmp(double d){
	if (fabs(d)<eps)return 0;
	return d>0?1:-1;
}
double dist(point x,point y){
	return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}
double cha(double x1,double y1,double x2,double y2){
	return x1*y2-x2*y1;
}
double dotmultiply(point p1,point p2){
	return p1.x*p2.x+p1.y*p2.y;
}
point rotate(point o,point p,double alpha){
	point tmp;
	p.x-=o.x;p.y-=o.y;
	tmp.x=p.x*cos(alpha)-p.y*sin(alpha)+o.x;
	tmp.y=p.y*cos(alpha)+p.x*sin(alpha)+o.y;
	return tmp;
}
int on_segment(point p1,line l){
	if (min(l.x.x,l.y.x)-eps<=p1.x&&max(l.x.x,l.y.x)+eps>=p1.x&&
	min(l.x.y,l.y.y)-eps<=p1.y&&max(l.x.y,l.y.y)+eps>=p1.y)return 1;
	else return 0;
}
int online(point p,line l){
	return dblcmp((p-l.x)*(l.y-l.x))==0&&dblcmp((p.x-l.x.x)*(p.x-l.y.x))<1&&dblcmp((p.y-l.x.y)*(p.y-l.y.y))<1;
}
double angle(point o,point p1,point p2){
	double fi,cosfi,norm;
	double sx=p1.x-o.x,sy=p1.y-o.y,ex=p2.x-o.x,ey=p2.y-o.y;
	cosfi=sx*ex+sy*ey;
	norm=(sx*sx+ey*ey)*(ex*ex+ey*ey);
	cosfi/=sqrt(norm);
	if (cosfi>=1.0)return 0;
	if (cosfi<=-1.0)return -pi;
	fi=acos(cosfi);
	if (cha(sx,sy,ex,ey)>0)return fi;
		else return -fi;
}
int direction(point p1,point p2,point p3){
	return dblcmp((p3-p1)*(p2-p1));
}
int cross(line a,line b){
	point &p1=a.x,&p2=a.y,&p3=b.x,&p4=b.y;
	int d1,d2,d3,d4;
	d1=direction(p3,p4,p1);
	d2=direction(p3,p4,p2);
	d3=direction(p1,p2,p3);
	d4=direction(p1,p2,p4);
	if (d1*d2==-1&&d3*d4==-1){
		//printf("%d %d %d %d\n",d1,d2,d3,d4);
		return 1;
	}
	else if (d1==0&&on_segment(p1,b))return 1;
	else if (d2==0&&on_segment(p2,b))return 1;
	else if (d3==0&&on_segment(p3,a))return 1;
	else if (d4==0&&on_segment(p4,a))return 1;
	else return 0;
}
line a[N];
int n,i,j;
int cmp(line l1,line l2){
	return min(l1.x.x,l1.y.x)<min(l2.x.x,l2.y.x);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	int x1,x2,y1,y2;
	scanf("%d",&n);//if (n>10)n=10;
	for (i=1;i<=n;++i){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		a[i].x.x=x1;a[i].x.y=y1;a[i].y.x=x2;a[i].y.y=y2;a[i].rank=i;
	}
	if (n<=400){
	for (i=1;i<n;++i)
		for (j=i+1;j<=n;++j)
		if (cross(a[i],a[j])){
			printf("YES\n");
			printf("%d %d\n",i,j);
			return 0;
		}
	}
	sort(a+1,a+n+1,cmp);
	srand(time(0));
	for (int i1=1;i1<500;++i1){
		for (i=1;i<n;++i)
			if (cross(a[i],a[i+1])){
				printf("YES\n");
				printf("%d %d\n",a[i].rank,a[i+1].rank);
				return 0;
			}
		for (i=1;i<=int(n/3);++i){
			int x=((rand()<<16)+rand())%n+1;
			int y=rand()%10+1;
			if (x+y>n)continue;
			line tmp;y+=x;
			tmp=a[x];a[x]=a[y];a[y]=tmp;
		}
		if (clock()-t1>800)break;
	}
	printf("NO\n");
	system("pause");for (;;);
	return 0;
}


