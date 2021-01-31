#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Edge{
	#define Mx 400005
	int link[Mx],next[Mx],son[Mx],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
};
Edge g;
const int maxn=100005;
int n,n1,n2,m,ans,time;
int y[maxn],link[maxn];
bool find(int v)
{
	for (int p=g.son[v],i;p;p=g.next[p]){
		i=g.link[p];
		if (y[i]!=time){
			y[i]=time;
			if (!link[i]||find(link[i])){
				link[i]=v;return 1;
			}
		}
	}
	return 0;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int x,y;
	scanf("%d%d%d",&n1,&n2,&m);
	if (n1>n)n=n1;
	if (n2>n)n=n2;
	for (int i=1;i<=m;++i)
		scanf("%d%d",&x,&y),g.addedge(x,y);
	memset(link,0,sizeof(link));
	for (int i=1;i<=n;++i){
		time=i;
		if (find(i))++ans;
	}
	printf("%d\n",ans);
	//system("pause");
	return 0;
}




