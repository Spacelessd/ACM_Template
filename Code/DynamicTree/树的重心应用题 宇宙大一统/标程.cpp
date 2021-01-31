#include<cstdio>
#include<algorithm>
#include<ctime>
using namespace std;
namespace you{
void Start(int);
void SetWeight(int,int);
long long AddEdge(int,int);
void DestroyAll();
const int NMax=200000;
int N;
struct node{
	node *l,*r,*p;
	int sz,w,sw,mrev;
	long long c,scl,scr;
	bool isroot(){
		return !(p && (p->l==this || p->r==this));
	}
	void reverse(){
		swap(scl,scr);
		swap(l,r);
		mrev^=1;
	}
	void down(){
		if (mrev){
			if (l)l->reverse();
			if (r)r->reverse();
			mrev=0;
		}
	}
	void update(){
		sz=1;sw=w;
		scl=scr=c;
		if (l){
			scl+=l->scl+(long long)sw*l->sz;
			scr+=l->scr+(long long)l->sw*sz;
			sz+=l->sz;
			sw+=l->sw;
		}
		if (r){
			scl+=r->scl+(long long)r->sw*sz;
			scr+=r->scr+(long long)sw*r->sz;
			sz+=r->sz;
			sw+=r->sw;
		}
	}
	void setr(node *y){
		if (r){
			w+=r->sw;
			c+=r->scl+r->sw;
		}
		if ((r=y)){
			w-=y->sw;
			c-=y->scl+y->sw;
		}
		update();
	}
}nodes[NMax];
void showall(){
	for (int i=0;i<N;i++){
		printf("%d:%d %d %d\n",i,nodes[i].p-nodes,nodes[i].l-nodes,nodes[i].r-nodes);
		printf("sz=%d w=%d c=%I64d sw=%d scl=%I64d scr=%I64d mrev=%d\n",nodes[i].sz,nodes[i].w,nodes[i].c,nodes[i].sw,nodes[i].scl,nodes[i].scr,nodes[i].mrev);
	}
}
void zig(node *p){
	node *q=p->p,*r=q->p;
	//	r
	//  q
	//p
	if ((q->l=p->r))q->l->p=q;
	p->r=q;q->p=p;
	if ((p->p=r)){
		if (q==r->l)r->l=p;
		else if (q==r->r)r->r=p;
	}
	q->update();
}
void zag(node *p){
	node *q=p->p,*r=q->p;
	if ((q->r=p->l))q->r->p=q;
	p->l=q;q->p=p;
	if ((p->p=r)){
		if (q==r->l)r->l=p;
		else if (q==r->r)r->r=p;
	}
	q->update();
}
void Splay(node *p){
	//printf("Splay %d\n",p-nodes);
	static node *sta[NMax];
	int top=0;
	for (node *i=p;!(sta[top++]=i)->isroot();i=i->p){
	}
	while (top){
		sta[--top]->down();
	}
	while (!p->isroot()){
		node *q=p->p;
		if (q->isroot()){
			if (p==q->l)zig(p);
			else zag(p);
		}else{
			node *r=q->p;
			if (q==r->l){
				if (p==q->l)zig(q),zig(p);
				else zag(p),zig(p);
			}else{
				if (p==q->r)zag(q),zag(p);
				else zig(p),zag(p);
			}
		}
	}
	p->update();
	//puts("splay done");
}
node *Expose(node *p){
	//printf("Expose %d\n",p-nodes);
	node *y=NULL;
	for (;p;p=p->p){
		Splay(p);
		p->setr(y);
		y=p;
	}
	return y;
}
void Start(int n){
	N=n;
	for (int i=0;i<N;i++){
		nodes[i].l=nodes[i].r=nodes[i].p=NULL;
		nodes[i].c=0;
		nodes[i].mrev=0;
	}
}
void SetWeight(int i,int w){
	nodes[i].w=w;
	nodes[i].update();
}
node *getCapital(node *c,int tot){
	int z=0;
	while (1){
		c->down();
		int u=z+(c->l?c->l->sw:0);
		if (u>=((tot+1)>>1)){
			c=c->l;
		}else if (u+c->w>=((tot+1)>>1)){
			break;
		}else{
			z=u+c->w;
			c=c->r;
		}
	}
	Splay(c);
	return c;
}
long long AddEdge(int na,int nb){
	//showall();
	//printf("addedge %d %d\n",na,nb);
	node *a=nodes+na,*b=nodes+nb;
	node *c=Expose(a),*d=Expose(b);
	//printf("c=%d d=%d\n",c-nodes,d-nodes);
	int tot=c->sw+d->sw;
	if (c->sw<=(tot>>1))swap(a,b),swap(c,d);
	Splay(a);
	d->reverse();
	a->r=d;d->p=a;a->update();
	//showall();
	node *e=getCapital(a,tot);
	node *f=Expose(e);
	f->reverse();
	//showall();
	//getchar();
	return f->scl;
}
void DestroyAll(){
}
}
int main()
{
	FILE *fin=fopen("1.in","r"),*fout=fopen("1.out","w");
	int n;
	while (fscanf(fin,"%d",&n),n){
		you::Start(n);
		int x;
		for (int i=0;i<n;i++){
			fscanf(fin,"%d",&x);
			you::SetWeight(i,x);
		}
		long long c=0;
		int flg=1;
		for (int i=0;i<n-1;i++){
			int a,b;
			fscanf(fin,"%d%d",&a,&b);a--;b--;
			if (flg){
				a=a^int(c)^int(c>>32);
				b=b^(int(c)+int(c>>32));
				if (a>=0 && a<n && b>=0 && b<n){
					c=you::AddEdge(a,b);
					fprintf(fout,"%I64d\n",c);
				}else{
					flg=0;
					you::DestroyAll();
				}
			}
			if (!flg){
				fprintf(fout,"-1\n");
			}
		}
		if (flg)you::DestroyAll();
	}
	fclose(fin);fclose(fout);
	return 0;
}


