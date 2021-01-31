#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct node{
	node *l,*r;
	int d,key;
}nodes[N];
#define DIST(_) (_?_->d:-1)
#define SWAP(_,__) t=_,_=__,__=t
node *Merge(node *p,node *q){
	static node *t;
	if (!p || !q)return p?p:q;
	if (p->key>q->key)SWAP(p,q);
	p->r=Merge(p->r,q);
	if (DIST(p->l)<DIST(p->r))SWAP(p->l,p->r);
	return p->d=DIST(p->r)+1,p;
}
node *root;
int n;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d",&n);
	int x=13251325;
	int t1=clock();
	root=NULL;
	for (int i=0;i<n;++i){
		nodes[i].key=x&0x7fffffff;
		nodes[i].l=nodes[i].r=NULL;
		nodes[i].d=0;
		x+=(x<<2)+1;
		root=Merge(root,nodes+i);
	}
	while (root){
		//printf("%d\n",root->k);
		root=Merge(root->l,root->r);
	}
	printf("time=%d\n",(int)clock()-t1);
	system("pause");for (;;);
	return 0;
}


