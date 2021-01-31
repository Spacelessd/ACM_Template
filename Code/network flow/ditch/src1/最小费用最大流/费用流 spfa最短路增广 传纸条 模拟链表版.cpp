#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define min(a,b) (a)>(b)?(b):(a)
const int maxn=1000000;
const int oo=1993101215;
int f[maxn],que[maxn],hash[maxn];
int other[maxn],pre[maxn],last[maxn],cap[maxn],cost[maxn],my[maxn],cup[maxn];
int i,j,n,m,w,ed,l,r,u,augc,ans,path,e;

int num(int x,int y,int p)
{
    if (p==0)
       return ((x-1)*m+y);
    else
       return (n*m+(x-1)*m+y);
}

int spfa(int u)
{
    int i,q,p;
    memset(hash,0,sizeof(hash));
    for (i=1;i<=ed;i++)
        f[i]=oo;
    f[u]=0;
    l=0;
    r=1;
    que[r]=u;
    hash[u]=1;
    while (l<r)
    {
          q=que[++l];
          p=last[q];
          while (p!=0)
          {
              if ((cap[p]>0)&&(f[other[p]]>f[q]+cost[p]))
              {
                   f[other[p]]=f[q]+cost[p];
                   cup[other[p]]=p;
                   if (hash[other[p]]==0)
                   {
                       que[++r]=other[p];
                       hash[other[p]]=1;
                   }
              }
              p=pre[p];
          }
          hash[q]=0;
    }
    return f[ed];
}

void add(int u,int v,int c,int w)
{
     e++;
     pre[e]=last[u];
     last[u]=e;
     other[e]=v;
     my[e]=u;
     cap[e]=c;
     cost[e]=w;
}

void build(int u,int v,int c,int w)
{
     add(u,v,c,w);
     add(v,u,0,-w);
}

int main()
{
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
        {
            scanf("%d",&w);
            if ((i==1)&&(j==1))
            {
                 build(num(1,1,0),num(1,1,1),2,0);
                 build(num(1,1,1),num(1,2,0),1,0);
                 build(num(1,1,1),num(2,1,0),1,0);
            }
            else
            if ((i==n)&&(j==m))
                 build(num(n,m,0),num(n,m,1),2,0);
            else
            {               
                build(num(i,j,0),num(i,j,1),1,-w);
                if (i!=n)
                     build(num(i,j,1),num(i+1,j,0),1,0);
                if (j!=m)
                     build(num(i,j,1),num(i,j+1,0),1,0);              
            }
        }
    ed=n*m*2;
    ans=0;
    while ((path=spfa(1))<oo)
    {
          augc=oo;
          u=ed;
          while (u!=1)
          {
               augc=min(cap[cup[u]],augc);
               u=my[cup[u]];
          }
          u=ed;
          while (u!=1)
          {
               cap[cup[u]]-=augc;
               if (cup[u]%2==1)
                  cap[cup[u]+1]+=augc;
               else
                  cap[cup[u]-1]+=augc;
               u=my[cup[u]];
          }          
          ans=ans+augc*path; 
    }
    printf("%d",abs(ans));
    system("pause");
    return 0;
}
