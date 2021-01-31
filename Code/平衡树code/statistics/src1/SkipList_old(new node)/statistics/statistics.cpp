#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
#define exp 0.5
#define Maxlevel 20
#define Maxp 100005
int state,sum,ans;
struct node{
	node *l,*r,*d;
	int key,level,size;bool top;
};
struct SkipList{
	static node *last[Maxlevel+2],*tmp[Maxlevel+2],*tmp1[Maxlevel+2],*path[Maxp];
	int p1;node *root;
	void clear(){
		int lvl=Maxlevel;
		for (int i=0;i<=lvl;++i)tmp[i]=new node,tmp[i]->l=NULL,tmp[i]->key=-oo,tmp[i]->size=0;
		for (int i=0;i<=lvl;++i)tmp1[i]=new node,tmp1[i]->r=NULL,tmp1[i]->key=oo,tmp1[i]->size=0;
		for (int i=0;i<=lvl;++i){
			tmp[i]->r=tmp1[i];tmp1[i]->l=tmp[i];
			if (i==0)tmp[i]->d=tmp1[i]->d=NULL;
				else tmp[i]->d=tmp[i-1],tmp1[i]->d=tmp1[i-1];
		}
		root=tmp[lvl];root->level=lvl;
	}
	SkipList(){clear();}
	int Rand(){
		static int x=12347;
		x=(x*1001+333)%100007;
		return x&32767;
	}
	int RandLevel(){
		int lvl=1;
		while (Rand()<exp*32768&&lvl<Maxlevel)++lvl;
		return lvl;
	}
	node *find(int key){
		node *x=root;int lvl=root->level;p1=0;
		while (x){
			path[++p1]=x;
			if (x->r->key<=key)x=x->r;
				else last[lvl--]=x,x=x->d;
		}
		return last[0];
	}
	void update(int x){
		find(x);
		for (int i=p1-1;i;--i){
			if (path[i]->r->top)
				path[i]->size=path[i]->d->size+path[i]->r->size;
			else path[i]->size=path[i]->d->size;
		}
	}
	void insert(int key){
		++sum;find(key);
		int lvl=RandLevel();
		for (int i=0;i<=lvl;++i)tmp[i]=new node,tmp[i]->key=key,tmp[i]->top=0;
		tmp[lvl+1]=NULL;
		for (int i=0;i<=lvl;++i){
			tmp[i]->r=last[i]->r;
			last[i]->r->l=tmp[i];
			last[i]->r=tmp[i];tmp[i]->l=last[i];
			if (i==0)tmp[i]->d=NULL;
				else tmp[i]->d=tmp[i-1];
		}
		tmp[0]->level=lvl;tmp[lvl]->top=1;tmp[0]->size=1;
		update(key);update(key-1);
	}
	void del(int key){
		--sum;find(key);node *x;
		int lvl=x->level;
		for (int i=1;i<=lvl;++i){
			x->r->l=x->l;x->l->r=x->r;
		}
	}
	node *max(node *x){
		while (x->r||x->d)
			if (x->r)x=x->r;
				else x=x->d;
		return x;
	}
	node *findkth(int k){
		node *x=root;
		while (k){
			if (x->r->top&&x->d&&x->d->size<k)k-=x->d->size,x=x->r;
				else {if (!x->d)break;x=x->d;}
		}
		return x;
	}
	void print(){
		node *x=root,*y;
		for (int i=0;i<=root->level;++i){
			y=x;while (y!=NULL)printf("%d %d | ",y->key,y->size),y=y->r;
			printf("\n");x=x->d;
		}
		printf("end\n");
	}
};
node* SkipList::last[Maxlevel+2];
node* SkipList::tmp[Maxlevel+2];
node* SkipList::tmp1[Maxlevel+2];
node* SkipList::path[Maxp];
SkipList a;
void init(){
	//srand(time(0));
	ans=0;sum=0;a.clear();
}
int main()
{
	long long n,A,b,c,m,i,tmp,key,ans=1;
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	a.insert(1);
	for (i=2;i<=n;++i){
		if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
		m=a.findkth(tmp)->key;
		key=(A*m+b*i+c)%1000000007;
		a.insert((int)key);
		ans+=key;
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}




