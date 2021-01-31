#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define ll long long
const ll maxp=323537;
#define N 100005
ll x[N],y[N],next[N],pre[N];
ll n,l,w,skip,i,j,R,best,low,high,maxl;
void Q(ll x[],ll y[],ll s,ll t){
	ll p,i=s,j=t,m=x[(i+j)/2],m1=y[(i+j)/2];
	do {
		while (x[i]<m||x[i]==m&&y[i]<m1) ++i;
		while (x[j]>m||x[j]==m&&y[j]>m1) --j;
		if (i<=j){
			p=x[i]; x[i]=x[j]; x[j]=p;
			p=y[i]; y[i]=y[j]; y[j]=p;
			++i; --j;
		}
	}while (i<=j);
	if (i<t) Q(x,y,i,t);
	if (s<j) Q(x,y,s,j);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	/*scanf("%I64d%I64d",&l,&w);
	scanf("%I64d",&n);
	for (i=1;i<=n;++i)scanf("%I64d%I64d",&x[i],&y[i]);*/
	l=w=maxp;
	scanf("%I64d%I64d",&skip,&n);
	R=1;
	for (i=1;i<=skip;++i)R=R*111%maxp;
	for (i=1;i<=n;++i){
		x[i]=R=R*111%maxp;
		y[i]=R=R*111%maxp;
	}
	++n;x[n]=0;y[n]=0;
	++n;x[n]=l;y[n]=0;
	++n;x[n]=0;y[n]=w;
	++n;x[n]=l;y[n]=w;
	Q(x,y,1,n);
	next[n]=n+1;
	for (i=n-1;i;--i)
		if (x[i+1]==x[i])next[i]=next[i+1];
			else next[i]=i+1;
	pre[1]=0;
	for (i=1;i<=n;++i)
		if (x[i-1]==x[i])pre[i]=pre[i-1];
			else pre[i]=i-1;
	best=0;
	for (i=1;i<=n;++i){
		low=0;high=w;maxl=l-x[i];
		for (j=next[i];j<=n;++j){
			if ((x[j]-x[i])*(high-low)>best)best=(x[j]-x[i])*(high-low);
				else if (maxl*(high-low)<=best)break;
			if (y[j]==y[i])break;
			if (y[j]<y[i]&&y[j]>low)low=y[j];
				else if (y[j]>y[i]&&y[j]<high)high=y[j];
		}
	}
	Q(y,x,1,n);
	for (i=2;i<=n;++i)if ((y[i]-y[i-1])*l>best)best=(y[i]-y[i-1])*l;
	//printf("%I64d\n",best);
	printf("%.9lf\n",(double)(best)/double(maxp*maxp));
	system("pause");for (;;);
	return 0;
}


