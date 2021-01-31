#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
const int maxn=2010;
int c[maxn][maxn];
int d[maxn],vd[maxn];
int n,m,flow,S,T;
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
     int i,delta,now=flow,mind=n-1;
     if (x==T)return flow;
     for (i=1;i<=n;i++)
         if (c[x][i]>0){
             if (d[x]==d[i]+1){
                 delta=aug(i,min(now,c[x][i]));
                 c[x][i]-=delta;c[i][x]+=delta;
                 now-=delta;
                 if (d[S]>=n)return flow-now;
                 if (!now)break;
                 }
             if (mind>d[i])mind=d[i];
             }
     if (flow==now){
         vd[d[x]]--;
         if (!vd[d[x]])d[S]=n;
         d[x]=mind+1;
         vd[d[x]]++;
         }
     return flow-now;
}
void sap()
{
	memset(d,0,sizeof(int)*(n+5));
	memset(vd,0,sizeof(int)*(n+5));
	vd[0]=n;
	while(d[S]<n) flow+=aug(S,oo);
}
int main()
{
	//freopen("ditch.in","r",stdin);
	//freopen("ditch.out","w",stdout);
	init();
	sap();
	printf("%d\n",flow);
	system("pause");
	return 0;
}














