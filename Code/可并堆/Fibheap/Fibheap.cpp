#include <cstdio>
#include <stdlib.h>
#define NMax 10000
using namespace std;
struct node{
	int k,d;
	node *l,*r,*p,*s;
	char mark;
}nodes[NMax];
#define FHLINK(_,__) _->r=__,__->l=_
#define FHINSERT(_,__) _->r=__->r,_->l=__,\
					 _->r->l=_,__->r=_
struct fibheap{
	node *root;
	int n;
	fibheap(){n=0;root=NULL;}
	void ins(node *p){
		p->d=0;p->p=p->s=NULL;p->mark=0;
		if (!root){
			root=p;p->l=p->r=p;
		}else{
			FHINSERT(p,root);
			if (p->k<root->k)root=p;
		}
		n++;
	}
	void unite(fibheap *h){
		if (!h->n)return;
		if (!n){*this=*h;return;}
		node *p=root->r,*q=h->root->r;
		FHLINK(root,q);
		FHLINK(h->root,p);
		if (h->root->k<root->k)root=h->root;
		n+=h->n;
	}
	node *extract(){
		node *z=root;
		if (!z)return z;
		for (node *y=z->s;z->s;y=z->s){
			y->p=NULL;
			if (y->r==y)z->s=NULL,z->d=0;
			else{
				y->l->r=y->r,y->r->l=y->l,z->d--;
				z->s=z->s->r;
			}
			FHINSERT(y,z);
		}
		if (n==1)root=NULL;
		else{
			z->r->l=z->l;z->l->r=z->r;
			root=z->r;
			consolidate();
		}
		n--;
		return z;
	}
	void consolidate(){
		static node *buf[66];
		int D=0;
		while ((1<<D)<n)D++;
		D=D+D+2;
		for (int i=0;i<D;i++)buf[i]=NULL;
		for (node *w=root;root;w=root){
			if (w->r==w)root=NULL;
			else{
				w->r->l=w->l,w->l->r=w->r;
				root=root->r;
			}
			while (buf[w->d]){
				node *x=w,*y=buf[w->d];
				if (x->k>y->k)w=y,y=x,x=w;
				if (!x->s)x->s=y,y->r=y->l=y;
				else FHINSERT(y,x->s);
				buf[w->d]=NULL;
				y->p=x;x->d++;
				x->mark=0;
			}
			buf[w->d]=w;
		}
		node *u;
		for (int i=0;i<D;i++)if ((u=buf[i])){
			if (!root)root=u,u->r=u->l=u;
			else{
				FHINSERT(u,root);
				if (u->k<root->k)root=u;
			}
		}
	}
	void cut(node *x,node *y){
		if (x->r==x)y->s=NULL;
		else{
			x->l->r=x->r;x->r->l=x->l;
			if (x==y->s)y->s=y->s->r;
		}
		y->d--;x->p=NULL;x->mark=0;
		FHINSERT(x,root);
	}
	void cascadingcut(node *y){
		node *z=y->p;
		if (z){
			if (y->mark==0)y->mark=1;
			else{
				cut(y,z);
				cascadingcut(z);
			}
		}
	}
	void decrease(node *p){
		node *y=p->p;
		if (y && p->k<y->k){
			cut(p,y);
			cascadingcut(y);
		}
		if (p->k<root->k)root=p;
	}
	void show(node *p,int d){
		/*for (int i=0;i<d;i++)printf("	");
		printf("%d %d %d\n",p->k,p->d,(int)p->mark);*/
		int tmp=0;
		for (node *i=p->s;i;i=i->r){
			if (i->r->l!=i || i->l->r!=i)printf("lr!");
			if (i->p!=p)printf("p!");
			if (i->k<p->k)printf("k!");
			show(i,d+1);
			tmp++;
			if (i->r==p->s)break;
		}
		if (tmp!=p->d){
			for (int i=0;i<d;i++)printf("	");
			printf("d!\n");
		}
	}
	void show(){
		for (node *p=root;p;p=p->r){
			if (p->r->l!=p || p->l->r!=p)printf("lr!");
			if (p->p)printf("p!");
			if (p->k<root->k)printf("k!");
			show(p,0);
			if (p->r==root)break;
		}
		//puts("");
	}
}H;
int main()
{
	for (int i=0;i<100;i++){
		nodes[i].k=rand();
		H.ins(nodes+i);
	}
	H.extract();
	int pt=100;
	for (int i=0;i<99;i++){
		int u=rand();
		if (u<nodes[i].k){
			nodes[i].k=u;
			H.decrease(nodes+i);
		}else if (u%100<20){
			nodes[i].k=-1000000000;
			H.decrease(nodes+i);
			H.extract();
		}else if (u%100>80){
			nodes[pt].k=rand();
			H.ins(nodes+pt);
			pt++;
		}
		H.show();
	}
	//H.show();
	while (H.n){
		printf("%d\n",H.extract()->k);
		//H.show();
	}
	system("pause");
	return 0;
}


