#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<queue>
#define N 100005
struct Edge{
	#define Mx 300005
	int link[Mx],next[Mx],son[Mx],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
};
Edge e;
int degree[N],visit[N],ans;
void del(int x){
	visit[x]=1;
	for (int p=e.son[x];p;p=e.next[p])--degree[e.link[p]];
}
struct node{
	int x;
	node(int _x):x(_x){}
	friend bool operator <(node x,node y){
		return degree[x.x]>=degree[y.x];
	}
};
std::priority_queue<node> Q;
int main()
{
	freopen("1.in","r",stdin);
	freopen("3.out","w",stdout);
	int n1,n2,m,x,y;e.clear();
	scanf("%d%d%d",&n1,&n2,&m);
	for (int i=1;i<=m;++i)
		scanf("%d%d",&x,&y),y+=n1,e.addedge(x,y),e.addedge(y,x),
		++degree[x],++degree[y];
	for (int i=1;i<=n1;++i) Q.push(node(i));
	while (1){
		int d=1<<30,x=-1,y=-1;
		if (Q.empty())break;
		x=Q.top().x;Q.pop();
		d=1<<30;
		for (int p=e.son[x];p;p=e.next[p])
			if (!visit[e.link[p]]&&degree[e.link[p]]<d)
				d=degree[e.link[p]],y=e.link[p];
		del(x);
		if (y>=0)del(y),++ans;
		//printf("match %d %d\n",x,y);
	}
	printf("%d\n",ans);
	//system("pause");
	return 0;
}


