#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 250005
#define CH 26
inline int max(int x,int y){return x>y?x:y;}
struct State{
	State *suf,*son[CH];int dep,right;
	State(){memset(son,NULL,sizeof(son));}
	//State(int _dep,State *_suf):dep(_dep),suf(_suf){}
};
State StatePool[N*2],*Q[N*2],*cur,*root,*last;
int F[N],cnt[N];
char str[N]="ababa";
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
void print(){
	for (State *x=StatePool;x!=cur;++x)
		for (int i=0;i<CH;++i)
			if (x->son[i]!=NULL)
			printf("%d->%c->%d\n",x-StatePool,i+'a',x->son[i]-StatePool);
	printf("\n");
	for (State *x=StatePool;x!=cur;++x)printf("dep%d %d\n",x-StatePool,x->dep);printf("\n");
	for (State *x=StatePool;x!=cur;++x)printf("suf%d %d\n",x-StatePool,x->suf-StatePool);printf("\n");
	for (State *x=StatePool;x!=cur;++x)printf("right%d %d\n",x-StatePool,x->right);printf("\n");
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	//scanf("%s",str);
	int n=strlen(str);
	for (int i=0;i<n;++i)str[i]-='a';
	init();
	for (int i=0;i<n;++i)extend(str[i]);
	for (State *x=StatePool;x!=cur;++x)++cnt[x->dep];
	for (int i=1;i<=n;++i)cnt[i]+=cnt[i-1];
	for (State *x=StatePool;x!=cur;++x)Q[--cnt[x->dep]]=x;
	for (State *x=root;;x=x->son[str[x->dep]]){
		x->right=1;printf("init%d\n",x-StatePool);if (x->dep==n)break;
	}
	for (int i=cur-StatePool-1;i>=0;--i){
		State *x=Q[i];
		F[x->dep]=max(F[x->dep],x->right);
		if (x->suf)x->suf->right+=x->right;
	}
	for (int i=n-1;i;--i)F[i]=max(F[i],F[i+1]);
	for (int i=1;i<=n;++i)printf("%d\n",F[i]);
	print();
	system("pause");for (;;);
	return 0;
}


