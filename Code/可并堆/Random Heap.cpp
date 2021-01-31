#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct node{node *l,*r;int key;}nodes[N];
int ran(){static int x=31253125;x+=(x<<4)+1;x&=0x7fffffff;return x&65536;}
node *M(node *p,node *q){
	return (!p||!q)?(p?p:q):(p->key>q->key?M(q,p):
		((ran()?p->r=M(p->r,q):p->l=M(p->l,q)),p));
}
node *root;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n;scanf("%d",&n);
	int x=13251325;
	int t1=clock();
	root=NULL;
	for (int i=0;i<n;++i){
		nodes[i].key=x&0x7fffffff;
		nodes[i].l=nodes[i].r=NULL;
		x+=(x<<2)+1;
		root=M(root,nodes+i);
	}
	while (root){
		//printf("%d\n",root->k);
		root=M(root->l,root->r);
	}
	printf("time=%d\n",(int)clock()-t1);
	system("pause");for (;;);
	return 0;
}


