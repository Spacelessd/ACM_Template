#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<queue>
using namespace std;
#define N 100005
struct Edge{
	#define Mx 500005
	int link[Mx],cost[Mx],next[Mx],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	Edge(){clear();}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
};
Edge e;
int n,m,S,T;
int d[N],inq[N];
priority_queue<int> q;
void spfa(int S,Edge &e,int d[]){
	for (int i=1;i<=n;++i)d[i]=1<<29;
	for (int i=1;i<=n;++i)inq[i]=0;
	d[S]=0;q.push(S);inq[S]=1;
	while (!q.empty()){
		int i=q.top();q.pop();inq[i]=0;
		for (int p=e.son[i];p;p=e.next[p]){
			int j=e.link[p];
			if (d[i]+e.cost[p]<d[j]){
				d[j]=d[i]+e.cost[p];
				if (!inq[j])q.push(j),inq[j]=1;
			}
		}
	}
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int x,y,z;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i)
		scanf("%d%d%d",&x,&y,&z),e.addedge(x,y,z);
	//scanf("%d%d",&S,&T);
	S=1;T=n;
	spfa(S,e,d);
	printf("%d\n",d[T]);
	//system("pause");
	return 0;
}


