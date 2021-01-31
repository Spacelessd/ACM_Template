#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
int dfn[N],low[N],stack[N],num[N],instack[N],D,now,top;
struct Edge{
	#define Mx 500005
	int link[Mx],next[Mx],son[Mx],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
}e;
inline int min(int x,int y){return x<y?x:y;}
void tarjan(int x){
	dfn[x]=low[x]=++D;stack[++top]=x;instack[x]=1;
	for (int p=e.son[x];p;p=e.next[p]){
		int j=e.link[p];
		if (!dfn[j]) tarjan(j),low[x]=min(low[x],low[j]);
		else if (instack[j]) low[x]=min(low[x],dfn[j]);
	}
	if (low[x]==dfn[x]){
		int k;++now;
		do k=stack[top--],instack[k]=0,num[k]=now; while (k!=x);
	}
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,m,x,y;
	scanf("%d%d",&n,&m);e.clear();
	for (int i=1;i<=m;++i)
		scanf("%d%d",&x,&y),e.addedge(x,y);
	memset(dfn,0,sizeof(dfn));D=0;top=0;now=0;
	for (int i=1;i<=n;++i)
		if (!dfn[i])tarjan(i);
	for (int i=1;i<=n;++i)printf("%d %d\n",i,num[i]);
	system("pause");for (;;);
	return 0;
}


