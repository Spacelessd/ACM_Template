#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
using namespace std;
#define NMax 10000
struct node{
	int key,mn,delta;
	int revmark;
	node *p,*l,*r;
	node(){}
};
struct DynamicTree{
	node *nodes;
	int N;
	static void ini_node(node *p){
		p->p=p->l=p->r=NULL;
		p->revmark=0;p->delta=0;p->mn=~0u>>2;p->key=~0u>>2;
	}
	static int isroot(node *p){return !p->p || (p->p->l!=p && p->p->r!=p);}
	DynamicTree(int n){
		N=n;
		nodes=new node[n];
		for (int i=0;i<n;i++)ini_node(nodes+i);
	}
	static void inc(node *p,int d){
		p->key+=d;p->mn+=d;p->delta+=d;
	}
	static void rev(node *p){
		swap(p->l,p->r);
		p->revmark^=1;
	}
	static void down(node *p){
		if (p->delta){
			if (p->l)inc(p->l,p->delta);
			if (p->r)inc(p->r,p->delta);
			p->delta=0;
		}
		if (p->revmark){
			if (p->l)rev(p->l);
			if (p->r)rev(p->r);
			p->revmark=0;
		}
	}
	static void update(node *p){
		p->mn=p->key;
		if (p->l && p->l->mn+p->delta<p->mn)p->mn=p->l->mn+p->delta;
		if (p->r && p->r->mn+p->delta<p->mn)p->mn=p->r->mn+p->delta;
	}
	static void zig(node *p){
		node *x=p->p,*y=x->p;
		p->p=y;x->p=p;
		if (y){
			if (x==y->l)y->l=p;
			else if (x==y->r)y->r=p;
		}
		x->l=p->r;if (x->l)x->l->p=x;
		p->r=x;
		update(x);
		update(p);
	}
	static void zag(node *p){
		node *x=p->p,*y=x->p;
		p->p=y;x->p=p;
		if (y){
			if (x==y->l)y->l=p;
			else if (x==y->r)y->r=p;
		}
		x->r=p->l;if (x->r)x->r->p=x;
		p->l=x;
		update(x);
		update(p);
	}
	static void Splay(node *p){
		static node *stack[NMax];
		int top=1;
		stack[0]=p;
		for (node *q=p;!isroot(q);)stack[top++]=(q=q->p);
		while (top)down(stack[--top]);
		while (!isroot(p)){
			node *q=p->p;
			if (isroot(q)){
				if (q->l==p)zig(p);
				else zag(p);
			}else{
				if (q==q->p->l){
					if (p==q->l){
						zig(q);zig(p);
					}else{
						zag(p);zig(p);
					}
				}else{
					if (p==q->r){
						zag(q);zag(p);
					}else{
						zig(p);zag(p);
					}
				}
			}
		}
	}
	static node* head(node *p){
		for (down(p);p->l;p=p->l)down(p);
		Splay(p);
		return p;
	}
	static node *tail(node *p){
		for (down(p);p->r;p=p->r)down(p);
		Splay(p);
		return p;
	}
	static node *prev(node *p){
		Splay(p);
		if (!p->l)return NULL;
		node *q=p->l;
		for (;q->r;q=q->r)down(q);
		Splay(q);
		return q;
	}
	static node *next(node *p){
		Splay(p);
		if (!p->r)return NULL;
		node *q=p->r;
		for (;q->l;q=q->l)down(q);
		Splay(q);
		return q;
	}
	static node *Expose(node *p){
		node *q;
		for (q=NULL;p;p=p->p){
			Splay(p);
			p->r=q;
			update(q=p);
		}
		return q;
	}
	node *getNode(int id){return id>=0&&id<N?nodes+id:NULL;}
	int getId(node *p){return p?p-nodes:-1;}
	static int AskMin(node *p){
		return Expose(p)->mn;
	}
	int AskMin(int id){return AskMin(getNode(id));}
	static void Increase(node *p,int d){
		inc(Expose(p),d);
	}
	void Increase(int id,int d){Increase(getNode(id),d);}
	static void Change(node *p,int a){
		Splay(p);
		p->key=a;
		update(p);
	}
	void Change(int id,int a){Change(getNode(id),a);}
	static void ChangeRoot(node *p){
		rev(Expose(p));
	}
	void ChangeRoot(int id){ChangeRoot(getNode(id));}
	static node *getParent(node *p){
		Splay(p);
		if (p->l)return prev(p);
		return p->p;
	}
	int getParent(int id){return getId(getParent(getNode(id)));}
	static node *getRoot(node *p){
		return head(Expose(p));
	}
	int getRoot(int id){return getId(getRoot(getNode(id)));}
	static void Merge(node *p,node *q){
		Splay(q);
		q->p=p;
	}
	void Merge(int p,int q){Merge(getNode(p),getNode(q));}
	static void Cut(node *p){
		Splay(p);
		if (p->l){
			p->l->p=p->p;
			p->p=p->l=NULL;
		}else p->p=NULL;
	}
	void Cut(int id){Cut(getNode(id));}
	static node *LCA(node *p,node *q){
		node *x=head(Expose(p));
		node *y=Expose(q),*z=head(y);
		if (x==z)return y;
		return NULL;
	}
	int LCA(int p,int q){return getId(LCA(getNode(p),getNode(q)));}
	int Query(node *p,node *q){
		node *x=getRoot(p),*y=Expose(q),*z=head(y);
		int Max1=max(y->r->m,y->key);
		y=Expose(p);
		int Max2=max(y->r->max,y->key);
		return max(Max1,Max2);
	}
};
#define maxn 50010
struct Edge{
	int link[maxn*2],next[maxn*2],cost[maxn*2],son[maxn],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
		}
}e;
struct Tree{
	int fa[maxn],dep[maxn],w[maxn];
	void clear(){}
	Tree(){clear();}
	void Build(int x,int y,int deep){
    dep[x]=deep;fa[x]=y;
    for (int i=e.son[x];i;i=e.next[i]){
        int j=e.link[i];
        if (j!=y)w[j]=e.cost[i],Build(j,x,deep+1);
    }
}
};
Tree c;
DynamicTree a(maxn);
int n,i,x,y,T,tmp;
char str[100];
int edgex[maxn*2],edgey[maxn*2];
void copy(){
	int i;
	for (i=1;i<=n;i++)
	{
        a.nodes[i].p=a.getNode(c.fa[i]);
        a.nodes[i].l=a.nodes[i].r=a.nodes[i].p=NULL;
        a.nodes[i].key=c.w[i];
        a.update(a.getNode(i));
    }
    a.nodes[1].p=NULL;
    //for (int i=1;i<=n;i++)a.nodes[i].num=i;
    //a.nodes[0].num=1234;
    //a.null->num=-1;
}
void init(){
     int x,y,z;
     //a.clear();
     e.clear();
     scanf("%d",&n);
     for (i=1;i<=n-1;i++){
         scanf("%d%d%d",&x,&y,&z),e.addedge(x,y,z),e.addedge(y,x,z),edgex[i]=x,edgey[i]=y;
     }
     c.Build(1,0,0);
     copy();
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	scanf("%d",&T);
	while (T--){
          init();
          while (1){
                scanf("%s",str);
                if (str[0]=='D')break;
                scanf("%d%d",&x,&y);
                if (str[1]=='H'){
                    if (c.dep[edgex[x]]>c.dep[edgey[x]])tmp=edgex[x];
                       else tmp=edgey[x];
                    a.Change(tmp,y);             
                    }
                if (str[1]=='U')printf("%d\n",a.Query(x,y));
                }
          }
	//system("pause");
	//for (;;);
	return 0;
}














