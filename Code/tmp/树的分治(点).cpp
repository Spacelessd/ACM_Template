#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define maxn 100010
struct Edge{
	int link[maxn*2],next[maxn*2],cost[maxn*2],son[maxn],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
};
Edge e;
int n,ans,root,Limit;
int a[maxn],p[maxn],pp[maxn],size[maxn],key[maxn],key1,stack[maxn],stack1;
void Q(int a[],int s,int t){
	int p,i=s,j=t,m=a[(i+j)>>1];
	do {
		while (a[i]<m) ++i;
		while (a[j]>m) --j;
		if (i<=j){
			p=a[i]; a[i]=a[j]; a[j]=p;
			++i; --j;
		}
	}while (i<=j);
	if (i<t) Q(a,i,t);
	if (s<j) Q(a,s,j);
}
void dfsroot(int x){
	stack[++stack1]=x;
	int bo=1;p[x]=1;size[x]=1;
	for (int i=e.son[x];i;i=e.next[i])
		if (!p[e.link[i]]&&!pp[e.link[i]]){
		dfsroot(e.link[i]);
		size[x]+=size[e.link[i]];
		if (size[e.link[i]]>(Limit>>1))bo=0;
	}
	if (Limit-size[x]>(Limit>>1))bo=0;
	if (bo)root=x;
}
void dfssize(int x){
	p[x]=1;size[x]=1;
	for (int i=e.son[x];i;i=e.next[i])
		if (!p[e.link[i]]&&!pp[e.link[i]]){
		dfssize(e.link[i]);
		size[x]+=size[e.link[i]];
	}
}
void dfskey(int x,int dep){
	key[++key1]=a[x]-dep; p[x]=1;
	for (int i=e.son[x];i;i=e.next[i]){
		if (!p[e.link[i]]&&!pp[e.link[i]])dfskey(e.link[i],dep+e.cost[i]);
	}
}
int calc(int key[],int len){
	Q(key,1,len);
	int tmp=0,j=len;key[0]=-(1<<30);
	for (int i=1;i<=len;++i){
		while (key[i]+key[j]>0)--j;
		tmp+=len-j;if (j<i)--tmp;
	}
	return tmp;
}
void clear(){for (int i=1;i<=stack1;++i)p[stack[i]]=0;}
void F(int x,int S){
	Limit=S;
	stack1=0;dfsroot(x);clear();
	dfssize(root);clear();
	key1=0;dfskey(root,0);clear();
	ans+=calc(key,key1);
	pp[root]=1;
	for (int i=e.son[root];i;i=e.next[i])
		if (!pp[e.link[i]]){
			key1=0;dfskey(e.link[i],e.cost[i]);
			ans-=calc(key,key1);
		}
	clear();
	for (int i=e.son[root];i;i=e.next[i])
		if (!pp[e.link[i]])F(e.link[i],size[e.link[i]]);
	//pp[root]=0;
}
int main()
{
	//freopen("tree.in","r",stdin);
	//freopen("tree.out","w",stdout);
	int x,y,z;
	scanf("%d",&n);e.clear();
	for (int i=1;i<=n;++i)scanf("%d",&a[i]);
	for (int i=1;i<n;++i){
		scanf("%d%d%d",&x,&y,&z);
		e.addedge(x,y,z);e.addedge(y,x,z);
	}
	F(1,n);ans/=2;
	printf("%d\n",ans);
	system("pause");for (;;);
	return 0;
}


