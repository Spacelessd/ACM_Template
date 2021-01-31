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
int n,m,i,x,y,z,sums,sumt,S,T,ll;
int h[maxn],sumh[maxn*2],son[maxn];
int link[maxm],next[maxm],cap[maxm],opp[maxm];
int q[maxn];
void addedge(int x,int y,int z)
{
    link[++ll]=y;next[ll]=son[x];son[x]=ll;cap[ll]=z;opp[ll]=ll+1;
    link[++ll]=x;next[ll]=son[y];son[y]=ll;cap[ll]=0;opp[ll]=ll-1;
}
void build()
{
    int x,y,i,l=1,r=1;
    for (i=1;i<=n;i++)h[i]=n*2;
    q[1]=T;h[T]=0;
    while (l<=r){
          x=q[l++];
          for (i=son[x];i!=-1;i=next[i]){
                y=link[i];
                if (cap[opp[i]]&&h[x]+1<h[y]){
                    h[y]=h[x]+1;q[++r]=y;
                    }
                }
          }
    h[S]=n;
    memset(sumh,0,sizeof(int)*(n+5));
    for (i=1;i<=n;i++)sumh[h[i]]++;
}
int main()
{
    freopen("ditch.in","r",stdin);
    freopen("ditch.out","w",stdout);
    scanf("%d%d",&m,&n);
    memset(son,-1,sizeof(int)*(n+5));
    S=1;T=n;ll=0;
    for (i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&z),addedge(x,y,z);
        if (x==y)continue;
        if (x==S)sums+=z;
        if (y==T)sumt+=z;
    }
    build();
    printf("%d\n",sums<sumt?sums:sumt);
    //system("pause");
    //for(;;);
    return 0;
}


