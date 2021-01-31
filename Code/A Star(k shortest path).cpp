#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<queue>
using namespace std;
#define N 1005
struct Edge{
	#define Mx N*N
	int link[Mx],cost[Mx],next[Mx],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	Edge(){clear();}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
}e,e1;
struct Astar{
	int w,d,x;
	Astar(int _w,int _d,int _x){w=_w;d=_d;x=_x;}
	friend bool operator <(const Astar &x,const Astar &y){return x.w>y.w;}
};
int n,m,S,T,K;
int h[N],q[N],inq[N];
void spfa(int S,Edge &e,int d[]){
	int h=0,t=1;
	for (int i=1;i<=n;++i)d[i]=1<<29;
	for (int i=1;i<=n;++i)inq[i]=0;
	d[S]=0;q[1]=S;inq[S]=1;
	while (h!=t){
		h=h<n?h+1:1;int i=q[h];inq[i]=0;
		for (int p=e.son[i];p;p=e.next[p]){
			int j=e.link[p];
			if (d[i]+e.cost[p]<d[j]){
				d[j]=d[i]+e.cost[p];
				if (!inq[j])t=t<n?t+1:1,q[t]=j,inq[j]=1;
			}
		}
	}
}
int cnt[N];
priority_queue<Astar> Q;
int Kshortest(int S,int T,int K,Edge &e){
	Q.push(Astar(h[S],0,S));
	for (int i=1;i<=n;++i)cnt[i]=0;
	while (!Q.empty()){
		int w=Q.top().w,d=Q.top().d,x=Q.top().x;
		Q.pop();++cnt[x];
		if (cnt[x]>K)continue;
		if (cnt[T]==K)return w;
		for (int p=e.son[x];p;p=e.next[p]){
			int v=e.link[p];
			Q.push(Astar(d+e.cost[p]+h[v],d+e.cost[p],v));
		}
	}
	return -1;
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int x,y,z;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i){
		scanf("%d%d%d",&x,&y,&z);
		e.addedge(x,y,z);e1.addedge(y,x,z);
	}
	scanf("%d%d%d",&S,&T,&K);
	if (S==T)++K;
	spfa(T,e1,h);
	printf("%d\n",Kshortest(S,T,K,e));
	system("pause");for (;;);
	return 0;
}


