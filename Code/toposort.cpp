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
	#define Mx 500005
	int link[Mx],next[Mx],son[Mx],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
}e;
int f[N],in[N];
void toposort(int n){
	int h=0,t=0;
	for (int i=1;i<=n;++i)in[i]=0;
	for (int i=1;i<=n;++i)
		for (int p=e.son[i];p;p=e.next[p])++in[e.link[p]];
	for (int i=1;i<=n;++i)if (!in[i])f[++t]=i;
	while (h<t){
		int i=f[++h];
		for (int p=e.son[i];p;p=e.next[p]){
			int j=e.link[p]; --in[j];
			if (!in[j])f[++t]=j;
		}
	}
	for (int i=1;i<=t;++i)printf("%d %d\n",i,f[i]);
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,m,x,y;
	scanf("%d%d",&n,&m);e.clear();
	for (int i=1;i<=m;++i)
		scanf("%d%d",&x,&y),e.addedge(x,y);
	toposort(n);
	system("pause");for (;;);
	return 0;
}


