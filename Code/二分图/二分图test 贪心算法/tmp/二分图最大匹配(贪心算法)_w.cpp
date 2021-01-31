#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
struct Edge{
	#define Mx 300005
	int link[Mx],next[Mx],son[Mx],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
};
Edge e;
int degree[N],visit[N],n1,n2,ans;
struct node{
	int x;
	node(){}
	node(int _x):x(_x){}
	friend bool operator <(node x,node y){
		return degree[x.x]<degree[y.x]||degree[x.x]==degree[y.x]&&x.x<y.x;
	}
};
struct heap{
	#define N 500005
	typedef node value;
	value a[N];int len;
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
		if (e.link[p]<=n1)Q.insert(node(e.link[p]));
	}
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("3.out","w",stdout);
	int m,x,y;e.clear();
	scanf("%d%d%d",&n1,&n2,&m);
	for (int i=1;i<=m;++i)
		scanf("%d%d",&x,&y),y+=n1,e.addedge(x,y),e.addedge(y,x),
		++degree[x],++degree[y];
	for (int i=1;i<=n1;++i) Q.insert(node(i));
	while (1){
		int d=1<<30,x=-1,y=-1;
		while (!Q.empty()&&visit[Q.top().x])Q.pop();
		if (Q.empty())break;
		x=Q.top().x;Q.pop();printf("degree[x]=%d\n",degree[x]);
		d=1<<30;
		for (int p=e.son[x];p;p=e.next[p])
			if (!visit[e.link[p]]&&degree[e.link[p]]<d)
				d=degree[e.link[p]],y=e.link[p];
		del(x);
		if (y>=0)del(y),++ans;
		//printf("match %d %d\n",x,y);
	}
	printf("%d\n",ans);
	//system("pause");
	return 0;
}


