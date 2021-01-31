#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 4000005
#define CH 26
struct State{
	State *suf,*son[CH];int dep,ans,curlen;
	State(){}//{memset(son,NULL,sizeof(son));}
};
State StatePool[N*2],*Q[N*2],*cur,*root,*last;
char str[N];int cnt[N],State1;
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
	int t1=clock();
	init();scanf("%s",str);int n=strlen(str);
	for (char *pt=str;*pt;++pt)extend(*pt-'a'); //print();
	State1=cur-StatePool;
	for (State *x=StatePool;x!=cur;++x)x->ans=x->dep;
	for (State *x=StatePool;x!=cur;++x)++cnt[x->dep];
	for (int i=1;i<=n;++i)cnt[i]+=cnt[i-1];
	for (State *x=StatePool;x!=cur;++x)Q[cnt[x->dep]--]=x;
	while(scanf("%s",str)!=EOF){
		for (int i=0;i<State1;++i)StatePool[i].curlen=0;
		State *now=root;int l=0;
		for (char *pt=str;*pt;++pt){
			char c=*pt-'a';
			while (now->suf&&!now->son[c])now=now->suf,l=now->dep;
			if (now->son[c]){
				now=now->son[c];
				if (++l>now->curlen)now->curlen=l;
			}
		}
		for (int i=State1;i;--i){
			State *x=Q[i];
			if (x->curlen<x->ans)x->ans=x->curlen;
			if (x->suf&&x->curlen>x->suf->curlen)x->suf->curlen=x->curlen;
		}
	}
	int ans=0;
	for (State *x=StatePool;x!=cur;++x)if (x->ans>ans)ans=x->ans;
	printf("%d\n",ans);
	printf("time=%d\n",clock()-t1);
	//system("pause");for (;;);
	return 0;
}


