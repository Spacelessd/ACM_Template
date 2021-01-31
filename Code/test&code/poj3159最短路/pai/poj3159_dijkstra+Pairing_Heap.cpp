#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<queue>
using namespace std;
#define N 500005
struct Edge{
	#define Mx 2000005
	int link[Mx],cost[Mx],next[Mx],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	Edge(){clear();}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
};
Edge e;
int cnt[N],n,m,S,T;
struct Node{
	int d,x;
	Node(){}
	Node(int _d,int _x){d=_d;x=_x;}
	friend bool operator >(Node x,Node y){return x.d>y.d;}
};
template <class T>
struct Pairing_Heap{
	#undef N
	#define N 1000005
	struct node{
		node *l,*r,*pre;
		T key;
	};
	node tree[N],*tmp[N],*Null;
	node *root;int len;
	void clear(){
		len=0;tmp[0]=root=Null=new node;
		Null->key=Node((1<<30),-1);Null->l=Null->r=Null->pre=Null;
	}
	Pairing_Heap(){clear();}
	node *Newnode(T key){
		node *p=tree+(++len);
		p->key=key;p->l=p->r=p->pre=Null;
		return p;
	}
	node *link(node *a,node *b){
		if (a->key>b->key) {node *tmp=a;a=b;b=tmp;}
		if (b==Null)return a;
		b->r=a->l;a->l->pre=b;
		a->l=b;b->pre=a;
		return a;
	}
	node *combine(node *x){
		int total=0,i;node *y,*z;
		for (x->pre=Null;x!=Null;x=z){
			y=x->r,z=y->r;
			x->r=y->r=y->pre=z->pre=Null;
			tmp[++total]=link(x,y);
		}
		for (x=tmp[total],i=total-1;i>0;--i)x=link(x,tmp[i]);
		return x;
	}
	void insert(node *x){root=link(x,root);}
	node *pop(){
		node *tmp=root;
		root=combine(root->l);
		return tmp;
	}
	void decreasekey(node *x,int key){
		x->key=key;
		if (x!=root){
			x->r->pre=x->pre;
			if (x->pre->l!=x)x->pre->r=x->r;
				else x->pre->l=x->r;
			x->r=x->pre=Null;
			root=link(x,root);
		}
	}
	void insert(T key){node *x=Newnode(key);insert(x);}
	void del(node *x){decreasekey(x,-2147483647);pop();}
	void merge(Pairing_Heap *x){root=link(root,x->root);}
	T top(){return root->key;}
	bool empty(){return root==Null;}
	#undef N
};
Pairing_Heap<Node> Q;
int dijkstra(int S,int T,Edge &e){
	Q.insert(Node(0,S));
	while (!Q.empty()){
		int d=Q.top().d,x=Q.top().x;cnt[x]=1;
		if (x==T)return d;
		for (int p=e.son[x];p;p=e.next[p]){
			int v=e.link[p];
			Q.insert(Node(d+e.cost[p],v));
		}
		while (cnt[Q.top().x]&&!Q.empty())Q.pop();
	}
	return -1;
}
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	int x,y,z;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i)
		scanf("%d%d%d",&x,&y,&z),e.addedge(x,y,z);
	//scanf("%d%d",&S,&T);
	S=1;T=n;
	printf("%d\n",dijkstra(S,T,e));
	/*&Q.insert(Node(7,-5));
	Q.insert(Node(1,-5));
	Q.insert(Node(9,3));
	Q.insert(Node(-4,-6));
	/*for (int i=1;i<=10;++i)Q.insert(Node(rand()%10,rand()%10));
	for (int i=1;i<=10;++i){
		printf("%d %d\n",Q.top().d,Q.top().x);
		Q.pop();
		printf("empty%d\n",Q.empty());
	}*/
	//system("pause");
	return 0;
}


