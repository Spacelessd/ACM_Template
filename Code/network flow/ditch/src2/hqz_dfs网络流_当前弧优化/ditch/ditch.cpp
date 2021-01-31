/*
ID:hqztrue1
LANG:C++
TASK:ditch
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxn 1510
int n,m,S,T,i,x,y,z,ans;
int a[maxn][maxn],p[maxn],cur[maxn];
inline int min(int x,int y){return x<y?x:y;}
int find(int now,int flow)
{
    int ret,i,j,y;
    if (now==T)return flow;
    p[now]=1;
    for (j=1,i=cur[now]+1;j<=n;j++,i=i<n?i+1:1)
        if (!p[i]&&a[now][i]&&(ret=find(i,min(flow,a[now][i]))))
        {
            a[now][i]-=ret;a[i][now]+=ret;
            cur[now]=i<n?i:0;;return ret;
        }
    return 0;
}
void network_flow(){
     int flow;
     while (flow=find(S,1<<30)){
         memset(p,0,sizeof(int)*(n+5));
         ans+=flow;
         }
}
int main()
{
    freopen("ditch.in","r",stdin);
    freopen("ditch.out","w",stdout);
    scanf("%d%d",&m,&n);
    for (i=1;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        a[x][y]+=z;
        }
    S=1;T=n;
    network_flow();
    printf("%d\n",ans);
    return 0;
}
