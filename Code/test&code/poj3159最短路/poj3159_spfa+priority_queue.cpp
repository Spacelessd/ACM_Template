#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
struct Edge{
	#define Mx 500005
	int link[Mx],cost[Mx],next[Mx],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	Edge(){clear();}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
};
Edge e;
int n,m,S,T;
int d[N],inq[N],a[N],pos[N],len;
inline void swap(int x,int y){
	int tmp=a[x];a[x]=a[y];a[y]=tmp;pos[a[x]]=x;pos[a[y]]=y;
}
inline void up(int x){
	int i=x;
	while (i>1&&d[a[i]]<d[a[i>>1]]){
		swap(i,i>>1);i>>=1;
	}
}
inline void down(int x){
	int i=x,j;
	while (i<<1<=len){
		j=i; if (d[a[i<<1]]<d[a[i]])j=i<<1;
		if ((i<<1)+1<=len&&d[a[(i<<1)+1]]<d[a[j]])j=(i<<1)+1;
		if (j==i)break;
		swap(i,j); i=j;
	}
}
inline void insert(int x){a[++len]=x;pos[x]=len;up(len);}
inline bool empty(){return len==0;}
inline int top(){return a[1];}
inline void pop(){a[1]=a[len--];pos[a[1]]=1;down(1);}
void spfa(int S,Edge &e,int d[]){
	for (int i=1;i<=n;++i)d[i]=1<<29;
	for (int i=1;i<=n;++i)inq[i]=0;
	d[S]=0;len=0;insert(S);inq[S]=1;
	while (!empty()){
		int i=top();pop();inq[i]=0;
		for (int p=e.son[i];p;p=e.next[p]){
			int j=e.link[p];
			if (d[i]+e.cost[p]<d[j]){
				d[j]=d[i]+e.cost[p];
				if (!inq[j])insert(j),inq[j]=1;else up(pos[j]);
			}
		}
	}
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int x,y,z;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i)
		scanf("%d%d%d",&x,&y,&z),e.addedge(x,y,z);
	//scanf("%d%d",&S,&T);
	S=1;T=n;
	spfa(S,e,d);
	printf("%d\n",d[T]);
	//system("pause");for (;;);
	return 0;
}


