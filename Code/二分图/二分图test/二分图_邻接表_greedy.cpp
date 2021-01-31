#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct Edge{
	#define Mx 400005
	int link[Mx],next[Mx],son[Mx],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
};
Edge g;
#define N 100005
int visit[N],link[N],greedy[N],n,ans,Time;
bool find(int v){
	for (int p=g.son[v],i;p;p=g.next[p]){
		i=g.link[p];
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
	freopen("3.out","w",stdout);
	int x,y,n1,n2,m;
	scanf("%d%d%d",&n1,&n2,&m);
	n=n1>n2?n1:n2;
	for (int i=1;i<=m;++i)
		scanf("%d%d",&x,&y),g.addedge(x,y);
	memset(link,0,sizeof(link));ans=0;
	for (int i=1;i<=n1;++i){
		for (int j=g.son[i];j;j=g.next[j])
			if (!link[g.link[j]]){greedy[i]=1;link[g.link[j]]=i;++ans;break;}
	}
	//printf("greedy %d\n",ans);
	//for (int i=1;i<=n2;++i)printf("link %d=%d\n",i,link[i]);
	memset(visit,0,sizeof(visit));
	for (int i=1;i<=n;++i)
		if (!greedy[i]){
			Time=i;if (find(i))++ans;
		}
	printf("%d\n",ans);
	//for (int i=1;i<=n2;++i)printf("link %d=%d\n",i,link[i]);
	//system("pause");for (;;);
	return 0;
}


