#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<map>
using namespace std;
#define maxn 300010
map<int,int> M;
int n,m,i,x,y,Fx,Fy,LCA,ans,Sum;
int deep[maxn],w[maxn],f[maxn],p[maxn];
struct Edge{
	int link[maxn*2],next[maxn*2],son[maxn],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
		}
};
Edge e;
void dfs(int x,int pre,int dep){
     f[x]=pre;deep[x]=dep;
     for (int i=e.son[x];i;i=e.next[i])
         if (e.link[i]!=pre){
            dfs(e.link[i],x,dep+1);
         }
}
int main()
{
	freopen("cot2.in","r",stdin);
	freopen("cot2.out","w",stdout);
	scanf("%d%d",&n,&m);
	//for (i=1;i<=n;++i)scanf("%d",&w[i]);
	for (i=1;i<=n;++i){
        scanf("%d",&w[i]);
        if (M.count(w[i])==0)M[w[i]]=++Sum;
        w[i]=M[w[i]];
        }
	for (i=1;i<n;++i)scanf("%d%d",&x,&y),e.addedge(x,y),e.addedge(y,x);
	dfs(1,0,1);ans=0;//return 0;
    while (m--)
    //for (int wei=1;wei<=1000;++wei)
    {
          scanf("%d%d",&x,&y);//printf("%d %d\n",x,y);
          //x=x^ans;
           Fx=x;Fy=y;
             while (Fx!=Fy){
                   if (deep[Fx]>deep[Fy])Fx=f[Fx];
                      else if (deep[Fx]<deep[Fy])Fy=f[Fy];
                           else Fx=f[Fx],Fy=f[Fy];
                   }
             LCA=Fx;ans=0;
             Fx=x;
             while (1){
                   if (!p[w[Fx]])++ans;++p[w[Fx]];
                   if (Fx==LCA)break;Fx=f[Fx];
                   }
             Fx=y;
             while (1){
                   if (!p[w[Fx]])++ans;++p[w[Fx]];
                   if (Fx==LCA)break;Fx=f[Fx];
                   }
             Fx=x;
             while (1){
                   --p[w[Fx]];if (Fx==LCA)break;Fx=f[Fx];
                   }
             Fx=y;
             while (1){
                   --p[w[Fx]];if (Fx==LCA)break;Fx=f[Fx];
                   }
             printf("%d\n",ans);
    }
	//system("pause");
	//for (;;);
	return 0;
}














