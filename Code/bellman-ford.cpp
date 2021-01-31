#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 100005
#define M 500005
struct Edge{
	int link[M],cost[M],next[M],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	Edge(){clear();}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
}e;
int d[N],n,m,S,T;
void bellman_ford(int S,Edge &e,int d[]){
	for (int i=1;i<=n;++i)d[i]=1<<29; d[S]=0;
	for (int i1=1;i1<n;++i1){
		bool flag=0;
		for (int i=1;i<=n;++i)
			for (int p=e.son[i];p;p=e.next[p])
				if (d[i]+e.cost[p]<d[e.link[p]]){
					d[e.link[p]]=d[i]+e.cost[p];flag=1;
				}
		if (!flag)break;
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int x,y,z;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i)
		scanf("%d%d%d",&x,&y,&z),e.addedge(x,y,z);
	scanf("%d%d",&S,&T);
	bellman_ford(S,e,d);
	printf("%d\n",d[T]);
	system("pause");for (;;);
	return 0;
}


