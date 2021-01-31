#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxn 1510
int n,m,S,T,i,x,y,z,ans;
int a[maxn][maxn],p[maxn];
inline int min(int x,int y){return x<y?x:y;}
int find(int now,int flow)
{
    int ret,i,y,w=0;
    if (now==T)return flow;
    p[now]=1;
    for (i=1;i<=n;i++)
        if (!p[i]&&a[now][i]&&(ret=find(i,min(flow-w,a[now][i]))))
        {
            a[now][i]-=ret;
            a[i][now]+=ret;
            w+=ret;
            if (w==flow)break;
        }
    return w;
}
void network_flow(){
     int flow;
     while (1){
         memset(p,0,sizeof(int)*(n+5));
         flow=find(S,1<<30);
         if (!flow)break;
         ans+=flow;
         }
}
int main()
{
    //freopen("ditch.in","r",stdin);
    //freopen("ditch.out","w",stdout);
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
