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
	static node *update[Maxlevel+2],*tmp[Maxlevel+2],*tmp1[Maxlevel+2];
	node *root;
	void clear(){
		int lvl=1;
		tmp[lvl]=new node,tmp[lvl]->key=-oo;
		tmp1[lvl]=new node,tmp1[lvl]->key=oo;
		tmp[lvl-1]=tmp[lvl+1]=tmp1[lvl-1]=tmp1[lvl+1]=NULL;
		tmp[lvl]->r=tmp1[lvl];tmp1[lvl]->l=tmp[lvl];
		tmp[lvl]->u=tmp[lvl+1];tmp[lvl]->d=tmp[lvl-1];
		tmp1[lvl]->u=tmp1[lvl+1];tmp1[lvl]->d=tmp1[lvl-1];
		root=tmp[lvl];root->level=lvl;
	}
	int Rand(){
		static int x=12347;
		x=(x*1001+333)%100007;
		return x&32767;
	}
	int RandLevel(){
		int lvl=1;
		while (Rand()<exp*32768&&lvl<Maxlevel)++lvl;
		if (lvl>root->level){
			for (int i=root->level+1;i<=lvl;++i)tmp[i]=new node,tmp[i]->key=-oo;
			for (int i=root->level+1;i<=lvl;++i)tmp1[i]=new node,tmp1[i]->key=oo;
			tmp[root->level]=root;tmp1[root->level]=root->r;
			while (tmp1[root->level]->r!=NULL)tmp1[root->level]=tmp1[root->level]->r;
			tmp[lvl+1]=tmp1[lvl+1]=NULL;
			for (int i=root->level+1;i<=lvl;++i){
				tmp[i]->r=tmp1[i];tmp1[i]->l=tmp[i];
				tmp[i]->u=tmp[i+1];tmp[i]->d=tmp[i-1];
				tmp1[i]->u=tmp1[i+1];tmp1[i]->d=tmp1[i-1];
			}
			for (int i=root->level+1;i<=lvl;++i) update[i]=tmp[i];  
			root=tmp[lvl];root->level=lvl;
		}
		return lvl;
	}
	void find(int key){
		node *x=root;int i=root->level;
		while (x){
			if (x->r->key<=key)x=x->r;
			else update[i--]=x,x=x->d;
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
		lvl=root->level;
		while (lvl>1&&root->r->r==NULL)--lvl,root=root->d;
		root->level=lvl;
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
node* SkipList::update[Maxlevel+2];
node* SkipList::tmp[Maxlevel+2];
node* SkipList::tmp1[Maxlevel+2];
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




