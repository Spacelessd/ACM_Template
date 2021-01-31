#include <cstdio> 
#include <bits/stl_pair.h> 
#include <queue> 
#include <deque> 
#include <algorithm> 
using namespace std; 
int ran(){ 
	static int x=222313214; 
	x+=(x<<2)+1; 
	return x; 
} 
struct node{ 
	int w,sz; 
	char k; 
	node *l,*r; 
	static node* getnew(node *p=NULL){ 
		static node * list=NULL; 
		if (p){ 
			p->w=ran(); 
			p->r=list;list=p; 
			return NULL; 
		} 
		if (!list){ 
			node *p=new node[10000]; 
			for (int i=0;i<10000;i++){ 
				p[i].r=list;list=p+i; 
				p[i].w=ran(); 
			} 
		} 
		node *q=list; 
		list=list->r; 
		q->l=NULL;q->r=NULL;q->sz=1; 
		return q; 
	} 
}; 
#define SIZE(_) ((_)?(_)->sz:0) 
int M,curid; 
queue<pair<int,node*> > Literbox; 
deque<node*> Roots; 
void giveback(node *p){ 
	Literbox.push(make_pair(curid,p)); 
} 
void dfs(node *p,int a,int b){ 
	if (p){ 
		int u=SIZE(p->l); 
		if (u>a)dfs(p->l,a,min(b,u-1)); 
		if (a<=u && u<=b)putchar(p->k); 
		if (b>u)dfs(p->r,max(a-u-1,0),b-u-1); 
	} 
} 
node * combine(node *p,node *q){ 
	if (!p || !q)return p?p:q; 
	if (p->w<q->w){ 
		node *a=node::getnew(); 
		a->k=p->k; 
		a->w=p->w; 
		a->sz=p->sz+q->sz; 
		a->l=p->l; 
		a->r=combine(p->r,q); 
		giveback(p); 
		return a; 
	}else{ 
		node *a=node::getnew(); 
		a->k=q->k; 
		a->w=q->w; 
		a->sz=p->sz+q->sz; 
		a->r=q->r; 
		a->l=combine(p,q->l); 
		giveback(q); 
		return a; 
	} 
} 
void cutdown(node *p,node *&x,node *&y,int a){ 
	if (a==0)x=NULL,y=p; 
	else if (a==SIZE(p)){ 
		x=p;y=NULL; 
	}else{ 
		if (SIZE(p->l)+1<=a){ 
			x=node::getnew(); 
			x->k=p->k;x->w=p->w; 
			x->sz=a; 
			x->l=p->l; 
			cutdown(p->r,x->r,y,a-SIZE(p->l)-1); 
			giveback(p); 
		}else{ 
			y=node::getnew(); 
			y->k=p->k;y->w=p->w; 
			y->sz=p->sz-a; 
			y->r=p->r; 
			cutdown(p->l,x,y->l,a); 
			giveback(p); 
		} 
	} 
} 
void treeadd(node *&p,node *q){ 
	if (!p){ 
		p=q; 
	}else{ 
		if (p->w<q->w){ 
			treeadd(p->r,q); 
			p->sz++; 
		}else{ 
			q->l=p;q->sz=p->sz+1; 
			p=q; 
		} 
	} 
} 
void Insert(int i,char a){ 
	node *p=node::getnew(); 
	p->k=a; 
	node *x,*y; 
	cutdown(Roots.back(),x,y,i); 
	x=combine(x,p);x=combine(x,y); 
	Roots.push_back(x); 
	curid++; 
} 
void Delete(int i){ 
	node *x,*y,*z; 
	cutdown(Roots.back(),x,y,i); 
	cutdown(y,y,z,1); 
	giveback(y); 
	x=combine(x,z); 
	Roots.push_back(x); 
	curid++; 
} 
void Revolve(int a,int b,int c){ 
	node *p,*q,*r,*s; 
	cutdown(Roots.back(),p,q,a); 
	cutdown(q,q,r,b-a+1); 
	cutdown(r,r,s,c-b); 
	p=combine(p,r); 
	p=combine(p,q); 
	p=combine(p,s); 
	Roots.push_back(p); 
	curid++; 
} 
void Print(int a,int x,int y){ 
	node *p=Roots.at(Roots.size()-1-a); 
	dfs(p,x,y); 
	puts(""); 
} 
void readstr(vector<char> &a){ 
	char c; 
	while (c=getchar(),c==10 || c==13 || c==' '); 
	while (c!=10 && c!=13){ 
		a.push_back(c); 
		c=getchar(); 
	} 
} 
int main() 
{ 
	scanf("%d",&M); 
	vector<char> chs; 
	readstr(chs); 
	node *r=NULL; 
	for (int i=0;i<(int)chs.size();i++){ 
		node *p=node::getnew(); 
		p->k=chs[i]; 
		treeadd(r,p); 
	} 
	Roots.push_back(r); 
	curid=0; 
	char cmd[10]; 
	while (scanf("%s",cmd)!=EOF){ 
		if (cmd[0]=='I'){ 
			int x; 
			scanf("%d",&x); 
			scanf("%s",cmd); 
			Insert(x,cmd[0]); 
		}else if (cmd[0]=='D'){ 
			int x; 
			scanf("%d",&x); 
			Delete(x-1); 
		}else if (cmd[0]=='P'){ 
			int x,y,z; 
			scanf("%d%d%d",&x,&y,&z); 
			Print(x,y-1,z-1); 
		}else if (cmd[0]=='C'){ 
			int x,y,z; 
			scanf("%d%d%d",&x,&y,&z); 
			Revolve(x-1,y-1,z-1); 
		} 
		while (!Literbox.empty() && Literbox.front().first<curid-M){ 
			node::getnew(Literbox.front().second); 
			Literbox.pop(); 
		} 
		while ((int)Roots.size()>M)Roots.pop_front(); 
	} 
	return 0; 
} 


