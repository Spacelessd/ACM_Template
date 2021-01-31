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
	void* operator new(size_t, void *p){
		return p;
	}
}*E[maxn];
int D[maxn];//距离标号，即点到汇点的最少的弧数
int N,S,T;

void init_distance_label(){//就是从汇点开始，只走容量为0的边的一次广搜 
	int queue[maxn],head=0,tail=0;
	queue[tail++]=S;
	memset(D,-1,sizeof(D));
	D[T]=0;
	for(;;){
		int v=queue[head++];
		for(edge* e=E[v];e;e=e->next){
			if(e->w!=0)continue;
			int y=e->y;
			if(D[y]==-1){
				D[y]=D[v]+1;
				queue[tail++]=y;
			}
		}
		if(head==tail)
			break;
	}
}
int maxflow(){
	int res=0;
	init_distance_label();
	edge* path[maxn];
	edge* current[maxn];
	memcpy(current,E,sizeof(E));
	int path_n=0;
	int i=S;
	for(;;){
		if(i==T){
			int min=OO,mink;
			for(int k=0;k<path_n;++k){
				if(path[k]->w < min){
					min=path[k]->w;
					mink=k;
				}
			}
			res+=min;
			for(int k=0;k<path_n;++k){
				path[k]->w -= min;
				path[k]->back->w += min;
				path[k]->f += min;
				path[k]->back->f = -(path[k]->f);
			}
			path_n=mink;
			i=path[path_n]->x;
		}
		edge* e;
		for(e=current[i];e;e=e->next){
			if(e->w==0)continue;
			int j=e->y;
			if(D[i]==D[j]+1)
				break;
		}
		if(e){//e就是从i出发的允许弧
			current[i]=e;//前面的都不是允许弧，所以下次从这里开始找就可以 
			path[path_n++]=e;
			i=e->y;
		}
		else{//从i出发没有允许弧，需要修改标号 
			int minlabel=N;
			for(edge* e=E[i];e;e=e->next){
				if(e->w==0)continue;
				int j=e->y;
				if(D[j]<minlabel){
					minlabel=D[j];
					current[i]=e;//最小标号的边就是新的允许弧 
				}
			}
			D[i]=minlabel+1;
			if(i!=S){//由于i的标号被改变，路径中到i的那条弧肯定已经不是允许弧，所以要回退一步
				--path_n;
				i=path[path_n]->x;
			}
			else if(D[i]>N)//此时已经没有从源点到汇点的路了 
				break;
		}
	}
	return res;
}
void input(){
	int m;
	scanf("%d%d",&m,&N);
	memset(E,0,sizeof(E));
	edge* data=new edge[2*m];
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
int main(){
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
	input();
	int res=maxflow();
	printf("%d\n",res);
}
