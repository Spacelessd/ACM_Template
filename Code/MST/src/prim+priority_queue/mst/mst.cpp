#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define N 3000005
#define M 5000005
#define ll long long
struct node{
	int d,id;
	node(){}
	node (int _id,int _d):id(_id),d(_d){}
	bool operator <(const node &y)const{return d>y.d;}
};
priority_queue<node> Q;
struct Edge{
	int link[M*2],next[M*2],cost[M*2],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
}e;
int visit[N];
ll prim(int n){
	ll ans=0;Q.push(node(1,0));
	for (int i=1;i<=n;++i)visit[i]=0;
	for (int i1=1;i1<=n;++i1){
		while (visit[Q.top().id])Q.pop();
		int id=Q.top().id;ans+=Q.top().d;visit[id]=1;Q.pop();
		for (int p=e.son[id];p;p=e.next[p])Q.push(node(e.link[p],e.cost[p]));
	}
	return ans;
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
	int n,m;read(n);read(m);e.clear();
	for (int i=1;i<=m;++i){
		int x,y,z;read(x);read(y);read(z);
		e.addedge(x,y,z);e.addedge(y,x,z);
	}
	ll ans=prim(n);
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


