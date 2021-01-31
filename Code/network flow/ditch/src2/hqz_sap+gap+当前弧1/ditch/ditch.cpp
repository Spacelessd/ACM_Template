/*
ID:hqztrue1
LANG:C++
TASK:ditch
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
const int maxn=3010;
const int maxm=500010;
int c[maxn][maxn];
int d[maxn],vd[maxn],cur[maxn];
int n,m,ans,S,T;
inline int min(int a,int b) {return a<b?a:b;}
void init()
{
     int i,x,y,z;
     scanf("%d%d",&m,&n);
     S=1;T=n;
     for (i=1;i<=m;i++){
         scanf("%d%d%d",&x,&y,&z);
         c[x][y]+=z;
         }
}
int aug(int x,int flow)
{
     int i,delta,now=flow,mind,place;
     if (x==T)return flow;
     for (i=cur[x];i<=n;i++)
         if (c[x][i]>0){
             if (d[x]==d[i]+1){
                 cur[x]=i;
                 delta=aug(i,min(now,c[x][i]));
                 c[x][i]-=delta;c[i][x]+=delta;
                 now-=delta;
                 if (d[S]>=n)return flow-now;
                 if (!now)break;
                 }
             }
     if (flow==now){
         mind=n-1;
         for (i=1;i<=n;i++)if (c[x][i]&&d[i]<mind)mind=d[i],place=i;
         vd[d[x]]--;
         if (!vd[d[x]])d[S]=n;
         d[x]=mind+1;
         vd[d[x]]++;
         cur[x]=place;
         }
     return flow-now;
}
void sap()
{
	memset(d,0,sizeof(int)*(n+5));
	memset(vd,0,sizeof(int)*(n+5));
	for (int i=1;i<=n;i++)cur[i]=1;
	vd[0]=n;
	while(d[S]<n) ans+=aug(S,oo);
}
int main()
{
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
	init();
	sap();
	printf("%d\n",ans);
	//system("pause");
	return 0;
}














