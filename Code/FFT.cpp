#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
const double pi=2*asin(1);
#define N 1000005
struct cpx{
	double x,y;
	cpx(double _x=0,double _y=0):x(_x),y(_y){}
};
inline cpx operator +(cpx a,cpx b){
	return cpx(a.x+b.x,a.y+b.y);
}
inline cpx operator -(cpx a,cpx b){
	return cpx(a.x-b.x,a.y-b.y);
}
inline cpx operator *(cpx a,cpx b){
	return cpx(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
}
cpx f[N],aa[N];
char str[N];
int ans[N],n;
void init(cpx a[]){
	scanf("%s",str);
	int j=strlen(str),k=0,l=0,tmp=0;
	int u[4]={1,10,100,1000};
	for (int i=j-1;i>=0;--i){
		tmp+=u[k++]*(str[i]-'0');
		if (k==4)a[l++].x=tmp,k=tmp=0;
	}
	if (k)a[l++].x=tmp;
	if (l>n)n=l;
}
struct DFT{
	cpx a[N];
	void cal(int n,int s,int t){
		if (n==1)return;
		int j=n>>1;
		cal(j,s,t+1);cal(j,s+(1<<t),t+1);
		for (int i=0;i<j;++i){
			int p=s+(i<<(t+1));
			cpx w=f[i<<t]*a[p+(1<<t)];
			aa[i]=a[p]+w;aa[i+j]=a[p]-w;
		}
		for (int i=0;i<n;++i)a[s+(i<<t)]=aa[i];
	}
};
DFT a,b,c;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	n=0;init(a.a);init(b.a);
	int tmp=1;
	while (tmp<n)tmp<<=1;
	n=tmp<<1;
	for (int i=0;i<n;++i)f[i]=cpx(cos(2*pi*i/n),sin(2*pi*i/n));
	a.cal(n,0,0);b.cal(n,0,0);
	for (int i=0;i<n;++i)c.a[i]=a.a[i]*b.a[i];
	for (int i=0;i<n;++i)f[i].y*=-1;
	c.cal(n,0,0);
	long long x=0;
	for (int i=0;i<n;++i){
		c.a[i].x/=n;
		x+=(long long)(c.a[i].x+0.1);
		ans[i]=x%10000;x/=10000;
	}
	while (n&&!ans[n])--n;
	printf("%d",ans[n--]);
	for (int i=n;i>=0;--i)printf("%04d",ans[i]);
	printf("\n");
	system("pause");for (;;);
	return 0;
}


