//dfs增广的最大流(加入当前弧优化） 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int maxn=510;
const int oo=1993101215;
int cap[maxn][maxn],hash[maxn],data[maxn]; //hash[i]表示当前增广是否访问过这个节点（避免死循环）
int i,j,n,m,u,v,w,ans,flow;

int min(int a,int b)
{
    if (a>b) return b;
    else
    return a;
}

int dfs(int u,int low)        
{
    int i,num;
    if (u==n) return low;
    if (hash[i]==1) return 0;
    for (i=data[u];i<=n;i++)
        if ((cap[u][i]>0)&&(hash[i]==0))
        {
           hash[i]=1;
           num=dfs(i,min(cap[u][i],low));
           data[u]=i;
           if (num>0)
           {
                cap[u][i]-=num;
                cap[i][u]+=num;
                return num;
           }
        }
    return 0;
}

int main()
{
    memset(hash,0,sizeof(hash));
    memset(cap,0,sizeof(cap));
    scanf("%d%d",&m,&n);
    

    
    for (i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        cap[u][v]+=w;
    }

    while ((flow=dfs(1,oo))>0)
    {
        ans+=flow;
        memset(hash,0,sizeof(hash));
        for (i=1;i<=n;i++)
           data[i]=1;
    }
    printf("%d",ans);
    //system("pause");
}
