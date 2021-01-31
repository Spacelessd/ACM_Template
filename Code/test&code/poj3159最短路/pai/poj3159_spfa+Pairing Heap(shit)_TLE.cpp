#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<queue>
using namespace std;
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
int d[N],inq[N];
struct Pairing_Heap{
	#define N 1000005
	struct node{
		node *l,*r,*pre;
		int key;
	};
	node tree[N],*tmp[N],*Null;
	node *root;int len;
	void clear(){
		len=0;tmp[0]=root=Null=new node;
		Null->key=1<<30;Null->l=Null->r=Null->pre=Null;
	}
	Pairing_Heap(){clear();}
	node *Newnode(int key){
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
	void insert(int key){node *x=Newnode(key);insert(x);}
	void del(node *x){decreasekey(x,-2147483647);pop();}
	void merge(Pairing_Heap *x){root=link(root,x->root);}
	int top(){return root->key;}
	bool empty(){return root==Null;}
	#undef N
};
Pairing_Heap q;
void spfa(int S,Edge &e,int d[]){
	for (int i=1;i<=n;++i)d[i]=1<<29;
	for (int i=1;i<=n;++i)inq[i]=0;
	d[S]=0;q.insert(S);inq[S]=1;
	while (!q.empty()){
		int i=q.top();q.pop();inq[i]=0;
		//printf("%d\n",i);
		for (int p=e.son[i];p;p=e.next[p]){
			int j=e.link[p];
			if (d[i]+e.cost[p]<d[j]){
				d[j]=d[i]+e.cost[p];
				if (!inq[j])q.insert(j),inq[j]=1;
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
	//system("pause");
	return 0;
}


