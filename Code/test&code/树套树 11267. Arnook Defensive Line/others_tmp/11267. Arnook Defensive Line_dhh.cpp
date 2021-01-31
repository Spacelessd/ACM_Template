#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#define CH getchar()
#define N 500005
int n,m,tot=0,yy,f[N],g[N],ans[N];
struct note{int x,y,id;}s[N],a[N],e[N];
char c[N];
bool cmp(const note i,const note j){return i.y<j.y;}
void add(int x,int t)
{
	for (;x<=m;x+=x&(-x)) 
		if (t==g[x]) f[x]++; else g[x]=t,f[x]=1;
}
int get(int x,int t)
{
	int res=0;
	for (;x;x-=x&(-x)) if (t==g[x]) res+=f[x];
	return res;
}
void read(int &x)
{
	char ch; x=0;
	for (ch=CH;ch<'0' || ch>'9';ch=CH);
	for (;ch>='0' && ch<='9';x=x*10+ch-48,ch=CH);
}
void work(int l,int r)
{
	if (l==r) return; int mid=(l+r)/2,now=++tot;
	work(l,mid); work(mid+1,r);
	int i=l,j=mid+1;
	for (int k=l;k<=r;k++)
		if (i<=mid && (j>r || a[i].x<a[j].x || a[i].x==a[j].x && c[a[i].id]=='+')){
			if (c[a[i].id]=='+') add(m-a[i].y,now); e[k]=a[i++];
			}
		else {if (c[a[j].id]=='?') ans[a[j].id]+=get(m-a[j].y,now); e[k]=a[j++];}
	for (int i=l;i<=r;i++) a[i]=e[i];
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("d.out","w",stdout);
	read(n); srand(time(0)); //int t1=clock();
	for (int i=1;i<=n;i++){
		char ch=CH; while (ch!='+' && ch!='?') ch=CH; c[i]=ch;
		read(a[i].x); read(s[i].y); a[i].id=s[i].id=i;
		}
	std::sort(s+1,s+n+1,cmp); m=0;
	for (int i=1;i<=n;i++){
		if (i==1 || s[i].y!=s[i-1].y) m++;
		a[s[i].id].y=m;
		}
	m+=2; work(1,n);
	for (int i=1;i<=n;i++) if (c[i]=='?') printf("%d\n",ans[i]);		
//	printf("t1=%d\n",clock()-t1);
	return 0;
}


