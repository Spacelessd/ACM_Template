#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define rep(i,n) for(int i=1;i<=n;++i)
#define maxn 100010
#define oo (1<<30)
inline int max(int a,int b){return a>b?a:b;}
int Lim,n,x,y,z,q,test;
int w[maxn],dep[maxn],fa[maxn],own[maxn],Max[maxn],Sum[maxn];
int edgex[maxn],edgey[maxn];
char str[100];
struct Edge{
	int link[maxn*2],next[maxn*2],cost[maxn*2],son[maxn],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
		}
}e,et;
void Build(int x,int y,int deep){
    dep[x]=deep;fa[x]=y;
    if (own[x]==-1)own[x]=x,Sum[x]=1;
    int tmp=own[x];
    for (int i=e.son[x];i;i=e.next[i]){
        int j=e.link[i];if (j!=y){
            if (Sum[tmp]<Lim){
               et.addedge(x,j,0);
               own[j]=tmp;Sum[tmp]++;
            }
            w[j]=e.cost[i];Build(j,x,deep+1);
        }
    }
}
void Dfs(int x,int m){
    Max[x]=m=max(m,w[x]);
    for (int i=et.son[x];i;i=et.next[i])Dfs(et.link[i],m);
}
void Change(int x,int key){
    w[x]=key;
    if (x==own[x])Dfs(x,-oo);
    else Dfs(x,Max[fa[x]]);
}
int Qmax(int x,int y){
    int m=-oo,tmp;
    while (x!=y){
        if (dep[x]<dep[y]){tmp=x;x=y;y=tmp;}
        if (own[x]==own[y]){m=max(m,w[x]);x=fa[x];}
        else {
            if (dep[own[x]]<dep[own[y]]){tmp=x;x=y;y=tmp;}
            m=max(m,Max[x]);x=fa[own[x]];
        }
    }
    return m;
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	scanf("%d",&test);
	while (test--){
	scanf("%d",&n);Lim=(int)sqrt(n)+1;
	e.clear();et.clear();
	rep(i,n-1)scanf("%d%d%d",&x,&y,&z),e.addedge(x,y,z),e.addedge(y,x,z),edgex[i]=x,edgey[i]=y;
	memset(own,-1,sizeof(int)*(n+5));
	Build(1,-1,0);
	rep(i,n)if (own[i]==i)Dfs(i,-oo);
	int tmp;
	while (1){
        gets(str);
        scanf("%s",str);
        if (str[0]=='D')break;
        scanf("%d%d",&x,&y);
        if (str[1]=='H'){
                         if (dep[edgex[x]]>dep[edgey[x]])tmp=edgex[x];
                         else tmp=edgey[x];
                         Change(tmp,y);
                         }
        else if (str[1]=='U')printf("%d\n",Qmax(x,y));
    }
    }
	//system("pause");
	//for (;;);
	return 0;
}


