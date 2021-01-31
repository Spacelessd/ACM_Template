#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<math.h>
#include<time.h>
#include<map>
using namespace std;
#define maxn 40010
#define maxX 310
class hash{
      public:
      int *key,*v,*next,*e,len,pp,size;
      void build(int ll=9,int p=11)  //ll¸öÊý  hashsize=p
      {
           pp=p;len=0;size=ll;ll++;
           v=new int[p];memset(v,0,4*p);
           key=new int[ll];memset(key,0,4*ll);
           next=new int[ll];memset(next,0,4*ll);
           e=new int[ll];memset(e,0,4*ll);
      }
      hash(int ll=0,int p=11){
			if (ll==0)return;
			build(ll,p);
	  }
      int gethash(int x){return x%pp;} 
      void insert(int x,int y=0){
           int x1=gethash(x);
           e[++len]=x;key[len]=y;
           next[len]=v[x1];
           v[x1]=len;
      }
      void del(int x){
           int x1=gethash(x),pre=0;
	       int i=v[x1];
	       while(i){
	       	 if (e[i]==x){
				if (pre==0)v[x1]=next[i];
				  else next[pre]=next[i];
				}
		     pre=i;i=next[i];
	         }
	  }
      int find(int x){
  	       int x1=gethash(x);
	       int i=v[x1];
	       while(i){
	       	 if (e[i]==x)return key[i];
		     i=next[i];
	         }
           return -1;
      }
      void inc(int x,int y=1){
  	       int x1=gethash(x);
	       int i=v[x1];
	       while(i){
	       	 if (e[i]==x){key[i]+=y;return;}
		     i=next[i];
	         }
      }
      int operator [](int x){return find(x);}   
};
hash H(maxn*maxX,maxn*maxX*2);
struct Edge{
	int link[maxn*2],next[maxn*2],son[maxn],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
		}
};
Edge e;
map<int,int> M;
int n,m,i,x,y,Lim,X1=0,ans,Fx,Fy,LCA,Sum;
int w[maxn],X[maxn],F[maxn],deep[maxn],f[maxn],L[maxX*maxX],p[maxn];
inline int getrank(int x,int y){
    return (x-1)*X1+y-1;
}
void dfsX(int x,int pre,int dep){
     f[x]=pre;F[x]=1;deep[x]=dep;
     for (int i=e.son[x];i;i=e.next[i])
         if (e.link[i]!=pre){
            dfsX(e.link[i],x,dep+1);
            if (F[e.link[i]]+1>F[x])F[x]=F[e.link[i]]+1;
         }
     if (F[x]>=Lim){F[x]=0;X[x]=++X1;}
}
void dfs(int from,int x,int pre){
     if (p[w[x]]==0)++ans;
     ++p[w[x]];
     if (X[x]){
        int tmp=getrank(from,x);
        L[tmp]=ans;
        }
     for (int i=e.son[x];i;i=e.next[i])
         if (e.link[i]!=pre){
            dfs(from,e.link[i],x);
         }
     --p[w[x]];
     if (p[w[x]]==0)--ans;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d%d",&n,&m);Lim=(int)(sqrt(n)+1);e.clear();
	for (i=1;i<=n;++i){
        scanf("%d",&w[i]);
        if (M.count(w[i])==0)M[w[i]]=++Sum;
        w[i]=M[w[i]];
        }
	for (i=1;i<n;++i)scanf("%d%d",&x,&y),e.addedge(x,y),e.addedge(y,x);
	dfsX(1,0,0);if (!X[1])X[1]=++X1;
	for (i=1;i<=n;++i)if (X[i]){ans=0;dfs(i,i,0);}
	while (m--){
          scanf("%d%d",&x,&y);ans=0;
          for (Fx=x;!X[Fx];Fx=f[Fx]);
          for (Fy=y;!X[Fy];Fy=f[Fy]);
          if (Fx==Fy){
             Fx=x;Fy=y;
             while (Fx!=Fy){
                   if (deep[Fx]>deep[Fy])Fx=f[Fx];
                      else if (deep[Fx]<deep[Fy])Fy=f[Fy];
                           else Fx=f[Fx],Fy=f[Fy];
                   }
             LCA=Fx;
             Fx=x;
             while (1){
                   if (!p[w[Fx]])++ans;
                   ++p[w[Fx]];
                   if (Fx==LCA)break;
                   }
             Fx=y;
             while (1){
                   if (!p[w[Fx]])++ans;
                   ++p[w[Fx]];
                   if (Fx==LCA)break;
                   }
             Fx=x;
             while (1){
                   --p[w[Fx]];
                   if (Fx==LCA)break;
                   }
             Fx=y;
             while (1){
                   --p[w[Fx]];
                   if (Fx==LCA)break;
                   }
             }
             else {
                  int rank=getrank(Fx,Fy);
                  for (int tmp=x;tmp!=Fx;tmp=f[tmp])
                  }
          printf("%d\n",ans);
          }
	system("pause");
	return 0;
}










