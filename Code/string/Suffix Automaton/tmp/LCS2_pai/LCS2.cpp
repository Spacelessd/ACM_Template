#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <algorithm>
using namespace std;
#define N 250005
#define CH 26
struct State{
	State *suf,*son[CH];int dep,l[9];
	State(){}//{memset(son,NULL,sizeof(son));}
};
State StatePool[N*2],*Q[N*2],*cur,*root,*last;
char str[N];int cnt[N];
void init(){
	cur=StatePool;root=last=cur++;
	root->suf=0;root->dep=0;
}
void extend(char c){
	State *p=last,*np=cur++;
	np->dep=p->dep+1;
	while (p&&!p->son[c])p->son[c]=np,p=p->suf;
	if (!p)np->suf=root;
	else {
		State *q=p->son[c];
		if (p->dep+1==q->dep)np->suf=q;
		else {
			State *nq=cur++; memcpy(nq->son,q->son,sizeof(q->son));
			nq->dep=p->dep+1; nq->suf=q->suf; q->suf=nq; np->suf=nq;
			while (p&&p->son[c]==q)p->son[c]=nq,p=p->suf;
		}
	}
	last=np;
}
void print(){
	for (State *x=StatePool;x!=cur;++x)
		for (int i=0;i<CH;++i)if (x->son[i])
			printf("%d->%c->%d\n",x-StatePool,i+'a',x->son[i]-StatePool);
	printf("\n");
	for (State *x=StatePool;x!=cur;++x)printf("dep%d %d\n",x-StatePool,x->dep);printf("\n");
	for (State *x=StatePool;x!=cur;++x)printf("suf%d %d\n",x-StatePool,x->suf-StatePool);printf("\n");
	//for (State *x=StatePool;x!=cur;++x)printf("right%d %d\n",x-StatePool,x->right);printf("\n");
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	init();scanf("%s",str);int n=strlen(str);
	for (char *pt=str;*pt;++pt)extend(*pt-'a');
	//print();
	for (State *x=StatePool;x!=cur;++x)++cnt[x->dep];
	for (int i=1;i<=n;++i)cnt[i]+=cnt[i-1];
	for (State *x=StatePool;x!=cur;++x)Q[cnt[x->dep]--]=x;
	int id;
	for (id=0;scanf("%s",str)!=EOF;++id){
		State *now=root;int l=0;
		for (char *pt=str;*pt;++pt){
			char c=*pt-'a';
			while (now&&!now->son[c])now=now->suf,l=now?now->dep:0;
			if (!now)now=root;
			else now=now->son[c],now->l[id]=max(now->l[id],++l);
		}
	}
	int ans=0;
	for (int i=cur-StatePool;i;--i){
		State *x=Q[i];int tmp=N;//x->dep;
		for (int j=0;j<id;++j){
			tmp=min(tmp,x->l[j]);
			if (x->suf)x->suf->l[j]=max(x->suf->l[j],x->l[j]);
		}
		ans=max(ans,tmp);
	}
	printf("%d\n",ans);
	//system("pause");for (;;);
	return 0;
}


