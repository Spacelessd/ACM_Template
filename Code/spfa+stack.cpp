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
}e;
int d[N],stack[N],instack[N],n,m,S,T;
void spfa(int S,Edge &e,int d[]){
	int top=1;
	for (int i=1;i<=n;++i)d[i]=1<<29;
	for (int i=1;i<=n;++i)instack[i]=0;
	d[S]=0;stack[1]=S;instack[S]=1;
	while (top){
		int x=stack[top--];instack[x]=0;
		for (int p=e.son[x];p;p=e.next[p]){
			int j=e.link[p];
			if (d[x]+e.cost[p]<d[j]){
				d[j]=d[x]+e.cost[p];
				if (!instack[j])stack[++top]=j,instack[j]=1;
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
	scanf("%d%d",&S,&T);
	spfa(S,e,d);
	printf("%d\n",d[T]);
	system("pause");for (;;);
	return 0;
}


