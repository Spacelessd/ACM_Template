#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<math.h>
#include<time.h>
#include<map>
#include<vector>
using namespace std;
#define maxn 40010
#define maxX 310
struct hash{
      int *key,*num,*v,*next,*e,len,pp,size;
      void build(int ll=9,int p=11)  //ll¸öÊý  hashsize=p
      {
           pp=p;len=0;size=ll;ll++;
           v=new int[p];memset(v,0,4*p);
           key=new int[ll];memset(key,0,4*ll);
           num=new int[ll];memset(num,0,4*ll);
           next=new int[ll];memset(next,0,4*ll);
           e=new int[ll];memset(e,0,4*ll);
      }
      hash(int ll=0,int p=11){
			if (ll==0)return;
			build(ll,p);
	  }
      int gethash(int x,int y){return (x^y)%pp;}
      void insert(int x,int y,int z){
           int x1=gethash(x,y);
           e[++len]=x;key[len]=y;num[len]=z;
           next[len]=v[x1];
           v[x1]=len;
      }
      int find(int x,int y){
  	       int x1=gethash(x,y);
	       int i=v[x1];
	       while(i){
	       	 if (e[i]==x&&key[i]==y)return num[i];
		     i=next[i];
	         }
           return -1;
      }
      void inc(int x,int y){
  	       int x1=gethash(x,y);
	       int i=v[x1];
	       while(i){
	       	 if (e[i]==x&&key[i]==y){++num[i];return;}
		     i=next[i];
	         }
      }
      void dec(int x,int y){
  	       int x1=gethash(x,y);
	       int i=v[x1];
	       while(i){
	       	 if (e[i]==x&&key[i]==y){++num[i];return;}
		     i=next[i];
	         }
      }
};
hash H(maxn*maxX*3,maxn*maxX*6);
//map<pair<int,int>,int> H;
struct Edge{
	int link[maxn*2],next[maxn*2],son[maxn],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
		}
};
Edge e;
map<int,int> M;
vector<int> son[maxn];
int n,m,i,x,y,Lim,X1=0,ans,Fx,Fy,LCA,Sum;
int w[maxn],X[maxn],F1[maxn],deep[maxn],f[maxn],L[maxX*maxX],p[maxn];
int F[maxn][21];
void BuildLCA(int x,int pre){
     F[x][0]=pre;
     for (i=1;i<=20;i++) F[x][i]=F[F[x][i-1]][i-1];
     for (int i=e.son[x];i;i=e.next[i])
         if (e.link[i]!=pre) BuildLCA(e.link[i],x);
}
int GetLCA(int x,int y){
    int i;
    if (deep[x]>deep[y])
       for (i=20;i>=0;--i){if (deep[x]-(1<<i)>=deep[y])x=F[x][i];}
           else for (i=20;i>=0;--i){if (deep[y]-(1<<i)>=deep[x])y=F[y][i];}
    for (i=20;i>=0;--i)
        if (F[x][i]!=F[y][i]){
            x=F[x][i];y=F[y][i];
        }
    if (x!=y)x=F[x][0];
    return x;
}
inline int getrank(int x,int y){
    return (x-1)*X1+y-1;
}
void dfsX(int x,int pre,int dep){
     f[x]=pre;F1[x]=1;deep[x]=dep;
     for (int i=e.son[x];i;i=e.next[i])
         if (e.link[i]!=pre){
            dfsX(e.link[i],x,dep+1);
            if (F1[e.link[i]]+1>F1[x])F1[x]=F1[e.link[i]]+1;
         }
     if (F1[x]>=Lim){F1[x]=0;X[x]=++X1;}
}
void Getson(int x,int pre,int root){
     son[root].push_back(w[x]);
     for (int i=e.son[x];i;i=e.next[i])
         if (e.link[i]!=pre&&!X[e.link[i]]){
            Getson(e.link[i],x,root);
         }
}
void dfs(int from,int x,int pre){
     if (p[w[x]]==0)++ans;++p[w[x]];
     if (X[x]){
        int tmp=getrank(X[from],X[x]);
        L[tmp]=ans;
        for (vector<int>::iterator i=son[x].begin();i!=son[x].end();++i)
            if (H.find(tmp,*i)==-1)H.insert(tmp,*i,p[*i]);
        for (vector<int>::iterator i=son[from].begin();i!=son[from].end();++i)
            if (H.find(tmp,*i)==-1)H.insert(tmp,*i,p[*i]);
        }
     for (int i=e.son[x];i;i=e.next[i])
         if (e.link[i]!=pre){
            dfs(from,e.link[i],x);
         }
     --p[w[x]];if (p[w[x]]==0)--ans;
}
int main()
{
	freopen("cot2.in","r",stdin);
	freopen("cot2.out","w",stdout);
	scanf("%d%d",&n,&m);//Lim=n*2;
    Lim=(int)(sqrt(n)+1);
    e.clear();
	for (i=1;i<=n;++i){
        scanf("%d",&w[i]);
        if (M.count(w[i])==0)M[w[i]]=++Sum;
        w[i]=M[w[i]];
        }
	for (i=1;i<n;++i)scanf("%d%d",&x,&y),e.addedge(x,y),e.addedge(y,x);
	dfsX(1,0,1);if (!X[1])X[1]=++X1; BuildLCA(1,0);
	for (i=1;i<=n;++i)if (X[i])Getson(i,f[i],i);
    for (i=1;i<=n;++i)if (X[i]){ans=0;dfs(i,i,0);}
    //for (vector<int>::iterator i=son[1].begin();i!=son[1].end();++i)
        //printf("son=%d\n",*i);
            
	while (m--)
	//for (int wei=1;wei<=10000;++wei)
    {
          scanf("%d%d",&x,&y);x=x^ans;
          //printf("rp%d %d\n",x,y);
          ans=-1;//for (i=0;i<=100;++i)if (p[i]!=0)printf("nie\n");
          for (Fx=x;!X[Fx];Fx=f[Fx]);
          for (Fy=y;!X[Fy];Fy=f[Fy]);
          int tmp=GetLCA(Fx,Fy);
          //printf("nie%d %d\n",Fx,Fy);
          if (deep[tmp]<deep[Fx]&&deep[tmp]<deep[Fy]){
             int rank=getrank(X[Fx],X[Fy]);ans=L[rank];
             for (int tmp=x;tmp!=Fx;tmp=f[tmp]){
                 if (H.find(rank,w[tmp])==0)++ans;
                 H.inc(rank,w[tmp]);
                 }
             for (int tmp=y;tmp!=Fy;tmp=f[tmp]){
                 if (H.find(rank,w[tmp])==0)++ans;
                 H.inc(rank,w[tmp]);
                 }
             for (int tmp=x;tmp!=Fx;tmp=f[tmp])H.dec(rank,w[tmp]);
             for (int tmp=y;tmp!=Fy;tmp=f[tmp])H.dec(rank,w[tmp]);
             printf("%d\n",ans);continue;
             }
          if (Fx!=Fy){
             if (deep[Fx]<deep[Fy]){
                 int tmp=Fx;Fx=Fy;Fy=tmp;
                 tmp=x;x=y;y=tmp;
                 }
             int rank=getrank(X[Fx],X[Fy]);ans=L[rank];
             
             //printf("No1. %d\n",H[make_pair(rank,0)]);
             //printf("%d\n",rank);
             //printf("No2. %d\n",H[make_pair(rank,1)]);
             
             for (int tmp=x;tmp!=Fx;tmp=f[tmp]){
                 if (H.find(rank,w[tmp])==0)++ans;
                 H.inc(rank,w[tmp]);
                 }
             int zzy=GetLCA(Fx,y);
             for (int tmp=y;tmp!=zzy;tmp=f[tmp]){
                 if (H.find(rank,w[tmp])==0)++ans;
                 H.inc(rank,w[tmp]);
                 }
             for (int tmp=F[zzy][0];deep[tmp]>=deep[Fy];tmp=f[tmp]){
                 H.dec(rank,w[tmp]);
                 if (H.find(rank,w[tmp])==0)--ans;
                 }
             for (int tmp=x;tmp!=Fx;tmp=f[tmp])H.dec(rank,w[tmp]);
             for (int tmp=y;tmp!=zzy;tmp=f[tmp])H.dec(rank,w[tmp]);
             for (int tmp=F[zzy][0];deep[tmp]>=deep[Fy];tmp=f[tmp])H.inc(rank,w[tmp]);
             printf("%d\n",ans);continue;
          }
          
          
          
          
          
          if (Fx==Fy){
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
             printf("%d\n",ans);continue;
          }
             
             
             
          
          printf("%d\n",ans);
          }
	//system("pause");
	//for (;;);
	return 0;
}










