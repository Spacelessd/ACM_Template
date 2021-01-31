#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<map>
#include<vector>
using namespace std;
#define maxn 40010
#define maxX 210
#define uint unsigned int
uint dhh=0,dhh1=0,dhh2;
struct hash{
      uint *key,*num,*v,*next,*e,len,pp,size;
      void build(uint ll=9,uint p=11)  //ll¸öÊý  hashsize=p
      {
           pp=p;len=0;size=ll;ll++;
           v=new uint[p];memset(v,0,4*p);
           key=new uint[ll];memset(key,0,4*ll);
           num=new uint[ll];memset(num,0,4*ll);
           next=new uint[ll];memset(next,0,4*ll);
           e=new uint[ll];memset(e,0,4*ll);
      }
      hash(uint ll=0,uint p=11){
			if (ll==0)return;
			build(ll,p);
	  }
      uint gethash(uint x,uint y){return ((x<<16)+y>>2+1)%pp;}
      void insert(uint x,uint y,uint z){
           uint x1=gethash(x,y);
           e[++len]=x;key[len]=y;num[len]=z;
           next[len]=v[x1];
           v[x1]=len;
      }
      int find(uint x,uint y){
  	       uint x1=gethash(x,y);
	       uint i=v[x1];++dhh2;
	       while(i){
	       	 if (e[i]==x&&key[i]==y)return num[i];
		     i=next[i];++dhh1;
	         }
           return -1;
      }
      void inc(uint x,uint y){
  	       uint x1=gethash(x,y);
	       uint i=v[x1];
	       while(i){
	       	 if (e[i]==x&&key[i]==y){++num[i];return;}
		     i=next[i];
	         }
      }
      void dec(uint x,uint y){
  	       uint x1=gethash(x,y);
	       uint i=v[x1];
	       while(i){
	       	 if (e[i]==x&&key[i]==y){--num[i];return;}
		     i=next[i];
	         }
      }
};
hash H(maxn*maxX*2,maxn*maxX*2);
struct Edge{
	uint link[maxn*2],next[maxn*2],son[maxn],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(uint x,uint y){
		link[++l]=y;next[l]=son[x];son[x]=l;
		}
};
Edge e;
map<uint,uint> M;
vector<uint> son[maxn];
uint n,m,i,x,y,Lim,X1=0,ans,Fx,Fy,LCA,Sum;
uint w[maxn],X[maxn],F1[maxn],deep[maxn],f[maxn],L[maxX*maxX],p[maxn];
uint F[maxn][21];
void BuildLCA(uint x,uint pre){
     F[x][0]=pre;
     for (i=1;i<=20;i++) F[x][i]=F[F[x][i-1]][i-1];
     for (uint i=e.son[x];i;i=e.next[i])
         if (e.link[i]!=pre) BuildLCA(e.link[i],x);
}
uint GetLCA(uint x,uint y){
    uint i;
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
inline uint getrank(uint x,uint y){
    return (x-1)*X1+y-1;
}
void dfsX(uint x,uint pre,uint dep){
     f[x]=pre;F1[x]=1;deep[x]=dep;
     for (uint i=e.son[x];i;i=e.next[i])
         if (e.link[i]!=pre){
            dfsX(e.link[i],x,dep+1);
            if (F1[e.link[i]]+1>F1[x])F1[x]=F1[e.link[i]]+1;
         }
     if (F1[x]>=Lim){F1[x]=0;X[x]=++X1;}
}
void Getson(uint x,uint pre,uint root){
     son[root].push_back(w[x]);
     for (uint i=e.son[x];i;i=e.next[i])
         if (e.link[i]!=pre&&!X[e.link[i]]){
            Getson(e.link[i],x,root);
         }
}
void dfs(uint from,uint x,uint pre){
     if (p[w[x]]==0)++ans;++p[w[x]];
     if (X[x]){
        uint tmp=getrank(X[from],X[x]);
        L[tmp]=ans;
        for (vector<uint>::iterator i=son[x].begin();i!=son[x].end();++i){++dhh;
            if (H.find(tmp,*i)==-1)H.insert(tmp,*i,p[*i]);}
        for (vector<uint>::iterator i=son[from].begin();i!=son[from].end();++i){++dhh;
            if (H.find(tmp,*i)==-1)H.insert(tmp,*i,p[*i]);}
        }
     for (uint i=e.son[x];i;i=e.next[i])
         if (e.link[i]!=pre){
            dfs(from,e.link[i],x);
         }
     --p[w[x]];if (p[w[x]]==0)--ans;
}
uint t1;
int main()
{
	freopen("cot2.in","r",stdin);
	//freopen("cot2.out","w",stdout);
	t1=clock();
    scanf("%d%d",&n,&m);//Lim=n*2;
    Lim=(uint)(sqrt(n)+1);
    e.clear();
	for (i=1;i<=n;++i){
        scanf("%d",&w[i]);
        if (M.count(w[i])==0)M[w[i]]=++Sum;
        w[i]=M[w[i]];
        }
	for (i=1;i<n;++i)scanf("%d%d",&x,&y),e.addedge(x,y),e.addedge(y,x);
	
	dfsX(1,0,1);if (!X[1])X[1]=++X1; BuildLCA(1,0);
	for (i=1;i<=n;++i)if (X[i])Getson(i,f[i],i);
    for (i=1;i<=n;++i)if (X[i]){
        ans=0;dfs(i,i,0);
        }
	while (m--){
          scanf("%d%d",&x,&y);x=x^ans;
          for (Fx=x;!X[Fx];Fx=f[Fx]);
          for (Fy=y;!X[Fy];Fy=f[Fy]);
          uint tmp=GetLCA(Fx,Fy);
          if (deep[tmp]<deep[Fx]&&deep[tmp]<deep[Fy]){
             uint rank=getrank(X[Fx],X[Fy]);ans=L[rank];
             for (uint tmp=x;tmp!=Fx;tmp=f[tmp]){
                 if (H.find(rank,w[tmp])==0)++ans;
                 H.inc(rank,w[tmp]);
                 }
             for (uint tmp=y;tmp!=Fy;tmp=f[tmp]){
                 if (H.find(rank,w[tmp])==0)++ans;
                 H.inc(rank,w[tmp]);
                 }
             for (uint tmp=x;tmp!=Fx;tmp=f[tmp])H.dec(rank,w[tmp]);
             for (uint tmp=y;tmp!=Fy;tmp=f[tmp])H.dec(rank,w[tmp]);
             printf("%d\n",ans);continue;
             }
          if (Fx!=Fy){
             if (deep[Fx]<deep[Fy]){
                 uint tmp=Fx;Fx=Fy;Fy=tmp;
                 tmp=x;x=y;y=tmp;
                 }
             uint rank=getrank(X[Fx],X[Fy]);ans=L[rank];
             for (uint tmp=x;tmp!=Fx;tmp=f[tmp]){
                 if (H.find(rank,w[tmp])==0)++ans;
                 H.inc(rank,w[tmp]);
                 }
             uint zzy=GetLCA(Fx,y);
             for (uint tmp=y;tmp!=zzy;tmp=f[tmp]){
                 if (H.find(rank,w[tmp])==0)++ans;
                 H.inc(rank,w[tmp]);
                 }
             for (uint tmp=F[zzy][0];deep[tmp]>=deep[Fy];tmp=f[tmp]){
                 H.dec(rank,w[tmp]);
                 if (H.find(rank,w[tmp])==0)--ans;
                 }
             for (uint tmp=x;tmp!=Fx;tmp=f[tmp])H.dec(rank,w[tmp]);
             for (uint tmp=y;tmp!=zzy;tmp=f[tmp])H.dec(rank,w[tmp]);
             for (uint tmp=F[zzy][0];deep[tmp]>=deep[Fy];tmp=f[tmp])H.inc(rank,w[tmp]);
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










