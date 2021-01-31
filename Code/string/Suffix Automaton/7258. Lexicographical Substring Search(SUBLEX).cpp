#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
#define CH 26
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
struct State{
	State *suf,*son[CH];int dep;
	char transchar;unsigned int w;
	State(){}//{memset(son,NULL,sizeof(son));}
};
State StatePool[N*2],*Q[N*2],*cur,*root,*last;
char str[N];int cnt[N],State1,n;
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
void calc(){
	for (State *x=StatePool;x!=cur;++x)++cnt[x->dep];
	for (int i=1;i<=n;++i)cnt[i]+=cnt[i-1];
	for (State *x=StatePool;x!=cur;++x)Q[cnt[x->dep]--]=x;
	for (int i=State1;i;--i){
		State *x=Q[i];x->w=1;int k=0;
		for (int i=0;i<CH;++i)
			if (x->son[i]){
				x->w+=x->son[i]->w;
				x->son[k++]=x->son[i];
				x->son[i]->transchar='a'+i;
			}
		x->son[k]=0;
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	init();scanf("%s",str);n=strlen(str);
	for (char *pt=str;*pt;++pt)extend(*pt-'a'); //print();
	State1=cur-StatePool;
	calc();
	int T;scanf("%d",&T);
	static char buf[N];
	while (T--){
		unsigned int x;
		scanf("%u",&x);
		if (x>=root->w){puts("WRONG");continue;}
		char *pt=buf;
		for (State *p=root;x&&p;){
			--x;
			for (int i=0;p->son[i];++i){
				State *q=p->son[i];
				if (q->w<=x)x-=q->w;
				else {
					p=q;(*pt++)=q->transchar;
					break;
				}
			}
		}
		*pt=0;puts(buf);
	}
	//printf("time=%d\n",clock()-t1);
	//system("pause");for (;;);
	return 0;
}


