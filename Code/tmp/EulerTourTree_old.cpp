#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define ll long long
#define N 100005
struct LinkCutTree{
	struct node{
		int rev;
		node *l,*r,*p;
		void update(){}
	};
	node *a,*null;
	int isroot(node *p){return p->p->l!=p&&p->p->r!=p;}
	void ini_node(node *p){
		p->l=p->r=p->p=null;
		p->rev=0;
	}
	LinkCutTree(int n=5){
		n+=5;a=new node[n];null=new node;ini_node(null);
		for (int i=0;i<n;++i)ini_node(a+i);
	}
	void rev(node *p){
		node *tmp=p->l;p->l=p->r;p->r=tmp;
		p->rev^=1;
	}
	void down(node *p){
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
			if (isroot(y)){if (x==y->l)zig(x);else zag(x);}
			else
				if (y==z->l)
					if (x==y->l){zig(y);zig(x);}
					else{zag(x);zig(x);}
				else
					if (x==y->r){zag(y);zag(x);}
					else{zig(x);zag(x);}
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
	void Changeroot(int x){Changeroot(getnode(x));}
	int Parent(int x){return getid(Parent(getnode(x)));}
	int Root(int x){return getid(Root(getnode(x)));}
	void Cut(int x){Cut(getnode(x));}
	void Changefa(int x,int y){Changefa(getnode(x),getnode(y));}
	void link(int x,int y){link(getnode(x),getnode(y));}
	void cut(int x,int y){cut(getnode(x),getnode(y));}
	int LCA(int p,int q){return getid(LCA(getnode(p),getnode(q)));}
};
LinkCutTree LC(N);
#include<map>
#include<algorithm>
using namespace std;
struct EulerTourTree{
	struct node{
		ll delta,sum,key;
		int x,y,exist,cnt,id;
		node *l,*r,*p;
		void update(){
			cnt=l->cnt+r->cnt+exist;
			sum=l->sum+r->sum+key;
		}
	};
	node *a,*null;
	LinkCutTree &LC;
	map<int,node*> *M;
	node **stack;int stack1;
	void ini_node(node *p){
		p->l=p->r=p->p=null;
		p->delta=0;p->exist=0;p->cnt=0;
		p->key=0;p->sum=0;
	}
	node *newnode(){
		if (stack1<0)printf("error:out of memory!\n");
		ini_node(stack[stack1]);
		return stack[stack1--];
	}
	void delnode(node *x){stack[++stack1]=x;}
	node *getedge(int x,int y){
		map<int,node*>::iterator ans=M[x].find(y);
		if (ans!=M[x].end())return ans->second;
		else return null;
	}
	EulerTourTree(LinkCutTree &LCtree,int n=5):LC(LCtree){
		n+=5;n*=3;stack1=-1;stack=new node*[n];
		M=new map<int,node*>[n];
		a=new node[n];null=new node;ini_node(null);
		for (int i=n-1;i>=0;--i)stack[++stack1]=a+i;
	}
	int isroot(node *p){return p->p->l!=p&&p->p->r!=p;}
	void inc(node *p,ll d){
		if (p->exist)p->key+=d;
		p->sum+=p->cnt*d;
		p->delta+=d;
	}
	void down(node *p){
		if (p->delta){
			if (p->l!=null)inc(p->l,p->delta);
			if (p->r!=null)inc(p->r,p->delta);
			p->delta=0;
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
		static node* stack[N*3];int top=0;
		if (x==null) return;
		for (node *q=x;;q=q->p){stack[++top]=q;if (isroot(q))break;}
		while (top)down(stack[top--]);
		while (!isroot(x)){
			y=x->p;z=y->p;
			if (isroot(y)){if (x==y->l)zig(x);else zag(x);}
			else
				if (y==z->l)
					if (x==y->l){zig(y);zig(x);}
					else{zag(x);zig(x);}
				else
					if (x==y->r){zag(y);zag(x);}
					else{zig(x);zag(x);}
		}
		x->update();
	}
	node *head(node *p){
		for(;p->l!=null;p=p->l);
		splay(p);return p;
	}
	node *tail(node *p){
		for(;p->r!=null;p=p->r);
		splay(p);return p;
	}
	node *prev(node *p){
		if (p->l==null)return null;
		node *q=p->l;
		for (;q->r!=null;q=q->r);
		splay(q);return q;
	}
	node *next(node *p){
		if (p->r==null)return null;
		node *q=p->r;
		for (;q->l!=null;q=q->l);
		splay(q);return q;
	}
	node* getroot(node *x){
		for (;!isroot(x);x=x->p);return x;
	}
	int get_l_r(node *x,node *y){
		splay(y);for (;x->p!=y;x=x->p);
		if (x==y->l)return 0;else return 1;
	}
	node* merge(node *x,node *y){
		if (y==null){splay(x);return x;}
		if (x==null){splay(y);return y;}
		splay(x);x=tail(x);
		splay(y);y=head(y);
		x->r=y;y->p=x;x->update();
		return x;
	}
	pair<node*,node*> split_l(node *x){
		node *l,*r;
		splay(x);l=x;r=x->r;
		x->r->p=null;x->r=null;
		x->update();
		return make_pair(l,r);
	}
	pair<node*,node*> split_r(node *x){
		node *l,*r;
		splay(x);r=x;l=x->l;
		x->l->p=null;x->l=null;
		x->update();
		return make_pair(l,r);
	}
	void link(int u,int v){
		if (getedge(u,v)!=null)return;
		LC.link(u,v);
		node *u_v=newnode(),*v_u=newnode();
		u_v->x=u;u_v->y=v;v_u->x=v;v_u->y=u;
		M[u].insert(make_pair(v,u_v));M[v].insert(make_pair(u,v_u));
		node *T1_1,*T1_2,*T2_1,*T2_2;
		pair<node*,node*> tmp;
		tmp=split_l(getedge(u,u));T1_1=tmp.first;T1_2=tmp.second;
		tmp=split_l(getedge(v,v));T2_1=tmp.first;T2_2=tmp.second;
		node *x=null;
		x=merge(x,T1_2);x=merge(x,T1_1);x=merge(x,u_v);
		x=merge(x,T2_2);x=merge(x,T2_1);x=merge(x,v_u);
	}
	void cut(int u,int v){
		node *u_v=getedge(u,v),*v_u=getedge(v,u);
		if (get_l_r(u_v,v_u)){swap(u,v);swap(u_v,v_u);}
		node *T1,*T2,*T3;
		T1=split_r(u_v).first;split_l(u_v);
		T2=split_r(v_u).first;T3=split_l(v_u).second;
		merge(T3,T1);
		LC.cut(u,v);delnode(u_v);delnode(v_u);
		M[u].erase(v);M[v].erase(u);
	}
	void add(int x,ll y){
		int fa=LC.Parent(x);node *now;
		if (fa==LC.getid(LC.null)){
			now=getedge(x,x);
			splay(now);inc(now,y);return;
		}
		else {
			node *fa_x=getedge(fa,x),*x_fa=getedge(x,fa);
			int l_r=get_l_r(fa_x,x_fa);
			if (l_r)swap(x_fa,fa_x);
			node *T1,*T2,*T3;
			T1=split_r(fa_x).first;split_l(fa_x);
			T2=split_r(x_fa).first;T3=split_l(x_fa).second;
			T1=merge(T3,T1);
			if (!l_r)inc(T2,y);else inc(T1,y);
			T1=merge(x_fa,T1);T1=merge(T1,fa_x);
			merge(T2,T1);
		}
	}
	ll Query(int x){
		int fa=LC.Parent(x);node *now;
		if (fa==LC.getid(LC.null)){
			now=getedge(x,x);
			splay(now);return now->sum;
		}
		else {
			node *fa_x=getedge(fa,x),*x_fa=getedge(x,fa);
			int l_r=get_l_r(fa_x,x_fa);ll res;
			if (l_r)swap(x_fa,fa_x);
			node *T1,*T2,*T3;
			T1=split_r(fa_x).first;split_l(fa_x);
			T2=split_r(x_fa).first;T3=split_l(x_fa).second;
			T1=merge(T3,T1);
			if (!l_r)res=T2->sum;else res=T1->sum;
			T1=merge(x_fa,T1);T1=merge(T1,fa_x);
			merge(T2,T1);
			return res;
		}
	}
	void Changeroot(int x){LC.Changeroot(x);}
	int LCA(int p,int q){return LC.LCA(p,q);}
};
EulerTourTree ET(LC,N);
struct Edge{
	int link[N*2],next[N*2],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
	}
}e;
struct Tree{
	int fa[N],edgex[N*3],edgey[N*3],len;
	Edge &e;
	Tree(Edge &edge):e(edge){len=0;}
	void Build(int x,int y){
		fa[x]=y;
		for (int i=e.son[x];i;i=e.next[i]){
			int j=e.link[i];
			if (j!=y)Build(j,x);
		}
	}
	void dfs(int x,int y){
		if (y!=0){++len;edgex[len]=y;edgey[len]=x;}
		++len;edgex[len]=x;edgey[len]=x;
		for (int i=e.son[x];i;i=e.next[i]){
			int j=e.link[i];
			if (j!=y)dfs(j,x);
		}
		if (y!=0){++len;edgex[len]=x;edgey[len]=y;}
	}
};
Tree c(e);
int w[N],n,m;
void copy(EulerTourTree &ET){
	for (int i=1;i<=n;++i){
		ET.LC.a[i].p=ET.LC.getnode(c.fa[i]);
		ET.LC.a[i].l=ET.LC.a[i].r=ET.LC.null;
		ET.LC.getnode(i)->update();
	}
	ET.LC.getnode(1)->p=ET.LC.null;
	static EulerTourTree::node *x[N*3];
	for (int i=1;i<=c.len;++i){
		x[i]=ET.newnode();x[i]->x=c.edgex[i];x[i]->y=c.edgey[i];
		ET.M[c.edgex[i]].insert(make_pair(c.edgey[i],x[i]));
		if (c.edgex[i]==c.edgey[i]){
			x[i]->delta=0;x[i]->exist=1;x[i]->key=w[c.edgex[i]];
			x[i]->update();
		}
		else {
			x[i]->delta=0;x[i]->exist=0;x[i]->key=0;
			x[i]->update();
		}
		if (i>1)ET.merge(x[i-1],x[i]);
	}
	for (int i=0;i<c.len;++i)ET.a[i].id=i;
	ET.null->id=-1;
	ET.null->sum=0;
}
void init(){
	int x,y;e.clear();
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n-1;++i)
		scanf("%d%d",&x,&y),e.addedge(x,y),e.addedge(y,x);
	for (int i=1;i<=n;++i)scanf("%d",&w[i]);
	c.Build(1,0);c.dfs(1,0);
	copy(ET);
}
/*void print(){
	printf("print start:----------------\n");
	for (int i=0;i<c.len;++i){
		printf("node%d\n",i);
		printf("l=%d r=%d p=%d %d->%d\n",ET.a[i].l->id,ET.a[i].r->id,ET.a[i].p->id,ET.a[i].x,ET.a[i].y);
		printf("sum=%I64d key=%I64d delta=%I64d cnt=%d exist=%d\n",ET.a[i].sum,ET.a[i].key,ET.a[i].delta,ET.a[i].cnt,ET.a[i].exist);
	}
	printf("print end\n");
}*/
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	init();
	while (m--){
		int x,y;char str[105];
		scanf("%s",str);
		if (str[0]=='C'){
			scanf("%d",&x);
			ET.Changeroot(x);
		}
		if (str[0]=='A'){
			scanf("%d%d",&x,&y);
			ET.add(x,y);
		}
		if (str[0]=='Q'){
			scanf("%d",&x);
			printf("%I64d\n",ET.Query(x));
		}
	}
	system("pause");for (;;);
	return 0;
}


