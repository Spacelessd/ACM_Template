#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
int stack[N],num[N],p[N],now,top;
struct Edge{
	#define Mx 500005
	int link[Mx],next[Mx],son[Mx],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
}e1,e2;
void dfs1(int x){
	p[x]=1;
	for (int i=e1.son[x];i;i=e1.next[i])
		if (!p[e1.link[i]])dfs1(e1.link[i]);
	stack[++top]=x;
}
void dfs2(int x){
	p[x]=1;num[x]=now;
	for (int i=e2.son[x];i;i=e2.next[i])
		if (!p[e2.link[i]])dfs2(e2.link[i]);
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,m,x,y; scanf("%d%d",&n,&m);e1.clear();e2.clear();
	for (int i=1;i<=m;++i)
		scanf("%d%d",&x,&y),e1.addedge(x,y),e2.addedge(y,x);
	memset(p,0,sizeof(p));top=0;
	for (int i=1;i<=n;++i)
		if (!p[i])dfs1(i);
	memset(p,0,sizeof(p));now=0;
	for (int i=top;i;--i)
		if (!p[stack[i]])++now,dfs2(stack[i]);
	for (int i=1;i<=n;++i)printf("%d %d\n",i,num[i]);
	system("pause");for (;;);
	return 0;
}


