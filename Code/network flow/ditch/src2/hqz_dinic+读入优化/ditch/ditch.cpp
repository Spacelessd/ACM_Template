/*
ID:hqztrue1
LANG:C++
TASK:ditch
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int maxn=20010;
const int maxm=1000010;
int n,m,i,x,y,z,ll,ans,flow,S,T;
int son[maxn],d[maxn],q[maxn];
int link[maxm],next[maxm],cap[maxm],opp[maxm];
inline int min(int x,int y){return x<y?x:y;}
inline void read(int &x){
	int ch;x=0;
	for (ch=getchar();!(ch>='0' && ch<='9');ch=getchar());
	for (;ch>='0' && ch<='9';x=x*10+ch-'0',ch=getchar());
}

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
    freopen("ditch.in","r",stdin);
    freopen("ditch.out","w",stdout);
    scanf("%d%d",&m,&n);
    memset(son,-1,sizeof(int)*(n+5));
    S=1;T=n;ans=0;ll=0;
    for (i=1;i<=m;i++)
    {
        //scanf("%d%d%d",&x,&y,&z);
        read(x);read(y);read(z);addedge(x,y,z);
    }
    while (build())
        while (1){
              flow=find(S,1<<30);
              if (!flow)break;
              ans+=flow;
              }
    printf("%d\n",ans);
    //system("pause");
    //for(;;);
    return 0;
}










