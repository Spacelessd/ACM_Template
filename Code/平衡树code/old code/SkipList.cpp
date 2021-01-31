#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
#define exp 0.5
#define Maxlevel 30
int state,sum,ans;
struct node{
	node *l,*r,*u,*d;
	int key,level;
	node():l(NULL),r(NULL),u(NULL),d(NULL){}
};
struct SkipList{
	static node *update[Maxlevel+1],*tmp[Maxlevel+1],*tmp1[Maxlevel+1];
	node *root;
	void clear(){
		int lvl=Maxlevel;
		for (int i=1;i<=lvl;++i)tmp[i]=new node,tmp[i]->key=-oo;
		for (int i=1;i<=lvl;++i)tmp1[i]=new node,tmp1[i]->key=oo;
		tmp[0]=tmp[lvl+1]=tmp1[0]=tmp1[lvl+1]=NULL;
		for (int i=1;i<=lvl;++i){
			tmp[i]->r=tmp1[i];tmp1[i]->l=tmp[i];
			tmp[i]->u=tmp[i+1];tmp[i]->d=tmp[i-1];
			tmp1[i]->u=tmp1[i+1];tmp1[i]->d=tmp1[i-1];
		}
		root=tmp[lvl];root->level=lvl;
		tmp[1]->level=tmp1[1]->level=lvl;
	}
	int Rand(){
		static int nie=12347;
		nie=(nie*1001+333)%100007;
		return nie&32767;
	}
	int RandLevel(){
		int lvl=1;
		while (Rand()<exp*32768)++lvl;
		return lvl>Maxlevel?Maxlevel:lvl;
	}
	void find(int key){
		node *x=root;
		for (int i=root->level;i;--i){
			while (x->r->key<key)x=x->r;
			update[i]=x;x=x->d;
		}
	}
	void ins(int key){
		++sum;find(key);
		int lvl=RandLevel();
		for (int i=1;i<=lvl;++i)tmp[i]=new node,tmp[i]->key=key;
		tmp[lvl+1]=NULL;
		for (int i=1;i<=lvl;++i){
			tmp[i]->r=update[i]->r;update[i]->r->l=tmp[i];
			update[i]->r=tmp[i];tmp[i]->l=update[i];
			tmp[i]->u=tmp[i+1];tmp[i]->d=tmp[i-1];
		}
		tmp[1]->level=lvl;
	}
	void del(int key){
		--sum;find(key);node *x;
		if (key-update[1]->key<=update[1]->r->key-key)
			ans=(ans+key-update[1]->key)%1000000,x=update[1];
			else ans=(ans+update[1]->r->key-key)%1000000,x=update[1]->r;
		int lvl=x->level;
		for (int i=1;i<=lvl;++i){
			x->r->l=x->l;x->l->r=x->r;x=x->u;
		}
	}
	void print(){
		node *x=root,*y;
		for (int i=1;i<=root->level;++i){
			y=x;while (y!=NULL)printf("%d * ",y->key),y=y->r;
			printf("\n");x=x->d;
		}
		printf("end\n");
	}
};
node* SkipList::update[Maxlevel+1];
node* SkipList::tmp[Maxlevel+1];
node* SkipList::tmp1[Maxlevel+1];
SkipList a;
void init(){
	//srand(time(0));
	ans=0;sum=0;a.clear();
}
int main()
{
	freopen("pet.in","r",stdin);
	freopen("pet.out","w",stdout);
	int ch,n,x;scanf("%d",&n);
	init();
	for (int i=1;i<=n;++i){
		scanf("%d%d",&ch,&x);
		if (!sum)state=ch;
		if (ch==state)a.ins(x);
			else a.del(x);
		//a.print();
	}
	printf("%d\n",ans);
	//system("pause");for (;;);
	return 0;
}


