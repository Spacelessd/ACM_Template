#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
const int NMax=2500005;
const int SMax=26;
struct node{
	int l;
	int mnlen,curlen;
	node *p;
	node *trans[SMax];
	node(){}
	node(int _l,node *_p):l(_l),p(_p){
		memset(trans,0,sizeof(trans));
	}
}npool[NMax*2],*ntop,*root,*curnode;
char A[NMax+1];
node *Q[NMax*2];
int cnt[NMax+1];
int N,nn;
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
				curnode->p=q->p=r;
				for (;p && p->trans[x]==q;p=p->p)p->trans[x]=r;
			}
		}
	}
	nn=ntop-npool;
	for (int i=0;i<=N;i++)cnt[i]=0;
	for (int i=0;i<nn;i++)cnt[npool[i].l]++;
	for (int i=1;i<=N;i++)cnt[i]+=cnt[i-1];
	for (int i=nn-1;i>=0;i--)Q[--cnt[npool[i].l]]=npool+i;
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("3.out","w",stdout);
	scanf("%s",A);
	N=strlen(A);
	build();
	for (int i=0;i<nn;i++)npool[i].mnlen=npool[i].l;//init!!!
	while (scanf("%s",A)!=EOF){
		for (int i=0;i<nn;i++)npool[i].curlen=0;
		node *p=root;
		int l=0;
		for (int i=0;A[i];i++){
			int x=A[i]-'a';
			while (p->p && p->trans[x]==NULL)p=p->p,l=p->l;
			if (p->trans[x]){
				l++;
				p=p->trans[x];
				if (p->curlen<l)p->curlen=l;
			}else p=root,l=0;
		}
		//for (node *x=npool;x!=ntop;++x)printf("l=%d\n",x->curlen);
		for (int i=nn-1;i>=0;i--){
			node *p=Q[i];
			if (p->mnlen>p->curlen)p->mnlen=p->curlen;
			if (p->p){
				if (p->p->curlen<p->curlen)
					p->p->curlen=p->curlen;
			}
		}
		for (node *x=npool;x!=ntop;++x)printf("l=%d\n",x->curlen);
	}
	int ret=0;
	for (int i=0;i<nn;i++){
		if (ret<npool[i].mnlen)
			ret=npool[i].mnlen;
	}
	for (node *x=npool;x!=ntop;++x)printf("all=%d\n",x->mnlen);
	printf("%d\n",ret);
	return 0;
}


