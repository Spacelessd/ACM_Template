/*
ID:hqztrue1
LANG:C++
TASK:ditch
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
const int maxn=20010;
const int maxm=500010;
#define oo 50000000
int son[maxn],q[maxn],d[maxn],pre[maxn],inq[maxn];
int link[maxm],st[maxm],next[maxm],cap[maxm],opp[maxm],cost[maxm];
int n,m,i,S,T,ll,ans,maxflow,mincost;
int x,y,z,w;
void addedge(int x,int y,int z,int c)
{
     link[++ll]=y;st[ll]=x;next[ll]=son[x];son[x]=ll;cap[ll]=z;cost[ll]=c;opp[ll]=ll+1;
     link[++ll]=x;st[ll]=y;next[ll]=son[y];son[y]=ll;cap[ll]=0;cost[ll]=-c;opp[ll]=ll-1;
}
int spfa(int s)
{
     int h=0,t=1,i,j,p;
     memset(d,6,sizeof(int)*(n+5));
     memset(inq,0,sizeof(int)*(n+5));
     d[S]=0;q[1]=S;inq[S]=1;
     while (h!=t){
           h=h<n?h+1:1;i=q[h];inq[i]=0;
           for (p=son[i];p!=-1;p=next[p]){
               j=link[p];
               if (d[i]+cost[p]<d[j]&&cap[p]){
                   d[j]=d[i]+cost[p];pre[j]=p;
                   if (!inq[j])t=t<n?t+1:1,q[t]=j,inq[j]=1;
                   }
               }
           }
     return d[T]>oo?0:1;
}
void update()
{
     int p,flow=oo;
     for (p=T;p!=S;p=st[p]){
         p=pre[p];if (cap[p]<flow)flow=cap[p];
     }
     maxflow+=flow;
     for (p=T;p!=S;p=st[p]){
         p=pre[p];mincost+=cost[p]*flow;
         cap[p]-=flow;cap[opp[p]]+=flow;
     }
}
int main()
{
	freopen("c:\\costflow4.in","r",stdin);
	//freopen("costflow.out","w",stdout);
	ll=0;scanf("%d%d",&n,&m);
	memset(son,-1,sizeof(int)*(n+5));
	S=1;T=n;maxflow=mincost=0;
	for (i=1;i<=m;i++)
	{
        scanf("%d%d%d%d",&x,&y,&z,&w);
        addedge(x,y,z,w);
    }
    while (spfa(S)){
        for (int i=1;i<=n;i++)printf("%d %d %d\n",i,d[i],cap[pre[i]]);
        update();
        }
    //printf("%d\n",maxflow);
    printf("%d\n",mincost);
	system("pause");
	for(;;);
	return 0;
}














