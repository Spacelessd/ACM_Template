#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
struct Edge{
	#define Mx 400005
	int link[Mx],next[Mx],son[Mx],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
}e;
int visit[N],link[N],n,ans,Time;
bool find(int v){
	for (int p=e.son[v],i;p;p=e.next[p]){
		i=e.link[p];
		if (visit[i]!=Time){
			visit[i]=Time;
			if (!link[i]||find(link[i])){
				link[i]=v;return 1;
			}
		}
	}
	return 0;
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("2.out","w",stdout);
	int x,y,n1,n2,m;
	scanf("%d%d%d",&n1,&n2,&m);
	n=n1>n2?n1:n2;
	for (int i=1;i<=m;++i)
		scanf("%d%d",&x,&y),e.addedge(x,y);
	memset(link,0,sizeof(link));
	memset(visit,0,sizeof(visit));
	ans=0;
	for (int i=1;i<=n;++i){
		Time=i;if (find(i))++ans;
	}
	printf("%d\n",ans);
	//system("pause");for (;;);
	return 0;
}


