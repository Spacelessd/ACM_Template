#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
const int maxn=20010;
const int maxm=500010;
#define oo 50000000
int son[maxn],q[maxn],d[maxn],inq[maxn],visit[maxn];
int link[maxm],next[maxm],cap[maxm],opp[maxm],cost[maxm];
int n,m,i,S,T,ll,ans,maxflow,mincost;
int x,y,z,tmp;
void addedge(int x,int y,int z,int c)
{
     link[++ll]=y;next[ll]=son[x];son[x]=ll;cap[ll]=z;cost[ll]=c;opp[ll]=ll+1;
     link[++ll]=x;next[ll]=son[y];son[y]=ll;cap[ll]=0;cost[ll]=-c;opp[ll]=ll-1;
}
int spfa(int s)
{
     int h=1,t=1,i,j,p;
     memset(d,6,sizeof(int)*(n+5));
     memset(inq,0,sizeof(int)*(n+5));
     d[S]=0;q[1]=S;inq[S]=1;
     while (h<=t){
           i=q[h++];inq[i]=0;
           for (p=son[i];p!=-1;p=next[p]){
               j=link[p];
               if (cap[p]&&d[i]+cost[p]<d[j]){
                   d[j]=d[i]+cost[p];
                   if (!inq[j])q[++t]=j,inq[j]=1;
                   }
               }
           }
     return d[T]>oo?0:1;
}

int dfs(int x,int flow){
    if (x==T)return flow;
    visit[x]=1;
    int l=flow,p,t;
    for (p=son[x];p!=-1&&l;p=next[p])
        if (!visit[link[p]]&&cap[p]&&d[link[p]]==d[x]+cost[p]){
            t=dfs(link[p],l>cap[p]?cap[p]:l);
            mincost+=t*cost[p],cap[p]-=t,cap[opp[p]]+=t,l-=t;
            }
    return flow-l;
}
int main()
{
    //srand(time(0));
	//freopen("ditch.in","r",stdin);
	//freopen("ditch.out","w",stdout);
	ll=0;scanf("%d%d",&m,&n);
	memset(son,-1,sizeof(int)*(n+5));
	S=1;T=n;maxflow=mincost=0;
	for (i=1;i<=m;i++)
	{
        scanf("%d%d%d",&x,&y,&z);
        addedge(x,y,z,rand()&32767);
    }
    while (spfa(S)) {
          while (1){
              memset(visit,0,sizeof(int)*(n+5));
              tmp=dfs(S,oo);
              if (!tmp)break;
              maxflow+=tmp;
              }
          }
    printf("%d\n",maxflow);
    //printf("%d\n",mincost);
	//system("pause");
	//for(;;);
	return 0;
}







