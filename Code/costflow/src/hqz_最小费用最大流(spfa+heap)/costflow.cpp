#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 20005
#define M 1000005
#define oo (1<<29)
int son[N],d[N],pre[N],inq[N],a[N],pos[N],len;
int link[M],st[M],next[M],cap[M],opp[M],cost[M];
int n,m,S,T,ll,maxflow,mincost;
void addedge(int x,int y,int z,int c){
	link[++ll]=y;st[ll]=x;next[ll]=son[x];son[x]=ll;cap[ll]=z;cost[ll]=c;opp[ll]=ll+1;
	link[++ll]=x;st[ll]=y;next[ll]=son[y];son[y]=ll;cap[ll]=0;cost[ll]=-c;opp[ll]=ll-1;
}
inline void swap(int x,int y){
	int tmp=a[x];a[x]=a[y];a[y]=tmp;pos[a[x]]=x;pos[a[y]]=y;
}
inline void up(int x){
	while (x>1&&d[a[x]]<d[a[x>>1]]){
		swap(x,x>>1);x>>=1;
	}
}
inline void down(int x){
	int i=x,j;
	while (i<<1<=len){
		j=i; if (d[a[i<<1]]<d[a[i]])j=i<<1;
		if (i<<1<len&&d[a[(i<<1)+1]]<d[a[j]])j=(i<<1)+1;
		if (j==i)return;
		swap(i,j); i=j;
	}
}
inline void insert(int x){a[++len]=x;pos[x]=len;up(len);}
inline bool empty(){return len==0;}
inline int top(){return a[1];}
inline void pop(){a[1]=a[len--];pos[a[1]]=1;down(1);}
int spfa(int S){
	for (int i=0;i<=n;++i)d[i]=1<<29;
	for (int i=0;i<=n;++i)inq[i]=0;
	d[S]=0;len=0;insert(S);inq[S]=1;
	while (!empty()){
		int i=top();pop();inq[i]=0;
		for (int p=son[i];p!=-1;p=next[p]){
			int j=link[p];
			if (d[i]+cost[p]<d[j]&&cap[p]){
				d[j]=d[i]+cost[p];pre[j]=p;
				if (!inq[j])insert(j),inq[j]=1;else up(pos[j]);
			}
		}
	}
	return d[T]<oo?1:0;
}
void update(){
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
int main()
{
	freopen("costflow.in","r",stdin);
	freopen("costflow.out","w",stdout);
	int nn,x,y,z,w;ll=0;scanf("%d%d",&nn,&m);
	n=nn;S=1;T=n;memset(son,-1,sizeof(int)*(n+1));
	for (int i=1;i<=m;++i){
		scanf("%d%d%d%d",&x,&y,&z,&w);
		addedge(x,y,z,w);
	}
	maxflow=mincost=0;while (spfa(S))update();
	//printf("%d\n",maxflow);
	printf("%d\n",mincost);
	//system("pause");for(;;);
	return 0;
}


