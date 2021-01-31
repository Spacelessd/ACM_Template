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
	int st[M],ed[M],low[M],high[M],S,T,n,tot;
	struct Tmaxflow{
		int son[N],d[N],q[N],link[M],next[M],cap[M],can[M],S,T,tot,n;
		void init(int _n){n=_n;tot=1;memset(son,-1,sizeof(int)*(n+1));}
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
		void del(int x,int y){
			memset(can,0,sizeof(int)*(tot+1));
			for (int i=son[S];i!=-1;i=next[i])can[i]=can[i^1]=1;
			for (int i=son[T];i!=-1;i=next[i])can[i]=can[i^1]=1;
			for (int i=son[x];i!=-1;i=next[i])if (link[i]==y)can[i]=can[i^1]=1;
		}
	}maxflow;
	void init(int _n){n=_n;tot=0;}
	void add(int x,int y,int _low,int _high){
		++tot;st[tot]=x;ed[tot]=y;low[tot]=_low;high[tot]=_high;
	}
	int run(){
		maxflow.init(n+2);maxflow.S=n+1;maxflow.T=n+2;
		for (int i=1;i<=tot;++i)maxflow.add(st[i],ed[i],high[i]-low[i]),
			maxflow.add(st[i],maxflow.T,low[i]),maxflow.add(maxflow.S,ed[i],low[i]);
		maxflow.add(T,S,inf);maxflow.run();if (!maxflow.check())return -1;
		maxflow.del(S,T);maxflow.S=T;maxflow.T=S;maxflow.run();
		int res=0;
		for (int i=1;i<=tot;++i)if (st[i]==S)res+=low[i];
		for (int i=maxflow.son[S];i!=-1;i=maxflow.next[i])
			if (!maxflow.can[i])res+=maxflow.cap[i^1];
		return res;
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


