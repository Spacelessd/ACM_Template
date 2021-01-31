#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 250005
#define CH 26
struct State{
	State *suf,*son[CH];int dep;
	State(){}//{memset(son,NULL,sizeof(son));}
};
State StatePool[N*2],*cur,*root,*last;
char str[N];
void init(){
	cur=StatePool;root=last=cur++;
	root->suf=NULL;root->dep=0;
}
void extend(char c){
	State *p=last,*np=cur++;
	np->dep=p->dep+1;
	while (p!=NULL&&p->son[c]==NULL)
		p->son[c]=np,p=p->suf;
	if (p==NULL)np->suf=root;
	else {
		State *q=p->son[c];
		if (p->dep+1==q->dep)np->suf=q;
		else {
			State *nq=cur++;
			memcpy(nq->son,q->son,sizeof(q->son));
			nq->dep=p->dep+1; nq->suf=q->suf;
			q->suf=nq; np->suf=nq;
			while (p!=NULL&&p->son[c]==q)
				p->son[c]=nq,p=p->suf;
		}
	}
	last=np;
}
int ans;
void go(char *str){
	State *now=root;int l=0;ans=0;
	for (char *pt=str;*pt;++pt){
		char c=*pt-'a';
		if (now->son[c])now=now->son[c],++l;
		else {
			while (now!=NULL&&now->son[c]==NULL)
				now=now->suf;
			if (now==NULL)now=root,l=0;
			else l=now->dep+1,now=now->son[c];
		}
		if (l>ans)ans=l;
	}
}
void print(){
	for (State *x=StatePool;x!=cur;++x)
		for (int i=0;i<CH;++i)
			if (x->son[i]!=NULL)
			printf("%d->%c->%d\n",x-StatePool,i+'a',x->son[i]-StatePool);
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%s",str);
	init();
	for (char *pt=str;*pt;++pt)
		extend(*pt-'a');
	scanf("%s",str);
	go(str);
	printf("%d\n",ans);
	system("pause");
	return 0;
}


