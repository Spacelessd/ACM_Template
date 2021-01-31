#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<algorithm>
#define N 100005
int n;double a[N],b[N],rate[N],f[N];
inline double max(double x,double y){return x>y?x:y;}
inline double cha(double x1,double y1,double x2,double y2){return x1*y2-x2*y1;}
struct node{double x,y;}c[N],A[N],B[N];int top;
struct Query{double x;int id;}Q[N*2],*cur;
bool cmp(const Query &x,const Query &y){return x.x>y.x;}
void merge(int l,int mid,int r){
	int top1=l,top2=mid;
	for (int i=l;i<=r;++i)
		if (top2>r||top1<mid&&A[top1].x<A[top2].x)B[i]=A[top1++];else B[i]=A[top2++];
	for (int i=l;i<=r;++i)A[i]=B[i];
}
void calc(int l,int r,Query *Q){
	if (l==r){
		if (f[l-1]>f[l])f[l]=f[l-1];
		A[l].x=f[l]/(rate[l]*a[l]+b[l])*rate[l];
		A[l].y=f[l]/(rate[l]*a[l]+b[l]);
		return;
	}
	int mid=(l+r)>>1;Query *tmp=cur;
	for (int i=0;i<=r-l;++i)if (Q[i].id<=mid)*cur++=Q[i];
	calc(l,mid,tmp);cur=tmp;top=0;
	for (int i=l;i<=mid;++i){
		if (top>=1&&fabs(A[i].x-c[top].x)<1e-6){
			if (A[i].y>c[top].y)c[top]=A[i];
			continue;
		}
		while (top>1&&cha(A[i].x-c[top].x,A[i].y-c[top].y,c[top].x-c[top-1].x,c[top].y-c[top-1].y)<0)--top;
		c[++top]=A[i];
	}
	int now=1;
	for (int i=0;i<=r-l;++i)if (Q[i].id>mid){
		double f1,f2,f3=Q[i].x;
		while (1){
			if (now==1)f1=1e30;else f1=(c[now].y-c[now-1].y)/(c[now].x-c[now-1].x);
			if (now==top)f2=-1e30;else f2=(c[now+1].y-c[now].y)/(c[now+1].x-c[now].x);
			if (f1>=f3&&f3>=f2)break;
			++now;
		}
		int i1=Q[i].id;f[i1]=max(f[i1],a[i1]*c[now].x+b[i1]*c[now].y);
	}
	for (int i=0;i<=r-l;++i)if (Q[i].id>mid)*cur++=Q[i];
	calc(mid+1,r,tmp);cur=tmp;
	merge(l,mid+1,r);
}
inline void read(double &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();!(ch>='0' && ch<='9');ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0' && ch<='9';x=x*10+ch-'0',ch=getchar());
	if (ch=='.'){
		double tmp=1;
		for (ch=getchar();ch>='0' && ch<='9';tmp/=10.0,x+=tmp*(ch-'0'),ch=getchar());
	}
	if (bo)x=-x;
}
int main()
{
	//int t1=clock();
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d%lf",&n,&f[1]);
	for (int i=1;i<=n;++i)read(a[i]),read(b[i]),read(rate[i]);
	//scanf("%lf%lf%lf",&a[i],&b[i],&rate[i]);
	//printf("time=%d\n",clock()-t1);
	for (int i=1;i<=n;++i)Q[i].x=-a[i]/b[i],Q[i].id=i;
	std::sort(Q+1,Q+1+n,cmp);cur=Q+n+1;
	calc(1,n,Q+1);
	printf("%.3lf\n",f[n]);
	//printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


