#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
#define N 500005
int n,m,now=0,sum[N],last[N],ans[N];
struct Qnode{int x,y,id;}s[N],a[N],e[N];
char c[N];
bool cmp(const Qnode i,const Qnode j){return i.y<j.y;}
inline void add(register int x,register int t){
	for (;x<=m;x+=x&-x)
		if (last[x]==t)++sum[x];
			else last[x]=t,sum[x]=1;
}
inline int get(register int x,register int t){
	register int tmp=0;
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
		if (i<=mid&&(j>r||a[i].x<a[j].x||a[i].x==a[j].x&&c[a[i].id]=='+')){
			if (c[a[i].id]=='+') add(m-a[i].y,now); e[k]=a[i++];
		}
		else {if (c[a[j].id]=='?') ans[a[j].id]+=get(m-a[j].y,now); e[k]=a[j++];}
	for (int i=l;i<=r;++i) a[i]=e[i];
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	read(n);
	for (int i=1;i<=n;++i){
		char ch=getchar(); while (ch!='+'&&ch!='?') ch=getchar(); c[i]=ch;
		read(a[i].x); read(s[i].y); a[i].id=s[i].id=i;
	}
	std::sort(s+1,s+n+1,cmp); m=0;
	for (int i=1;i<=n;++i){
		if (i==1||s[i].y!=s[i-1].y)++m;
		a[s[i].id].y=m;
	}
	++m;++m; work(1,n);
	for (int i=1;i<=n;++i) if (c[i]=='?') printf("%d\n",ans[i]);		
	//printf("time=%d\n",clock()-t1);
	//system("pause");
	return 0;
}



