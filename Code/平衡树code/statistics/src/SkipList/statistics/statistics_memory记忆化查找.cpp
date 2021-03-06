#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
#define exp 0.5
#define Maxlevel 20
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
	#define memory
	static node *last[Maxlevel+2],*tmp[Maxlevel+2],*tmp1[Maxlevel+2],*path[Maxp];
	int level,p1,Pkey,Plvl;node *root;
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
		root=tmp[lvl];level=lvl;p1=1;path[p1]=root;Plvl=lvl;
	}
	SkipList(){clear();}
	int Rand(){
		static int x=12347;
		x=(x<<5)+(x>>2)+1;
		return x&32767;
	}
	int RandLevel(){
		int lvl=1;
		while (Rand()<exp*32768&&lvl<Maxlevel)++lvl;
		return lvl;
	}
	node *find(int key){
		node *x=root;int lvl=level;p1=0;
		while (x){
			path[++p1]=x;
			if (x->r->key<=key)x=x->r;
				else last[lvl--]=x,x=x->d;
		}
		return last[0];
	}
	node *find1(int key){
		int lvl=Plvl;
		if (key>=Pkey)
			while (p1>1&&path[p1]->r->key<=key){
				if (path[p1-1]->d==path[p1])++lvl;--p1;
		}
		else
			while (p1>1&&path[p1]->key>=key){
				if (path[p1-1]->d==path[p1])++lvl;--p1;
		}
		node *x=path[p1--];
		while (x){
			path[++p1]=x;
			if (x->r->key<=key)x=x->r;
				else last[lvl--]=x,x=x->d;
		}
		Pkey=key;Plvl=lvl+1;
		return last[0];
	}
	void update(int lvl){
		for (int i=1;i<=lvl;++i)
			tmp[i]->update();
		for (int i=p1-1;i;--i)
			path[i]->update();
	}
	void insert(int key){
		#ifdef memory
		find1(key);
		#else
		find(key);
		#endif
		int lvl=RandLevel();
		for (int i=0;i<=lvl;++i)tmp[i]=NewNode(),tmp[i]->key=key,tmp[i]->top=0;
		for (int i=0;i<=lvl;++i){
			tmp[i]->r=last[i]->r;last[i]->r->l=tmp[i];
			last[i]->r=tmp[i];tmp[i]->l=last[i];
			if (!i)tmp[i]->d=NULL;
				else tmp[i]->d=tmp[i-1];
		}
		tmp[lvl]->top=1;tmp[0]->size=1;
		update(lvl);
	}
	void del(int key){
		node *x=find(key);
		if (x->key!=key)return;x=NULL;
		for (int i=0;i<=level;++i){
			if (last[i]->d!=x)break;x=last[i];
			if (path[p1-1]->d==path[p1])++Plvl;--p1;
			x->r->l=x->l;x->l->r=x->r;
		}
		update(0);
	}
	node *findkth(int k){
		node *x=root;
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
	a.insert(1);
	for (i=2;i<=n;++i){
		if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
		m=a.findkth(tmp)->key;
		key=(A*m+b*i+c)%1000000007;
		a.insert((int)key);a.del((int)key);a.insert((int)key);
		ans+=key;
	}
	printf("%I64d\n",ans);
	//printf("time=%d\n",clock()-t1);
	//system("pause");for (;;);
}


