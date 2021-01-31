#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
const int NMax=90000;
const int SMax=26;
int N;
char A[NMax+1];
struct node{
	node *p;
	int l;
	unsigned int w;
	node *trans[SMax+1];
	char transchar;
	node(){}
	node(node *_p,int _l):p(_p),l(_l){
		memset(trans,0,sizeof(trans));
	}
}npool[NMax*2],*ntop;
node *root,*curnode;
void build(){
	ntop=npool;
	root=curnode=ntop++;curnode[0]=node(NULL,0);
	for (int i=0;i<N;i++){
		int x=A[i]-'a';
		node *p=curnode;
		curnode=ntop++;curnode[0]=node(NULL,i+1);
		for (;p && !p->trans[x];p=p->p)p->trans[x]=curnode;
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
}
node *Q[NMax*2];
int cnt[NMax+1];
void calc(){
	int nn=ntop-npool;
	for (int i=0;i<=N;i++)cnt[i]=0;
	for (int i=0;i<nn;i++)cnt[npool[i].l]++;
	for (int i=1;i<=N;i++)cnt[i]+=cnt[i-1];
	for (int i=0;i<nn;i++)Q[--cnt[npool[i].l]]=npool+i;
	for (int i=nn-1;i>=0;i--){
		node *p=Q[i];
		p->w=1;
		int k=0;
		for (int j=0;j<SMax;j++)
			if (p->trans[j]){
				p->w+=p->trans[j]->w;
				p->trans[k++]=p->trans[j];
				p->trans[j]->transchar='a'+j;
			}
		p->trans[k]=0;
	}
}
int main()
{
	scanf("%s",A);
	N=strlen(A);
	build();
	calc();
	int TT;
	scanf("%d",&TT);
	static char buf[NMax+1];
	while (TT--){
		unsigned int x;
		scanf("%u",&x);
		if (x>=root->w){
			puts("WRONG");
			continue;
		}
		char *pt=buf;
		for (node *p=root;x && p;){
			x--;
			for (int i=0;p->trans[i];i++){
				node *q=p->trans[i];
				if (q->w<=x)x-=q->w;
				else{
					p=q;
					*(pt++)=q->transchar;
					break;
				}
			}
		}
		pt[0]=0;
		puts(buf);
	}
	return 0;
}


