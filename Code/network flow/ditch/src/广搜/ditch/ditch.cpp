/*
ID:hqztrue1
LANG:C++
TASK:ditch
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
const int maxn=3010;
const int oo=1993101215;
int cap[maxn][maxn],f[maxn][maxn],a[maxn],pre[maxn];
int que[maxn];

int min(int a,int b)
{
    int min;
    min=(a>b)?b:a;
    return min;
}

int main()
{
    freopen("ditch.in","r",stdin);
    freopen("ditch.out","w",stdout);
    int n,m,i,j,u,v,w,l,r,ans=0,q;
    scanf("%d%d",&m,&n);
    for (i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        cap[u][v]+=w;
    }
    
    int s=1,t=n;
    //memset(f,0,sizeof(f));
    while (1)
    {
         memset(a,0,sizeof(a));
         a[s]=oo;
         l=0;
         r=1;
         que[r]=s;
         while (l<r)
         {
               l++;
               q=que[l];
               for (i=1;i<=n;i++) 
                   if ((a[i]==0)&&(cap[q][i]>f[q][i]))
                   {
                        r++;
                        que[r]=i;
                        pre[i]=q;
                        a[i]=min(cap[q][i]-f[q][i],a[q]);
                   }
         }
         if (a[t]==0) break;
         for (int i=t;i!=s;i=pre[i])
         {
              f[i][pre[i]]-=a[t];
              f[pre[i]][i]+=a[t];
         }
         ans+=a[t];
    }
    printf("%d\n",ans);
    //system("pause");
    return 0;
}
