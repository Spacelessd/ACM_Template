#include <cstdio>
#include <algorithm>
#define NMax 100010
using namespace std;
struct node{
	int k,mx;
	node *l,*r,*f;
	void update(){
		mx=k;
		if (l && l->mx>mx)mx=l->mx;
		if (r && r->mx>mx)mx=r->mx;
	}
}nodes[NMax];
struct edge{
	int e,c,who;
	edge *next;
}*E[NMax],epool[NMax+NMax],*etop=epool;
int N;
int Q[NMax];
void bfs(){
	int bot=1;
	Q[0]=0;
	for (int i=0;i<N;i++)nodes[i].f=NULL;
	for (int i=0;i<bot;i++){
		int x=Q[i];
		for (edge *p=E[x];p;p=p->next)
			if (p->e && nodes[p->e].f==NULL){
				nodes[p->e].k=p->c;
				p->who=p->e;
				epool[(p-epool)^1].who=p->e;
				nodes[Q[bot++]=p->e].f=nodes+x;
			}
	}
}
void zig(node *p){
	//    y
	//   /
	//  q
	// /
	//p
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
	node *q;
	for (q=NULL;p;p=p->f){
		Splay(p);
		p->r=q;
		(q=p)->update();
	}
	return q;
}
int Ask(int x,int y){
	node *p=nodes+x,*q=nodes+y;
	Expose(p);
	node *r=Expose(q);
	int mx=1<<31;
	if (r->r)mx=max(mx,r->r->mx);
	if (p!=r){
		Splay(p);
		mx=max(mx,p->mx);
	}
	return mx;
}
void Change(int x,int y){
	node *p=nodes+x;
	Splay(p);
	p->k=y;
	p->update();
}
void work(){
	scanf("%d",&N);
	etop=epool;
	for (int i=0;i<N;i++)E[i]=NULL;
	for (int i=0;i<N-1;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);x--;y--;
		etop->e=y;etop->c=z;etop->next=E[x];E[x]=etop++;
		etop->e=x;etop->c=z;etop->next=E[y];E[y]=etop++;
	}
	for (int i=0;i<N;i++){
		nodes[i].l=nodes[i].r=NULL;
		nodes[i].k=1<<31;
	}
	bfs();
	for (int i=0;i<N;i++)nodes[i].update();
	while (1){
		char buf[10];
		int x,y;
		scanf("%s",buf);
		if (buf[0]=='D')break;
		if (buf[0]=='Q'){
			scanf("%d%d",&x,&y);x--;y--;
			printf("%d\n",Ask(x,y));
		}else{
			scanf("%d%d",&x,&y);x--;
			Change(epool[x+x].who,y);
		}
	}
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	int TT;
	scanf("%d",&TT);
	while (TT--)work();
	return 0;
}

