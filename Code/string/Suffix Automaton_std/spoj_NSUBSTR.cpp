#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
const int NMax=250000;
const int SMax=26;
char A[NMax+1];
int N;
struct node{
	int l,sc;
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
	curnode=root=ntop++;root[0]=node(0,NULL);
	for (int i=0;i<N;i++){
		int x=A[i]-'a';
		node *p=curnode;
		curnode=ntop++;curnode[0]=node(i+1,NULL);
		for (;p && !p->trans[x];p=p->p)p->trans[x]=curnode;
		if (!p)curnode->p=root;
		else{
			node *q=p->trans[x];
			if (q->l==p->l+1)curnode->p=q;
			else{
				node *r=ntop++;r[0]=q[0];r->l=p->l+1;
				curnode->p=r;q->p=r;
				for (;p && p->trans[x]==q;p=p->p)p->trans[x]=r;
			}
		}
	}
}
int F[NMax+1];
int main()
{
	scanf("%s",A);
	N=strlen(A);
	build();
	//for (node *p=npool;p!=ntop;p++){
		//printf("%d: %d %d %d %d\n",p-npool,p->l,p->p?p->p-npool:-1,
			//p->trans[0]?p->trans[0]-npool:-1,
			//p->trans[1]?p->trans[1]-npool:-1);
	//}
	for (int i=0;i<=N;i++)F[i]=0;
	static node *Q[NMax*2];
	static int cnt[NMax+1];
	for (int i=0;i<=N;i++)cnt[i]=0;
	for (node *p=npool;p!=ntop;p++)p->sc=0,cnt[p->l]++;
	for (int i=1;i<=N;i++)cnt[i]+=cnt[i-1];
	for (node *p=npool;p!=ntop;p++)Q[--cnt[p->l]]=p;
	for (node *p=root;;p=p->trans[A[p->l]-'a']){
		p->sc=1;
		if (p->l==N)break;
		//printf(":%d\n",p->l);
	}
	for (int i=(ntop-npool)-1;i>=0;i--){
		node *p=Q[i];
		//printf("%d %d\n",p->l,p->sc);
		F[p->l]=max(F[p->l],p->sc);
		if (p->p)p->p->sc+=p->sc;
	}
	for (int i=N-1;i>=0;i--)F[i]=max(F[i],F[i+1]);
	for (int i=1;i<=N;i++)printf("%d\n",F[i]);
	return 0;
}


