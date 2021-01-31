#include <cstdio>
#include <ctime>
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
}H;
int N,ecnt=0;
int E(int x,int y){ecnt++;
	if (x==y)return 0;
	/*int r=x*13687+y*68877+x*y*3611+x*x*6541+y*y*6329;
	return (r&0x7fffffff)%100001+1;*/
	if (x>y){int t=x;x=y;y=t;}
	if (y==x+1)return 1;
	return (100000-x-x)*10000+10000-y;
}
char label[NMax];
int main()
{
	scanf("%d",&N);
	int cntdec=0;
	int t1=clock();
	nodes[0].k=0;
	for (int i=1;i<N;i++){
		label[i]=0;
		nodes[i].k=E(0,i);
		H.ins(nodes+i);
	}
	while (H.n){
		int x=H.extract()-nodes;
		label[x]=1;
		for (int i=1;i<N;i++)if (!label[i]){
			int t=nodes[x].k+E(x,i);
			if (t<nodes[i].k){
				nodes[i].k=t;
				H.decrease(nodes+i);
				cntdec++;
			}
		}
	}
	int t2=clock()-t1;
	//for (int i=0;i<N;i++)printf("%d %d\n",nodes[i].k,E(0,i));
	printf("ecnt=%d cntdec=%d\n",ecnt,cntdec);
	int t3=clock();
	int becnt=ecnt;
	for (int i=0;i<becnt;i++)E(123,456);
	int t4=clock()-t3;
	printf("time=%d-%d=%d\n",t2,t4,t2-t4);
	getchar();getchar();
	return 0;
}
