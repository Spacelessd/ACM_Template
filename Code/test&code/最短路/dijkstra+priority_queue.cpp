#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<queue>
using namespace std;
#define N 1000005
struct Edge{
	#define Mx 20000005
	int link[Mx],cost[Mx],next[Mx],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	Edge(){clear();}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
}e;
int n,m,S,T;
struct Node{
	int d,x;
	Node(int _d,int _x){d=_d;x=_x;}
	friend bool operator <(const Node &x,const Node &y){return x.d>y.d;}
};
priority_queue<Node> Q;
int cnt[N];
int dijkstra(int S,int T,Edge &e){
	Q.push(Node(0,S));
	while (!Q.empty()){
		int d=Q.top().d,x=Q.top().x;cnt[x]=1;
		if (x==T)return d;
		for (int p=e.son[x];p;p=e.next[p]){
			int v=e.link[p];
			Q.push(Node(d+e.cost[p],v));
		}
		while (cnt[Q.top().x]&&!Q.empty())Q.pop();
	}
	return -1;
}
int main(){
	freopen("1.in","r",stdin);
	freopen("2.out","w",stdout);
	int x,y,z;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i)
		scanf("%d%d%d",&x,&y,&z),e.addedge(x,y,z);
	scanf("%d%d",&S,&T);
	printf("%d\n",dijkstra(S,T,e));
	//system("pause");for (;;);
	return 0;
}


