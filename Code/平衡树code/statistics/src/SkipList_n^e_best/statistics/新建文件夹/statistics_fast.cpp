#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define oo (1<<30)
int Exp;
#define Maxlevel 11
#define Maxp 100005
struct node{
	node *l,*r,*d;
	int key,size,top;
	void update(){
		size=d->size;
		if (r->top)size+=r->size;
	}
};
#define BUFFER_SIZE 10000
node *Pool=new node[BUFFER_SIZE],*cur=Pool;
node *NewNode(){
	if (cur==Pool+BUFFER_SIZE)Pool=new node[BUFFER_SIZE],cur=Pool;
	return cur++;
}
struct SkipList{
	static node *last[Maxlevel+2],*tmp[Maxlevel+2],*tmp1[Maxlevel+2],*path[Maxp];
	int level,p1;node *root;
	void clear(){
		int lvl=Maxlevel;
		for (int i=0;i<=lvl;++i)tmp[i]=NewNode(),tmp[i]->l=NULL,
		tmp[i]->key=-oo,tmp[i]->size=0,tmp[i]->top=0;
		for (int i=0;i<=lvl;++i)tmp1[i]=NewNode(),tmp1[i]->r=NULL,
			tmp1[i]->key=oo,tmp1[i]->size=0,tmp1[i]->top=0;
		for (int i=0;i<=lvl;++i){
			tmp[i]->r=tmp1[i];tmp1[i]->l=tmp[i];
			if (!i)tmp[i]->d=tmp1[i]->d=NULL;
				else tmp[i]->d=tmp[i-1],tmp1[i]->d=tmp1[i-1];
		}
		root=tmp[lvl];level=lvl;
	}
	SkipList(){clear();}
	int Rand(){
		static int x=12347;
		x=(x<<5)+(x>>2)+1;
		return x&32767;
	}
	int RandLevel(){
		int lvl=1;
		while (Rand()<Exp&&lvl<Maxlevel)++lvl;
		return lvl;
	}
	node *find(register int key){
		register node *x=root;register int lvl=level;p1=0;
		while (x){
			path[++p1]=x;
			if (x->r->key<=key)x=x->r;
				else last[lvl--]=x,x=x->d;
		}
		return last[0];
	}
	void update(register int lvl){
		for (register int i=1;i<=lvl;++i)
			tmp[i]->update();
		for (register int i=p1-1;i;--i)
			path[i]->update();
	}
	void insert(int key){
		find(key);
		int lvl=RandLevel();register node *x,*y;
		for (int i=0;i<=lvl;++i)x=tmp[i]=NewNode(),x->key=key,x->top=0;
		for (int i=0;i<=lvl;++i){
			x=tmp[i];y=last[i];
			x->r=y->r;y->r->l=x;
			y->r=x;x->l=y;
			if (!i)x->d=NULL;
				else x->d=tmp[i-1];
		}
		tmp[lvl]->top=1;tmp[0]->size=1;
		update(lvl);
	}
	void del(int key){
		node *x=find(key);
		if (x->key!=key)return;x=NULL;
		for (int i=0;i<=10;++i){
			if (last[i]->d!=x)break;x=last[i];
			x->r->l=x->l;x->l->r=x->r;
		}
		update(0);
	}
	node *findkth(int k){
		register node *x=root;
		while (k){
			if (x->r->top&&x->d->size<k)k-=x->d->size,x=x->r;
				else {if (!x->d)break;x=x->d;}
		}
		return x;
	}
	void print(){
		node *x=root,*y;
		for (int i=0;i<=level;++i){
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
int main()
{
	int t1=clock();
	long long n,A,b,c,m,i,tmp,key,ans=1;
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	Exp=(int)(32768/pow(2,1.0/Maxlevel*log2(n)));
	a.insert(1);
	for (i=2;i<=n;++i){
		if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
		m=a.findkth(tmp)->key;
		key=(A*m+b*i+c)%1000000007;
		a.insert((int)key);
		ans+=key;
	}
	printf("%I64d\n",ans);
	//printf("time=%d\n",clock()-t1);
	//system("pause");for (;;);
}




