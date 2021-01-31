#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 100005
struct Edge{
	int link[N],next[N],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
}e;
int path[N],top,n,m;
void dfs(int x){
	for (int i=e.son[x];i;i=e.son[x])
		e.son[x]=e.next[i],dfs(e.link[i]);
	path[++top]=x;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	while (scanf("%d%d",&n,&m)!=EOF){
		int x,y;e.clear();
		for (int i=1;i<=m;++i)scanf("%d%d",&x,&y),e.addedge(x,y),e.addedge(y,x);
		top=0;dfs(1);
		while (top)printf("%d\n",path[top--]);
	}
	system("pause");for (;;);
	return 0;
}


