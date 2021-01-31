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
int n,m,i,x,y,z,ll,ans,flow,S,T,pre;
int son[maxn],d[maxn],q[maxn],son_[maxn];
int link[maxm],next[maxm],cap[maxm],opp[maxm],next_[maxm];
int stack[maxm],top,s1,s2;
inline int min(int x,int y){return x<y?x:y;}
void addedge(int x,int y,int z)
{
     link[++ll]=y;next[ll]=son[x];son[x]=ll;cap[ll]=z;opp[ll]=ll+1;
     link[++ll]=x;next[ll]=son[y];son[y]=ll;cap[ll]=0;opp[ll]=ll-1;
}
void rebuild()
{
    int i,j;
    for (i=1;i<=n;i++){
        top=0;
        for (j=son[i];j!=-1;j=next[j])
            if (d[i]+1==d[link[j]]) stack[++top]=j;
        son_[i]=top?stack[1]:-1;
        for (j=1;j<top;j++)next_[stack[j]]=stack[j+1];
        if (top) next_[stack[top]]=-1;
        }
    /*for (i=1;i<=n;i++)
      for (j=son_[i];j!=-1;j=next_[j])
        if (d[i]+1!=d[link[j]])printf("rp\n");*/
}
int build()
{
    int x,y,i,j,l=1,r=1;
    memset(d,-1,sizeof(int)*(n+5));
    q[1]=S;d[S]=0;
    while (l<=r){
          x=q[l++];
          for (i=son[x];i!=-1;i=next[i]){
                y=link[i];
                if (cap[i]&&d[y]==-1){
                    d[y]=d[x]+1;q[++r]=y;
                    if (y==T){rebuild();return 1;}
                    }
                }
          }
    return 0;
}
int find(int now,int flow)
{
    int ret,i,y,w=0,bo;
    if (now==T)return flow;
    for (i=son_[now],pre=0,bo=0;i!=-1&&w<flow;pre=bo?pre:i,i=next_[i],bo=0){
          if (d[now]+1!=d[link[i]]){
              if (i==son[now])son[now]=next_[i];
              next_[pre]=next_[i];
              }
          else {
          //if (d[now]+1!=d[link[i]])printf("rp\n");
          y=link[i];s2++; if (d[y]!=d[now]+1)s1++;
          if (cap[i]&&d[y]==d[now]+1&&(ret=find(y,min(flow-w,cap[i])))){
              cap[i]-=ret;
              cap[opp[i]]+=ret;
              w+=ret;
              }
          }
          }
    if (!w)d[now]=-1;
    return w;
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
        scanf("%d%d%d",&x,&y,&z);addedge(x,y,z);
    }
    while (build())
        while (1){
              flow=find(S,1<<30);
              if (!flow)break;
              ans+=flow;
              }
    printf("%d\n",ans);
    //printf("%d %d\n",s1,s2);
    //system("pause");
    //for(;;);
    return 0;
}


