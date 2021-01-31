#include<cstdio>
#include<algorithm>
#define NMax 30000
#define MOD 10007
using namespace std;
int Inv[MOD];
struct node{
	int k,b;
	int sk,sb;
	node *f,*l,*r,*spf;
	void update(){
		if (l){
			sb=(k*l->sb+b)%MOD;
			sk=k*l->sk%MOD;
		}else sb=b,sk=k;
		if (r){
			sb=(r->sk*sb+r->sb)%MOD;
			sk=sk*r->sk%MOD;
		}
	}
}nodes[NMax];
int N,uf[NMax];
int uffind(int a){
	int t=a;
	while (uf[a]!=-1)a=uf[a];
	while (t!=a){
		int b=uf[t];
		uf[t]=a;
		t=b;
	}
	return a;
}
void zig(node *p){
	node *q=p->f,*y=q->f;
	if ((q->l=p->r))q->l->f=q;
	p->r=q;q->f=p;
	p->f=y;
	if (y){
		if (y->l==q)y->l=p;
		else if (y->r==q)y->r=p;
	}
	q->update();
}
void zag(node *p){
	node *q=p->f,*y=q->f;
	if ((q->r=p->l))q->r->f=q;
	p->l=q;q->f=p;
	p->f=y;
	if (y){
		if (y->l==q)y->l=p;
		else if (y->r==q)y->r=p;
	}
	q->update();
}
void Splay(node *p){
	while (p->f && (p->f->l==p || p->f->r==p)){
		node *q=p->f,*y=q->f;
		if (y && y->l==q){
			if (q->l==p)zig(q),zig(p);
			else zag(p),zig(p);
		}else if (y && y->r==q){
			if (q->r==p)zag(q),zag(p);
			else zig(p),zag(p);
		}else{
			if (q->l==p)zig(p);
			else zag(p);
		}
	}
	p->update();
}
node *Expose(node *p){
	node *q=NULL;
	for (;p;p=p->f){
		Splay(p);
		p->r=q;
		(q=p)->update();
	}
	return q;
}
node *head(node *p){
	while (p->l)p=p->l;
	Splay(p);
	return p;
}
node *next(node *p){
	Splay(p);
	p=p->l;
	while (p->r)p=p->r;
	Splay(p);
	return p;
}
void show(node *p){
	if (p){
		putchar('[');
		show(p->l);
		if (p->l && p->l->f!=p)putchar('a');
		printf("%d ",p-nodes);
		if (p->r && p->r->f!=p)putchar('b');
		show(p->r);
		putchar(']');
	}
}
int getX(int a){
	node *p=Expose(nodes+a);
	int k=p->sk,b=p->sb;
	node *q=Expose(head(p)->spf);
	int k2=q->sk,b2=q->sb;
	k2=(k2<=1?1-k2:MOD+1-k2);
	if (k2==0)return b2?-1:-2;
	int x=Inv[k2]*b2%MOD;
	return (k*x+b)%MOD;
}
void Change(int a,int K,int P,int B){
	node *p=nodes+a;
	node *r=head(Expose(p));
	if (p==r){
		p->k=K;p->b=B;
		p->update();
	}else{
		node *lca=Expose(r->spf);
		Expose(p);
		node *n=next(p);
		n->r=NULL;n->update();
		Splay(p);
		p->f=NULL;
		p->k=K;p->b=B;p->update();
		if (lca==p){
			Splay(r);
			r->f=r->spf,r->spf=NULL;
		}
	}
	node *q=nodes+P;
	if (head(Expose(q))==p)p->spf=q;
	else p->f=q,p->spf=NULL;
}
int main()
{
	int t=1,it=1;
	for (int i=0;i<MOD;i++){
		Inv[t]=it;
		t=t*5%MOD;it=it*4003%MOD;
	}
	scanf("%d",&N);
	for (int i=0;i<N;i++)uf[i]=-1;
	for (int i=0;i<N;i++){
		int p;
		scanf("%d%d%d",&(nodes[i].k),&p,&(nodes[i].b));p--;
		if (uffind(i)==uffind(p))
			nodes[i].f=NULL,nodes[i].spf=nodes+p;
		else{
			uf[uffind(i)]=uffind(p);
			nodes[i].f=nodes+p,nodes[i].spf=NULL;
		}
		nodes[i].l=nodes[i].r=NULL;
		nodes[i].update();
	}
	int Q;
	scanf("%d",&Q);
	while (Q--){
		char buf[10];
		int a;
		scanf("%s",buf);
		if (buf[0]=='A'){
			scanf("%d",&a);a--;
			printf("%d\n",getX(a));
		}else if (buf[0]=='C'){
			scanf("%d",&a);a--;
			int k,p,b;
			scanf("%d%d%d",&k,&p,&b);p--;
			Change(a,k,p,b);
		}
	}
	return 0;
}


