#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<algorithm>
#define N 100005
struct point{double x,y;}p[N];
int c[N],top;
double cha(double x1,double y1,double x2,double y2){return x1*y2-x2*y1;}
bool cmp(const point &x,const point &y){return x.x<y.x||x.x==y.x&&x.y<y.y;}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n;double l;scanf("%d%lf",&n,&l);
	for (int i=1;i<=n;++i)scanf("%lf%lf",&p[i].x,&p[i].y);
	std::sort(p+1,p+1+n,cmp);top=0;
	for (int i=1;i<=n;++i){
		while (top>1&&cha(p[i].x-p[c[top]].x,p[i].y-p[c[top]].y,p[c[top]].x-p[c[top-1]].x,p[c[top]].y-p[c[top-1]].y)>0)--top;
		c[++top]=i;
	}
	for (int i=n-1;i;--i){
		while (top>1&&cha(p[i].x-p[c[top]].x,p[i].y-p[c[top]].y,p[c[top]].x-p[c[top-1]].x,p[c[top]].y-p[c[top-1]].y)>0)--top;
		c[++top]=i;
	}
	double ans=0;
	//for (int i=1;i<top;++i)ans+=cha(0,0,p[c[i+1]].x-p[c[i]].x,p[c[i+1]].y-p[c[i]].y);
	//if (ans<0)ans=-ans;
	c[top+1]=c[1];
	//for (int i=1;i<=top;++i)printf("zzwa%d %d\n",p[c[i]].x,p[c[i]].y);
	for (int i=1;i<=top;++i)ans+=sqrt((p[c[i+1]].x-p[c[i]].x)*(p[c[i+1]].x-p[c[i]].x)
		+(p[c[i+1]].y-p[c[i]].y)*(p[c[i+1]].y-p[c[i]].y));
	ans+=3.141592653589*l*2;
	printf("%.0f\n",ans);
	system("pause");for (;;);
	return 0;
}


