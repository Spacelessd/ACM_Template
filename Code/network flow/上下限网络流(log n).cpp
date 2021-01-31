#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=105,M=50005,inf=1<<29;
struct Tminflow{
	int st[M],ed[M],cap[M],sum[N],S,T,n,tot;
	struct Tmaxflow{
		int son[N],d[N],q[N],link[M],next[M],cap[M],S,T,tot,n;
		void init(int _n){n=_n;memset(son,-1,sizeof(int)*(n+1));tot=1;}
		bool build(){
			int x,y,h=1,t=1;
			memset(d,-1,sizeof(int)*(n+1));
			q[1]=S;d[S]=0;
			while (h<=t){
				x=q[h++];
				for (int i=son[x];i!=-1;i=next[i]){
					y=link[i];
					if (cap[i]&&d[y]==-1){
						d[y]=d[x]+1;q[++t]=y;
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
					cap[i]-=ret,cap[i^1]+=ret,w+=ret;
			}
			if (!w)d[now]=-1;
			return w;
		}
		void add(int x,int y,int z){
			link[++tot]=y;next[tot]=son[x];son[x]=tot;cap[tot]=z;
			link[++tot]=x;next[tot]=son[y];son[y]=tot;cap[tot]=0;
		}
		int run(){
			int ans=0;
			while (build())
				while (1){
					int flow=find(S,inf);
					if (!flow)break;
					ans+=flow;
				}
			return ans;
		}
		bool check(){
			for (int i=son[S];i!=-1;i=next[i])if (cap[i]>0)return 0;
			for (int i=son[T];i!=-1;i=next[i])if (cap[i^1]>0)return 0;
			return 1;
		}
	}maxflow;
	void init(int _n){n=_n;memset(sum,0,sizeof(int)*(n+1));tot=0;}
	void add(int x,int y,int low,int high){
		sum[x]-=low;sum[y]+=low;++tot;st[tot]=x;ed[tot]=y;cap[tot]=high-low;
	}
	bool can(int f){
		maxflow.init(n+2);maxflow.S=n+1;maxflow.T=n+2;
		for (int i=1;i<=n;++i){
			if (sum[i]>0)maxflow.add(maxflow.S,i,sum[i]);
			if (sum[i]<0)maxflow.add(i,maxflow.T,-sum[i]);
		}
		for (int i=1;i<=tot;++i)maxflow.add(st[i],ed[i],cap[i]);
		maxflow.add(T,S,f);maxflow.run();return maxflow.check();
	}
	int run(){
		int l=0,r=inf;
		while (l<r){
			int m=(l+r)>>1;
			if (can(m))r=m;else l=m+1;
		}
		return r;
	}
}minflow;
int visit[N];
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	int n;scanf("%d",&n);minflow.init(n+2);minflow.S=n+1;minflow.T=n+2;
	for (int i=1;i<=n;++i){
		int num;scanf("%d",&num);
		for (int j=1;j<=num;++j){
			int x;scanf("%d",&x);minflow.add(i,x,1,inf);visit[x]=1;
		}
		if (!num)minflow.add(i,minflow.T,0,inf);
	}
	for (int i=1;i<=n;++i)if (!visit[i])minflow.add(minflow.S,i,0,inf);
	printf("%d\n",minflow.run());
	//printf("time=%d\n",clock()-t1);
	system("pause");for(;;);
	return 0;
}


