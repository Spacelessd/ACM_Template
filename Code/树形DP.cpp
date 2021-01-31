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
	int link[N*2],next[N*2],son[N*2],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
}e;
int visit[N],n;
void dfs(int x){
	visit[x]=1;
	for (int p=e.son[x];p;p=e.next[p]){
		int j=e.link[p];
		if (!visit[j]){
			dfs(j);
		}
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int x,y;scanf("%d",&n);
	for (int i=1;i<n;++i){
		scanf("%d%d",&x,&y);
		e.addedge(x,y);e.addedge(y,x);
	}
	dfs(1);
	system("pause");for (;;);
	return 0;
}


