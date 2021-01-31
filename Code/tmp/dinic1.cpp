#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int maxn=20010;
const int maxm=500010;
int n,m,i,x,y,z,ll,ans,flow,ss,tt;
int son[maxn],d[maxn],q[maxn];
int link[maxm],next[maxm],cap[maxm],opp[maxm];
inline int min(int x,int y){return x<y?x:y;}
int build()
{
    int x,y,i,l,r;
    memset(d,-1,sizeof(int)*(n+5));
    l=r=1;q[1]=ss;d[ss]=0;
    while (l<=r){
          x=q[l++];i=son[x];
          while (i!=-1){
                y=link[i];
                if (cap[i]&&d[y]==-1){
                    d[y]=d[x]+1;
                    if (y==tt)return 1;
                    q[++r]=y;
                    }
                i=next[i];
                }
          }
    return 0;
}
int find(int now,int flow)
{
    int ret,i,y,w;
    if (now==tt)return flow;
    i=son[now];w=0;
    while (i!=-1&&w<flow){
          y=link[i];
          if (cap[i]&&d[y]==d[now]+1){
              ret=find(y,min(flow-w,cap[i]));
              if (ret){
                  cap[i]-=ret;
                  cap[opp[i]]+=ret;
                  w+=ret;
                  }
              }
          i=next[i];
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
    ss=0;tt=n+1;ans=0;
    while (build())
        while (1){
              flow=find(ss,1<<30);
              if (!flow)break;
              ans+=flow;
              }
    printf("%d\n",ans);
    //system("pause");
    return 0;
}











