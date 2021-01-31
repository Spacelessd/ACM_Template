#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
#define N 200005
#define M 1000005
int n,S,T,ll,son[N],d[N],q[N],link[M],next[M],cap[M],opp[M];
inline int min(int x,int y){return x<y?x:y;}
bool build(){
	int x,y,l=1,r=1;
	memset(d,-1,sizeof(int)*(n+5));
	q[1]=S;d[S]=0;
	while (l<=r){
		x=q[l++];
		for (int i=son[x];i!=-1;i=next[i]){
			y=link[i];
			if (cap[i]&&d[y]==-1){
				d[y]=d[x]+1;q[++r]=y;
				if (y==T)return 1;
			}
		}
	}
	return 0;
}
int find(int now,int flow){
	int ret,y,w=0;
	if (now==T)return flow;
	for (int i=son[now];i!=-1&&w<flow;i=next[i]){
		y=link[i];
		if (cap[i]&&d[y]==d[now]+1&&(ret=find(y,min(flow-w,cap[i]))))
			cap[i]-=ret,cap[opp[i]]+=ret,w+=ret;
	}
	if (!w)d[now]=-1;
	return w;
}
void addedge(int x,int y,int z){
	link[++ll]=y;next[ll]=son[x];son[x]=ll;cap[ll]=z;opp[ll]=ll+1;
	link[++ll]=x;next[ll]=son[y];son[y]=ll;cap[ll]=0;opp[ll]=ll-1;
}
int main()
{
	int m,x,y,ans,flow,n1,n2;
	freopen("1.in","r",stdin);
	freopen("8.out","w",stdout);
	scanf("%d%d%d",&n1,&n2,&m);
	n=n1+n2+2;
	memset(son,-1,sizeof(int)*(n+5));
	S=n1+n2+1;T=n1+n2+2;ans=0;ll=0;
	for (int i=1;i<=m;++i)
		scanf("%d%d",&x,&y),addedge(x,n1+y,1);
	for (int i=1;i<=n1;++i)addedge(S,i,1);
	for (int i=1;i<=n2;++i)addedge(n1+i,T,1);
	while (build())
		while (1){
			flow=find(S,1<<30);
			if (!flow)break;
			ans+=flow;
		}
	printf("%d\n",ans);
	//system("pause");for(;;);
	return 0;
}


