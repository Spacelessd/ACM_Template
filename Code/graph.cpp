#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
template<size_t N,size_t M>
struct graph{
	#define new_arr(arr) arr=new int[n+5]
	#define oo (1<<29)
	int link[M],cost[M],next[M],son[N],*cap,*opp,*st,l;
	void add(int x,int y,int z=0){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
	void clear(){l=0;memset(son,-1,sizeof(son));}
	void set(int _n){n=_n;clear();}
	graph():n(0),cap(NULL),opp(NULL){}
	graph(int _n):n(_n),cap(NULL),opp(NULL){clear();}
	void addedge(int x,int y){add(x,y);}
	void addedge2(int x,int y){add(x,y);add(y,x);}
	void addedge(int x,int y,int z){add(x,y,z);}
	void addedge2(int x,int y,int z){add(x,y,z);add(y,x,z);}
	void addedge_f(int x,int y,int z){
		if (!cap)cap=new int[M],opp=new int[M];
		link[++l]=y;next[l]=son[x];son[x]=l;cap[l]=z;opp[l]=l+1;
		link[++l]=x;next[l]=son[y];son[y]=l;cap[l]=0;opp[l]=l-1;
	}
	void addedge_c(int x,int y,int z,int c){
		if (!cap)cap=new int[M],opp=new int[M];if (!st)st=new int[M];
		link[++l]=y;st[l]=x;next[l]=son[x];son[x]=l;cap[l]=z;cost[l]=c;opp[l]=l+1;
		link[++l]=x;st[l]=y;next[l]=son[y];son[y]=l;cap[l]=0;cost[l]=-c;opp[l]=l-1;
	}
	int *inq,*q,*d,*f,*pre,n,S,T;
	void spfa(int S,int *d){
		int h=0,t=1;new_arr(inq);new_arr(q);
		for (int i=1;i<=n;++i)d[i]=oo;
		for (int i=1;i<=n;++i)inq[i]=0;
		d[S]=0;q[1]=S;inq[S]=1;
		while (h!=t){
			h=h<n?h+1:1;int i=q[h];inq[i]=0;
			for (int p=son[i];p!=-1;p=next[p]){
				int j=link[p];
				if (d[i]+cost[p]<d[j]){
					d[j]=d[i]+cost[p];
					if (!inq[j])t=t<n?t+1:1,q[t]=j,inq[j]=1;
				}
			}
		}
		delete[] inq;delete[] q;
	}
	struct d_node{
		int d,x;
		d_node(int _d,int _x){d=_d;x=_x;}
		bool operator <(const d_node &y)const{return d>y.d;}
	};
	void dijkstra(int S,int *dis){
		priority_queue<d_node> Q;
		bool *visit=new bool[n+5];
		for (int i=1;i<=n;++i)visit[i]=0,dis[i]=oo;
		Q.push(d_node(0,S));
		while (!Q.empty()){
			int d=Q.top().d,x=Q.top().x;visit[x]=1;dis[x]=d;
			for (int p=son[x];p!=-1;p=next[p])
				Q.push(d_node(d+cost[p],link[p]));
			while (visit[Q.top().x]&&!Q.empty())Q.pop();
		}
		delete[] visit;
	}
	int *dfn,*low,*stack,*instack,*num,top,D,now;
	void tarjan_f(int x){
		dfn[x]=low[x]=++D;stack[++top]=x;instack[x]=1;
		for (int p=son[x];p!=-1;p=next[p]){
			int j=link[p];
			if (!dfn[j]) tarjan_f(j),low[x]=min(low[x],low[j]);
			else if (instack[j]) low[x]=min(low[x],dfn[j]);
		}
		if (low[x]==dfn[x]){
			int k;++now;
			do k=stack[top--],instack[k]=0,num[k]=now; while (k!=x);
		}
	}
	void tarjan(int *_num){
		new_arr(dfn);new_arr(low);new_arr(stack);new_arr(instack);
		memset(dfn,0,sizeof(int)*(n+5));D=0;top=0;now=0;num=_num;
		for (int i=1;i<=n;++i)if (!dfn[i])tarjan(i);
		delete[] dfn;delete[] low;delete[] stack;delete[] instack;
	}
	int toposort(int *q){
		int *in;new_arr(in);
		int h=0,t=0;
		for (int i=1;i<=n;++i)in[i]=0;
		for (int i=1;i<=n;++i)
			for (int p=son[i];p!=-1;p=next[p])++in[link[p]];
		for (int i=1;i<=n;++i)if (!in[i])q[++t]=i;
		while (h<t){
			int i=q[++h];
			for (int p=son[i];p!=-1;p=next[p]){
				int j=link[p]; --in[j];
				if (!in[j])q[++t]=j;
			}
		}
		delete[] in;return t;
	}
	int find(int x){
		if (f[x]==x)return x;
		else return f[x]=find(f[x]);
	}
	struct k_edge{
		int x,y,z,id;
		bool operator <(const k_edge &y)const{return z<y.z;}
	};
	int kruskal(){
		k_edge *e=new k_edge[l+5];new_arr(f);
		int m=0,ans=0,num=0;
		for (int i=1;i<=n;++i)
			for (int p=son[i];p!=-1;p=next[p])
				e[++m].x=i,e[m].y=link[p],e[m].z=cost[p],e[m].id=m;
		std::sort(e+1,e+1+m);
		for (int i=1;i<=n;++i)f[i]=i;
		for (int i=1;i<=m;++i){
			int f1=find(e[i].x),f2=find(e[i].y);
			if (f1!=f2)f[f1]=f2,ans+=e[i].z,++num;
		}
		delete[] e;delete[] f;
		if (num==n-1)return ans;else return oo;
	}
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
	int maxflow(int _S,int _T){  //dinic
		int ans=0;new_arr(d);new_arr(q);S=_S;T=_T;
		while (build()) while (1){
			int flow=find(S,oo);
			if (!flow)break;
			ans+=flow;
		}
		delete[] d;delete[] q;
		return ans;
	}
	int spfa_c(){
		int h=0,t=1,i,j,p;
		for (int i=0;i<=n;++i)d[i]=oo;
		for (int i=0;i<=n;++i)inq[i]=0;
		d[S]=0;q[1]=S;inq[S]=1;
		while (h!=t){
			h=h<n?h+1:1;i=q[h];inq[i]=0;
			for (p=son[i];p!=-1;p=next[p]){
				j=link[p];
				if (d[i]+cost[p]<d[j]&&cap[p]){
					d[j]=d[i]+cost[p];pre[j]=p;
					if (!inq[j])t=t<n?t+1:1,q[t]=j,inq[j]=1;
				}
			}
		}
		return d[T]<oo?1:0;
	}
	void update(int &maxflow,int &mincost){
		int p,flow=oo;
		for (p=T;p!=S;p=st[p]){
			p=pre[p];if (cap[p]<flow)flow=cap[p];
		}
		maxflow+=flow;
		for (p=T;p!=S;p=st[p]){
			p=pre[p];mincost+=cost[p]*flow;
			cap[p]-=flow;cap[opp[p]]+=flow;
		}
	}
	pair<int,int> costflow(int _S,int _T){
		int maxflow,mincost;S=_S;T=_T;new_arr(d);new_arr(q);new_arr(inq);new_arr(pre);
		maxflow=mincost=0;while (spfa_c())update(maxflow,mincost);
		delete[] d;delete[] q;delete[] inq;delete[] pre;
		return make_pair(maxflow,mincost);
	}
	template<int _N,int _M>
	void floyd(int (&a)[_N][_M]){
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n;++j)a[i][j]=oo;
		for (int i=1;i<=n;++i)a[i][i]=0;
		for (int x=1;x<=n;++x)
			for (int p=son[x],y=link[p];p!=-1;p=next[p],y=link[p])
				a[x][y]=min(a[x][y],cost[p]);
		for (int k=1;k<=n;++k)
			for (int i=1;i<=n;++i)
				for (int j=1;j<=n;++j)
					a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
	}
	template<int _N,int _M>
	void Johnson(int (&a)[_N][_M]){
		if (n<1)return;
		int *_cost=new int[l];new_arr(d);spfa(1,d);
		memcpy(_cost,cost,sizeof(int)*l);
		for (int x=1;x<=n;++x)
			for (int p=son[x],y=link[p];p!=-1;p=next[p],y=link[p])
				cost[p]+=d[x]-d[y];
		for (int i=1;i<=n;++i){
			dijkstra(i,a[i]);
			for (int j=1;j<=n;++j)a[i][j]+=d[j]-d[i];
		}
		memcpy(cost,_cost,sizeof(int)*l);
		delete[] d;delete[] _cost;
	}
	#undef oo
	#undef new_arr
};
const int N=105,M=1005;
graph<N,M> G;
int d[N];
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n=3;G.set(n);
	G.addedge(1,2,1);//G.addedge(2,3,100);G.addedge(1,2,10);
	G.spfa(1,d);
	for (int i=1;i<=n;++i)printf("%d\n",d[i]);
	G.set(3);
	G.addedge_f(1,2,3);G.addedge_f(1,3,30);G.addedge_f(2,4,300);G.addedge_f(3,4,1);
	printf("%d\n",G.maxflow(1,4));
	system("pause");for (;;);
	return 0;
}


