/*
ID: dd.ener1
PROG: ditch
LANG: C++
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=20010,OO=1000000000;
struct edge{
	int x,y;//两个顶点 
	int w;//容量 
	int f;
	edge *next,*back;
	edge(){}
	edge(int x,int y,int w,edge* next):x(x),y(y),w(w),f(0),next(next),back(0){}
	void* operator new(size_t, void* p){
		return p;
	}
}*E[maxn],*cur[maxn];

int H[maxn];//高度函数
int P[maxn];//preflow
int N,S,T;
void input(){
	int m;
	scanf("%d%d",&m,&N);
	memset(E,0,sizeof(E));
	edge* data=new edge[2*(N+m+10)];
	while(m--){
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		E[x]=new((void*)data++) edge(x,y,w,E[x]);
		E[y]=new((void*)data++) edge(y,x,0,E[y]);
		E[x]->back = E[y];
		E[y]->back = E[x];
	}
	S=1;
	T=N;
}
template <class T>
const T& min(const T& a,const T& b){
	return a<b?a:b;
}
int count[maxn*2];
void gap_heuristic(){
	memset(count,0,sizeof(count));
	for(int i=1;i<=N;++i)
		count[H[i]]++;
	int k;
	for(k=1;k<N;++k)
		if(count[k]==0)
			break;
	if(k==N)
		return;
	for(int i=1;i<=N;++i){
		if(i==S)
			continue;
		if(k<H[i]&&H[i]<=N)
			H[i]=N+1;
	}
}
void push(edge* e,int num=-1){
    printf("in%d\n",num);
	int u=e->x,v=e->y;
	int delta=min(P[u],e->w);
	e->w -= delta;
	e->back->w += delta;
	e->f += delta;
	e->back->f = -(e->f);
	P[u]-=delta;
	P[v]+=delta;
	printf("out%d\n",num);
}
void relabel(int u){
	int minlabel=OO;
	for(edge* e=E[u];e;e=e->next){
		if(e->w==0)continue;
		int v=e->y;
		if(H[v]<minlabel){
			minlabel=H[v];
			cur[u]=e;
		}
	}
	H[u]=minlabel+1;
	
	static int times=0;
	if(++times==N){
		times=0;
		gap_heuristic();
	}
}
void discharge(int u){
	while(P[u]>0){
		if(!cur[u]){
			relabel(u);
			cur[u]=E[u];
		}
		int v=cur[u]->y;
		if(cur[u]->w >0 && H[u]==H[v]+1)
			push(cur[u]);
		cur[u]=cur[u]->next;
	}
}
void init_label(){
	memset(H,-1,sizeof(H));
	H[S]=N;
	int queue[maxn],head=0,tail=0;
	queue[tail++]=S;
	for(;;){
		int v=queue[head++];
		if(head==tail)
			break;
		for(edge* e=E[v];e;e=e->next){
			if(e->w==0)continue;
			int y=e->y;
			if(H[y]==-1){
				H[y]=H[v]-1;
				queue[tail++]=y;
			}
		}
	}
}
void init_preflow(){
	init_label();
	memset(P,0,sizeof(P));
	P[S]=OO;
	for(edge* e=E[S];e!=0;e=e->next)
		push(e,1);                        //1
}
struct vertex{
	int x;
	vertex* next;
	vertex(int x,vertex* next):x(x),next(next){}
	vertex(){}
	void* operator new(size_t, void* p){
		return p;
	}
};
vertex* build_list(){
	vertex* data=new vertex[N-2];
	vertex* L=0;
	for(int i=N;i>=1;--i)
		if(i!=S&&i!=T)
			L=new((void*)data++) vertex(i,L);
	return L;
}
int maxflow(){
	memcpy(cur,E,sizeof(E));
	init_preflow();
	vertex* L=build_list();//list
	vertex *v=L,*pre=0;
	while(v){
		int old_height=H[v->x];
		discharge(v->x);
		if(H[v->x]>old_height){
			if(pre){
				pre->next = v->next;
				v->next = L;
				L = v;
			}
			else;//本来就在表头 
		}
		pre = v;
		v = v->next;
	}
	return P[T];
}
int main(){
	freopen("ditch6.in","r",stdin);
	//freopen("ditch.out","w",stdout);
	input();
	int res=maxflow();
	printf("%d\n",res);
	for(;;);
}
