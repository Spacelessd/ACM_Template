#include<cstdio>
#include<algorithm>
#define NMax 30000
#define INF 100000000
using namespace std;
struct edge{
	int e;
	edge *next;
}epool[NMax+NMax],*E[NMax],*etop=epool;
char Map[NMax][10];
struct rec{
	int a[2][2],b[2][2];
	static rec ini(char *c){
		rec r;
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++){
				if (c[i]!='#' && c[j]!='#')
					r.a[i][j]=1+(i!=j);
				else r.a[i][j]=-INF;
			}
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++){
				if (c[j]=='#')r.b[i][j]=0;
				else r.b[i][j]=(c[1-j]!='#')+1;
			}
		return r;
	}
	static rec empty(){
		rec r;
		for (int i=0;i<2;i++)for (int j=0;j<2;j++){
			r.b[i][j]=0;
			r.a[i][j]=(i==j?0:-INF);
		}
		return r;
	}
	rec operator+(const rec &c)const{
		rec r;
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++){
				int s=a[i][0]+c.a[0][j];
				int t=a[i][1]+c.a[1][j];
				if (s<t)s=t;
				if (s<-INF)s=-INF;
				r.a[i][j]=s;
			}
		for (int j=0;j<2;j++){
			int s=b[0][j];
			for (int k=0;k<2;k++){
				int t=a[j][k]+c.b[0][k];
				if (s<t)s=t;
			}
			r.b[0][j]=s;
			s=c.b[1][j];
			for (int k=0;k<2;k++){
				int t=b[1][k]+c.a[k][j];
				if (s<t)s=t;
			}
			r.b[1][j]=s;
		}
		return r;
	}
	rec reverse()const{
		rec r;
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				r.a[i][j]=a[j][i],
				r.b[1-i][j]=b[i][j];
		return r;
	}
};
struct node{
	rec k,s;
	node *l,*r,*f;
	void update(){
		s=k;
		if (l)s=l->s+s;
		if (r)s=s+r->s;
	}
}nodes[NMax];
int N;
void bfs(){
	for (int i=0;i<N;i++){
		nodes[i].l=nodes[i].r=NULL;
		nodes[i].f=NULL;
		nodes[i].k=rec::ini(Map[i]);
		nodes[i].update();
	}
	static int Q[NMax];
	Q[0]=0;
	int bot=1;
	for (int i=0;i<bot;i++){
		int x=Q[i];
		for (edge *p=E[x];p;p=p->next)
			if (p->e && nodes[p->e].f==NULL)
				nodes[Q[bot++]=p->e].f=nodes+x;
	}
}
void zig(node *p){
	//     y
	//    /
	//   q
	//  /
	// p
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
void Change(int x){
	Splay(nodes+x);
	nodes[x].k=rec::ini(Map[x]);
	nodes[x].update();
}
int Ask(int x,int y){
	node *p=nodes+x,*q=nodes+y;
	Expose(p);
	node *r=Expose(q);
	rec ret=r->k;
	if (r->r)ret=ret+r->r->s;
	if (p!=r){
		Splay(p);
		ret=p->s.reverse()+ret;
	}
	return max(ret.b[0][0],ret.b[0][1]);
}
int main()
{
	int Q;
	scanf("%d%d",&N,&Q);
	for (int i=0;i<N;i++)E[i]=NULL;
	for (int i=0;i<N-1;i++){
		int x,y;
		scanf("%d%d",&x,&y);x--;y--;
		etop->e=y;etop->next=E[x];E[x]=etop++;
		etop->e=x;etop->next=E[y];E[y]=etop++;
	}
	for (int i=0;i<N;i++){
		scanf("%s",Map[i]);
	}
	bfs();
	while (Q--){
		char cmd[10];
		int x,y;
		scanf("%s",cmd);
		if (cmd[0]=='Q'){
			scanf("%d%d",&x,&y);x--;y--;
			printf("%d\n",Ask(x,y));
		}else{
			scanf("%d",&x);x--;
			scanf("%s",Map[x]);
			Change(x);
		}
	}
	return 0;
}


