#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
#define N 100005
struct DynamicTree{
	struct node{
		int key,size,max,rev,delta;
		node *l,*r,*p;
		void update(){
			size=l->size+r->size+1;
			max=key;
			if (l->max>max)max=l->max;
			if (r->max>max)max=r->max;
		}
	};
	node *a,*null;
	int max(int x,int y){return x>y?x:y;}
	int isroot(node *p){return p->p->l!=p&&p->p->r!=p;}
	void clear(){
		null=new node;null->l=null->r=null;
		null->size=0;null->delta=0;null->max=null->key=-oo;
	}
	void ini_node(node *p){
		p->l=p->r=p->p=null;
		p->rev=0;p->delta=0;p->max=-oo;
		p->size=1;p->key=-oo;
	}
	DynamicTree(int n=5){
		n+=5;a=new node[n];clear();
		for (int i=0;i<n;++i)ini_node(a+i);
	}
	void inc(node *p,int d){
		p->key+=d;p->max+=d;p->delta+=d;
	}
	void rev(node *p){
		node *tmp=p->l;p->l=p->r;p->r=tmp;
		p->rev^=1;
	}
	void down(node *p){
		if (p->delta){
			if (p->l!=null)inc(p->l,p->delta);
			if (p->r!=null)inc(p->r,p->delta);
			p->delta=0;
		}
		if (p->rev){
			rev(p->l);rev(p->r);
			p->rev=0;
		}
	}
	void zig(node *x){
		node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else if (z->r==y)z->r=x;
		x->p=z;y->p=x;y->l=x->r;x->r=y;
		y->l->p=y;y->update();
	}
	void zag(node *x){
		node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else if (z->r==y)z->r=x;
		x->p=z;y->p=x;y->r=x->l;x->l=y;
		y->r->p=y;y->update();
	}
	void splay(node *x){
		node *y,*z;
		static node* stack[N];int top=0;
		if (x==null) return;
		for (node *q=x;;q=q->p){stack[++top]=q;if (isroot(q))break;}
		while (top)down(stack[top--]);
		while (!isroot(x)){
			y=x->p;z=y->p;
			if (isroot(y))if (x==y->l)zig(x);else zag(x);
			else
				if (y==z->l)
					if (x==y->l)zig(y),zig(x);
					else zag(x),zig(x);
				else
					if (x==y->r)zag(y),zag(x);
					else zig(x),zag(x);
		}
		x->update();
	}
	node *head(node *p){
		for(down(p);p->l!=null;down(p))p=p->l;
		splay(p);return p;
	}
	node *tail(node *p){
		for(down(p);p->r!=null;down(p))p=p->r;
		splay(p);return p;
	}
	node *prev(node *p){
		if (p->l==null)return null;
		node *q=p->l;
		for (down(q);q->r!=null;down(q))q=q->r;
		splay(q);return q;
	}
	node *next(node *p){
		if (p->r==null)return null;
		node *q=p->r;
		for (down(q);q->l!=null;down(q))q=q->l;
		splay(q);return q;
	}
	node *Expose(node *p){
		node *q=null;
		for (;p!=null;p=p->p){
			splay(p);p->r=q;(q=p)->update();
		}
		return q;
	}
	node *getnode(int x){return a+x;}
	int getid(node *p){return p-a;}
	int Depth(node *p){Expose(p);splay(p);return p->l->size+1;}
	int Maxcost(node *p){return Expose(p)->max;}
	void Update(node *p,int d){inc(Expose(p),d);}
	void Change(node *p,int key){
		splay(p);p->key=key;p->update();
	}
	void Changeroot(node *p){rev(Expose(p));}
	node *Parent(node *p){
		splay(p);if (p->l!=null)return prev(p);
		else return p->p;
	}
	node *Root(node *p){return head(Expose(p));}
	void Cut(node *p){
		splay(p);p->l->p=p->p;p->l=null;
		p->p=null;p->update();
	}
	void Changefa(node *x,node *y){Cut(x);x->p=y;}
	void link(node *x,node *y){Changeroot(x);Changefa(x,y);}
	void cut(node *x,node *y){Changeroot(x);Cut(y);}
	node *LCA(node *p,node *q){
		node *x=Root(p),*y=Expose(q),*z=head(y);
		if (x==z)return y;
		else return null;
	}
	int Query(node *p,node *q){
		int Max;Expose(p);
		node *y=Expose(q);
		Max=y->r->max;
		if (p!=y)splay(p),Max=max(Max,p->max);
		return Max;
	}
	/*void print(){
		for (int i=1;i<=n;i++){
			node *tmp=getnode(i);
			printf("node%d: %d %d %d %d %d\n",i,tmp->l->num,tmp->r->num,tmp->p->num,tmp->key,tmp->max);
		}
	}*/
	int Depth(int x){return Depth(getnode(x));}
	int Maxcost(int x){return Maxcost(getnode(x));}
	void Update(int x,int d){Update(getnode(x),d);}
	void Change(int x,int key){Change(getnode(x),key);}
	void Changeroot(int x){Changeroot(getnode(x));}
	int Parent(int x){return getid(Parent(getnode(x)));}
	int Root(int x){return getid(Root(getnode(x)));}
	void Cut(int x){Cut(getnode(x));}
	void Changefa(int x,int y){Changefa(getnode(x),getnode(y));}
	void link(int x,int y){link(getnode(x),getnode(y));}
	void cut(int x,int y){cut(getnode(x),getnode(y));}
	int LCA(int p,int q){return getid(LCA(getnode(p),getnode(q)));}
	int Query(int p,int q){return Query(getnode(p),getnode(q));}
};
DynamicTree a(N);
struct Edge{
	int link[N*2],next[N*2],cost[N*2],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
};
Edge e;
struct Tree{
	int fa[N],dep[N],w[N];
	void Build(int x,int y,int deep){
		dep[x]=deep;fa[x]=y;
		for (int i=e.son[x];i;i=e.next[i]){
			int j=e.link[i];
			if (j!=y)w[j]=e.cost[i],Build(j,x,deep+1);
		}
	}
};
Tree c;
int n;int edgex[N*2],edgey[N*2];
char str[105];
void copy(){
	for (int i=1;i<=n;++i){
		a.a[i].p=a.getnode(c.fa[i]);
		a.a[i].l=a.a[i].r=a.null;
		a.a[i].key=c.w[i];
		a.getnode(i)->update();
	}
	a.a[1].p=a.null;
	/*for (int i=1;i<=n;i++)a.a[i].num=i;
	a.a[0].num=1234;
	a.null->num=-1;*/
}
void init(){
	int x,y,z;
	a.clear();e.clear();
	scanf("%d",&n);
	for (int i=1;i<=n-1;++i)
		scanf("%d%d%d",&x,&y,&z),e.addedge(x,y,z),e.addedge(y,x,z),edgex[i]=x,edgey[i]=y;
	c.Build(1,0,0);
	copy();
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int T,x,y;scanf("%d",&T);
	while (T--){
		init();int tmp;
		while (1){
			scanf("%s",str);
			if (str[0]=='D')break;
			scanf("%d%d",&x,&y);
			if (str[1]=='H'){
				if (c.dep[edgex[x]]>c.dep[edgey[x]])tmp=edgex[x];
					else tmp=edgey[x];
				a.Change(tmp,y);
			}
			if (str[1]=='U'){
				printf("%d\n",a.Query(x,y));
			}
		}
	}
	system("pause");for (;;);
	return 0;
}


