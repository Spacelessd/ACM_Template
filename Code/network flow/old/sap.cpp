#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
const int maxn=20010;
const int maxm=1000010;
int d[maxn],vd[maxn],son[maxn];
int link[maxm],next[maxm],cap[maxm],opp[maxm];
int n,m,ll,ans,S,T;
inline int min(int a,int b) {return a<b?a:b;}
void addedge(int x,int y,int z)
{
	link[++ll]=y;next[ll]=son[x];son[x]=ll;cap[ll]=z;opp[ll]=ll+1;
	link[++ll]=x;next[ll]=son[y];son[y]=ll;cap[ll]=0;opp[ll]=ll-1;
}
void init()
{
	int i,x,y,z;
	scanf("%d%d",&m,&n);
	memset(son,-1,sizeof(int)*(n+5));
	S=1;T=n;ll=0;ans=0;
	for (i=1;i<=m;i++)scanf("%d%d%d",&x,&y,&z),addedge(x,y,z);
}
int aug(int x,int flow)
{
	int i,j,delta,now=flow,mind=n-1;
	if (x==T)return flow;
	for (j=son[x];j!=-1;j=next[j]){
		i=link[j];
		if (cap[j]>0){
			if (d[x]==d[i]+1){
				delta=aug(i,min(now,cap[j]));
				cap[j]-=delta;cap[opp[j]]+=delta;
				now-=delta;
				if (d[S]>=n)return flow-now;
				if (!now)break;
			}
			if (mind>d[i])mind=d[i];
		}
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
	while(d[S]<n) ans+=aug(S,oo);
}
int main()
{
	//freopen("ditch.in","r",stdin);
	//freopen("ditch.out","w",stdout);
	init();
	sap();
	printf("%d\n",ans);
	//system("pause");
	return 0;
}




