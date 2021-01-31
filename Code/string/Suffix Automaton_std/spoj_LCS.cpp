#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
const int NMax=250000;
const int SMax=26;
int N,M;
char A[NMax+1],B[NMax+1];
struct node{
	int l;
	node *p;
	node *trans[SMax];
	node(){}
	node(int _l,node *_p):l(_l),p(_p){
		memset(trans,0,sizeof(trans));
	}
}npool[NMax*2],*ntop;
node *root,*curnode;
void build(){
	ntop=npool;
	root=curnode=ntop++;root[0]=node(0,NULL);
	for (int i=0;i<N;i++){
		int x=A[i]-'a';
		node *p=curnode;
		curnode=ntop++;curnode[0]=node(i+1,NULL);
		for (;p && p->trans[x]==NULL;p=p->p)p->trans[x]=curnode;
		if (!p)curnode->p=root;
		else{
			node *q=p->trans[x];
			if (q->l==p->l+1)curnode->p=q;
			else{
				node *r=ntop++;r[0]=q[0];r->l=p->l+1;
				q->p=r;curnode->p=r;
				for (;p && p->trans[x]==q;p=p->p)p->trans[x]=r;
			}
		}
	}
}
int main()
{
	scanf("%s%s",A,B);
	N=strlen(A);M=strlen(B);
	build();
	node *p=root;
	int ret=0;
	for (int i=0,l=0;i<M;i++){
		int x=B[i]-'a';
		if (p->trans[x])l++,p=p->trans[x];
		else{
			while (p && p->trans[x]==NULL)p=p->p;
			if (p){
				l=p->l+1;
				p=p->trans[x];
			}else{
				p=root;
				l=0;
			}
		}
		if (ret<l)ret=l;
	}
	printf("%d\n",ret);
	return 0;
}


