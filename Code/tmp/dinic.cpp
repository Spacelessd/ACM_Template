#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int maxn=20010;
const int maxm=500010;
int n,m,i,x,y,z,ll,ans,flow,S,T;
int son[maxn],d[maxn],q[maxn];
int link[maxm],next[maxm],cap[maxm],opp[maxm];
inline int min(int x,int y){return x<y?x:y;}
bool build()
{
    int x,y,i,l=1,r=1;
    memset(d,-1,sizeof(int)*(n+5));
    q[1]=S;d[S]=0;
    while (l<=r){
          x=q[l++];
          for (i=son[x];i!=-1;i=next[i]){
                y=link[i];
                if (cap[i]&&d[y]==-1){
                    d[y]=d[x]+1;q[++r]=y;
                    if (y==T)return 1;
                    }
                }
          }
    return 0;
}
int find(int now,int flow)
{
    int ret,i,y,w=0;
    if (now==T)return flow;
    for (i=son[now];i!=-1&&w<flow;i=next[i]){
          y=link[i];
          if (cap[i]&&d[y]==d[now]+1&&(ret=find(y,min(flow-w,cap[i])))){
              cap[i]-=ret;
              cap[opp[i]]+=ret;
              w+=ret;
              }
          }
    if (!w)d[now]=-1;
    return w;
}
void addedge(int x,int y,int z)
{
     link[++ll]=y;next[ll]=son[x];son[x]=ll;cap[ll]=z;opp[ll]=ll+1;
     link[++ll]=x;next[ll]=son[y];son[y]=ll;cap[ll]=0;opp[ll]=ll-1;
}
int main()
{
    //freopen("ditch.in","r",stdin);
    //freopen("ditch.out","w",stdout);
    ll=0;scanf("%d%d",&n,&m);
    memset(son,-1,sizeof(int)*(n+5));
    for (i=1;i<=n;i++)
    {
        x=0;y=i;scanf("%d",&z);addedge(x,y,z);
        x=i;y=n+1;scanf("%d",&z);addedge(x,y,z);
    }
    for (i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        link[++ll]=y;next[ll]=son[x];son[x]=ll;cap[ll]=z;opp[ll]=ll+1;
        link[++ll]=x;next[ll]=son[y];son[y]=ll;cap[ll]=z;opp[ll]=ll-1;
    }
    S=0;T=n+1;ans=0;
    while (build())
        while (1){
              flow=find(S,1<<30);
              if (!flow)break;
              ans+=flow;
              }
    printf("%d\n",ans);
    //system("pause");
    return 0;
}











