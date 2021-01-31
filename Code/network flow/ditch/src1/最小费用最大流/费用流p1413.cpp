#include<cstdio>
#include<iostream>
#include<memory.h>
using namespace std;
#define min(a,b) (a)<(b)?(a):(b)
const int oo=19951006;
int n,m,k,l=0,w,ans,len,augc;
int f[100005],d[20005],b[20005],son[20005],pre[20005];
int st[50005],ed[50005],cost[50005],next[50005],data[50005];

int num(int x,int y,int z)
{
    return n*m*z+(x-1)*m+y;
}

void add(int x,int y,int z,int c)
{
     l++; next[l]=son[x]; son[x]=l;
     st[l]=x; ed[l]=y; data[l]=z; cost[l]=c;
}

void build(int x,int y,int z,int c)
{
     add(x,y,z,c);
     add(y,x,0,-c);
}

int spfa(int u)
{
    memset(b,0,sizeof(b));    
    for (int i=1;i<=n*m*2;i++) d[i]=oo; d[u]=0;
    int h=0,t=1; f[1]=u; b[u]=1;
    while (h<t){
          int i=f[++h],p=son[i];
          while (p){
                int j=ed[p];
                if (data[p]>0 && cost[p]+d[i]<d[j]){
                   d[j]=d[i]+cost[p];
                   pre[j]=p;
                   if (!b[j]){f[++t]=j; b[j]=1;}
                   }
                p=next[p];
                }
          b[i]=0;
          }
    return d[n*m*2];
}    

int main()
{
    scanf("%d%d%d",&k,&m,&n);
    memset(son,0,sizeof(son));
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++){
            scanf("%d",&w);
            if (i==1 && j==1){
               build(num(1,1,0),num(1,1,1),k,0);
               build(num(1,1,1),num(1,2,0),oo,0);
               build(num(1,1,1),num(2,1,0),oo,0);
               ans-=w; continue;
               }
            if (i==n && j==m){
               build(num(n,m,0),num(n,m,1),k,0);    
               ans-=w; continue;
               }
            build(num(i,j,0),num(i,j,1),1,-w);
            build(num(i,j,0),num(i,j,1),oo,0);
            if (i!=n) build(num(i,j,1),num(i+1,j,0),oo,0);
            if (j!=m) build(num(i,j,1),num(i,j+1,0),oo,0);
            }    
    memset(pre,0,sizeof(pre));
    memset(f,0,sizeof(f));
    while ((len=spfa(1))<oo){
          augc=oo; int p=n*m*2;
          while (p!=1){
                augc=min(augc,data[pre[p]]);
                p=st[pre[p]];
                }
          p=n*m*2;          
          while (p!=1){
                data[pre[p]]-=augc;
                if (pre[p]%2==1) data[pre[p]+1]+=augc;
                else data[pre[p]-1]+=augc;
                p=st[pre[p]];
                }
          ans+=augc*len;
          }
    printf("%d\n",-ans);
    //system("pause");
    return 0;
}
