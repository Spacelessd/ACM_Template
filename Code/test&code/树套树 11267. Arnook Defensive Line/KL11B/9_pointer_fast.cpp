#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
#define N 500005
int n,m,now=0,sum[N],last[N],ans[N];
int x[N],idx[N],e[N],ide[N],y[N],idy[N],z[N];
char c[N];
inline void add(int x,int t){
	for (;x<=m;x+=x&-x)
		if (last[x]==t)++sum[x];
			else last[x]=t,sum[x]=1;
}
inline int get(int x,int t){
	int tmp=0;
	for (;x;x-=x&-x)
		if (last[x]==t)tmp+=sum[x];
	return tmp;
}
inline void read(int &x){
	char ch; x=0;
	for (ch=getchar();ch<'0'||ch>'9';ch=getchar());
	for (;ch>='0'&&ch<='9';x=x*10+ch-48,ch=getchar());
}
void work(int l,int r)
{
	if (l==r) return; int mid=(l+r)>>1,i=l,j=mid+1;
	work(l,mid); work(mid+1,r); ++now;
	for (int k=l;k<=r;++k)
		if (i<=mid&&(j>r||y[i]<y[j])) e[k]=y[i],ide[k]=idy[i++];
		else e[k]=y[j],ide[k]=idy[j++];
	for (int i=l;i<=r;++i) y[i]=e[i],idy[i]=ide[i];
	m=0;
	for (int i=l;i<=r;++i){
		if (i==l||y[i]!=y[i-1])++m;
		z[idy[i]]=m;
	}
	{
	++m; int *i=x+l,*j=x+mid+1,*k=e+l,*i1=idx+l,*j1=idx+mid+1,*k1=ide+l,*endi=x+mid+1,*endj=x+r+1,*endk=e+r+1;
	while (k!=endk)
		if (i!=endi&&(j==endj||*i<*j||*i==*j&&c[*i1]=='+')){
			if (c[*i1]=='+') add(m-z[*i1],now); *k++=*i++; *k1++=*i1++;
		}
		else {if (c[*j1]=='?') ans[*j1]+=get(m-z[*j1],now); *k++=*j++; *k1++=*j1++;}
	for (int i=l;i<=r;++i) x[i]=e[i],idx[i]=ide[i];
	}
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("9.out","w",stdout);
	read(n);
	for (int i=1;i<=n;++i){
		char ch=getchar(); while (ch!='+'&&ch!='?') ch=getchar(); c[i]=ch;
		read(x[i]); read(y[i]); idx[i]=idy[i]=i;
	}
	int t1=clock();
	work(1,n);
	for (int i=1;i<=n;++i) if (c[i]=='?') printf("%d\n",ans[i]);
	printf("time=%d\n",clock()-t1);
	//system("pause");
	return 0;
}


