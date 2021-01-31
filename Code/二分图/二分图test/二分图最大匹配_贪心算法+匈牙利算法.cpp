#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100005
struct Edge{
	#define Mx 300005
	int link[Mx],next[Mx],son[Mx],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
};
Edge e,g;
int degree[N],visit[N],n1,n2,n,ans;
struct node{
	int x,d;
	node(){}
	node(int _x,int _d):x(_x),d(_d){}
	friend bool operator <(node x,node y){
		return x.d<y.d||x.d==y.d&&x.x<y.x;
	}
};
struct heap{
	#define N_heap 500005
	typedef node value;
	value a[N_heap];int len;
	heap(){len=0;}
	void up(int x){
		int i=x;value j;
		while (i>1&&a[i]<a[i>>1]){
			j=a[i];a[i]=a[i>>1];a[i>>1]=j;i>>=1;
		}
	}
	void down(int x){
		int i=x,j;value k;
		while (i<<1<=len){
			j=i; if (a[i<<1]<a[i])j=i<<1;
			if ((i<<1)+1<=len&&a[(i<<1)+1]<a[j])j=(i<<1)+1;
			if (j==i)break;
			k=a[i];a[i]=a[j];a[j]=k; i=j;
		}
	}
	void insert(value x){a[++len]=x;up(len);}
	bool empty(){return len==0;}
	value top(){return a[1];}
	void pop(){a[1]=a[len--];down(1);}
};
heap Q;
void del(int x){
	visit[x]=1;
	for (int p=e.son[x];p;p=e.next[p])
		if (!visit[e.link[p]]){
		--degree[e.link[p]];
		if (e.link[p]<=n1)Q.insert(node(e.link[p],degree[e.link[p]]));
	}
}
int y[N],link[N],greedy[N],time;
bool find(int v){
	for (int p=g.son[v],i;p;p=g.next[p]){
		i=g.link[p];
		if (y[i]!=time){
			y[i]=time;
			if (!link[i]||find(link[i])){
				link[i]=v;return 1;
			}
		}
	}
	return 0;
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("9.out","w",stdout);
	int m,x,y;e.clear();
	scanf("%d%d%d",&n1,&n2,&m);
	n=n1>n2?n1:n2;
	for (int i=1;i<=m;++i)
		scanf("%d%d",&x,&y),g.addedge(x,y),y+=n1,
		e.addedge(x,y),e.addedge(y,x),++degree[x],++degree[y];
	for (int i=1;i<=n1;++i)Q.insert(node(i,degree[i]));
	memset(link,0,sizeof(link));
	while (1){
		int d=1<<30,x,y=-1;
		while (!Q.empty()&&visit[Q.top().x])Q.pop();
		if (Q.empty())break;
		x=Q.top().x;Q.pop();
		for (int p=e.son[x];p;p=e.next[p])
			if (!visit[e.link[p]]&&degree[e.link[p]]<d)
				d=degree[e.link[p]],y=e.link[p];
		del(x);
		if (y>=0)del(y),++ans,link[y-n1]=x,greedy[x]=1;
		//printf("match %d %d\n",x,y);
	}
	//ans=0;
	/*for (int i=1;i<=n1;++i){
		for (int j=g.son[i];j;j=g.next[j])
			if (!link[g.link[j]]){greedy[i]=1;link[g.link[j]]=i;++ans;break;}
	}*/
	for (int i=1;i<=n1;++i)
		if (!greedy[i]){
			time=i;if (find(i))++ans;
		}
	printf("%d\n",ans);
	//system("pause");for (;;);
	return 0;
}


