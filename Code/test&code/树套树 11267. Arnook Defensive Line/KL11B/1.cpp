#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#define CH getchar()
#define N 500005
#define M 10000000
int n,m,tot=0,xx,x[N],y[N];
int L[M],R[M],size[M],key[M],ran[M];
char c[N];
struct note{int x,id;}a[N];
struct Treap{
	int root;
	void updata(int x){size[x]=size[L[x]]+size[R[x]]+1;}
	void zig(int x,int y){L[y]=R[x]; R[x]=y; updata(y); updata(x);}
	void zag(int x,int y){R[y]=L[x]; L[x]=y; updata(y); updata(x);}
	void ins(int x,int &y){
		if (!y) {y=x,L[x]=R[x]=0,size[x]=1; return;}	size[y]++;
		if (key[x]<key[y]){ins(x,L[y]); if (ran[x]<ran[y]) zig(x,y),y=x;}
		else {ins(x,R[y]); if (ran[x]<ran[y]) zag(x,y),y=x;}
		}
	void modify(int v){int x=++tot; ran[x]=rand(); key[x]=v; ins(x,root);}
	int query(int v){
		int ans=0;
		for (int x=root;x;)
			if (key[x]>=v) ans+=size[R[x]]+1,x=L[x];
			else x=R[x];			
		return ans;
		}
}T[N];
void add(int x,int y){for (;x<=m;x+=x&(-x)) T[x].modify(y);}
int get(int x,int y){int res=0; for (;x;x-=x&(-x)) res+=T[x].query(y); return res;}
void read(int &x)
{
	char ch; x=0;
	for (ch=CH;ch<'0' || ch>'9';ch=CH);
	for (;ch>='0' && ch<='9';x=x*10+ch-48,ch=CH);
}
bool cmp(const note i,const note j){return i.x<j.x;}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	read(n); srand(time(0)); int t1=clock();
	for (int i=1;i<=n;i++){
		char ch=CH; while (ch!='+' && ch!='?') ch=CH; c[i]=ch;
		read(xx),read(y[i]); a[i].x=xx,a[i].id=i;
	}
	std::sort(a+1,a+n+1,cmp); m=1;
	for (int i=1;i<=n;i++){
		if (i==1 || a[i].x!=a[i-1].x) m++,T[m].root=0;
		x[a[i].id]=m;
	}
	for (int i=1;i<=n;i++)
		if (c[i]=='+') add(x[i],y[i]);
		else printf("%d\n",get(x[i],y[i]));
	printf("time=%d\n",clock()-t1);
	return 0;
}


