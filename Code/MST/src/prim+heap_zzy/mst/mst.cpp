#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
const int inf=(ll)(1LL<<31)-1;
#define N 3000005
#define M 5000005*2
int tot,l,n,m,heap[N],rankin[N],rankout[N];
int son[N],len[M],next[M],point[M];
bool use[N];
void addedge(int x, int y, int z){
	point[++tot]=y; next[tot]=son[x]; 
	son[x]=tot; len[tot]=z;
}
void swap(int x, int y){
	int tmp;
	tmp=heap[x]; heap[x]=heap[y]; heap[y]=tmp;
	tmp=rankout[x]; rankout[x]=rankout[y]; rankout[y]=tmp;
	rankin[rankout[x]]=x; rankin[rankout[y]]=y;
}
void up(int x){
	while (x && heap[x]<heap[x>>1]) swap(x,x>>1),x=x>>=1;
}
void down(int x){
	while (x*2<=l){
		int y=x;
		if (heap[x+x]<heap[y]) y=x+x;
		if (heap[x+x+1]<heap[y] && x+x+1<=l) y=x+x+1;
		if (x==y) break;
		swap(x,y); x=y;
	}
}
void add(int x, int y){
	heap[++l]=y; rankin[x]=l; rankout[l]=x;
}
inline void read(int &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
	if (bo)x=-x;
}
int main()
{
	freopen("mst.in","r",stdin);
	freopen("mst.out","w",stdout);
	read(n);read(m);
	for (int i=1; i<=m; i++){
		int x,y,z; read(x);read(y);read(z);
		addedge(x,y,z); addedge(y,x,z);
	}
	ll ans=0;
	add(1,0);
	for (int i=2; i<=n; i++) add(i,inf);
	for (int i=1; i<=n; i++)
	{
		int x,y;
		ans+=heap[1]; x=rankout[1]; use[x]=1;
		swap(1,l); l--; down(1);
		
		for (int p=son[x]; p; p=next[p])
		{
			y=point[p];
			if (!use[y])
			{
				if (len[p]<heap[rankin[y]]) heap[rankin[y]]=len[p];
				up(rankin[y]);
			}
		}
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


