#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct Pairing_Heap{
	#define N 1000005
	struct node{
		node *l,*r,*pre;
		int key;
	};
	node tree[N],*tmp[N],*Null;
	node *root;int len;
	void clear(){
		len=0;tmp[0]=root=Null=new node;
		Null->key=1<<30;Null->l=Null->r=Null->pre=Null;
	}
	Pairing_Heap(){clear();}
	node *Newnode(int key){
		node *p=tree+(++len);
		p->key=key;p->l=p->r=p->pre=Null;
		return p;
	}
	node *link(node *a,node *b){
		if (a->key>b->key) {node *tmp=a;a=b;b=tmp;}
		if (b==Null)return a;
		b->r=a->l;a->l->pre=b;
		a->l=b;b->pre=a;
		return a;
	}
	node *combine(node *x){
		int total=0,i;node *y,*z;
		for (x->pre=Null;x!=Null;x=z){
			y=x->r,z=y->r;
			x->r=y->r=y->pre=z->pre=Null;
			tmp[++total]=link(x,y);
		}
		for (x=tmp[total],i=total-1;i>0;--i)x=link(x,tmp[i]);
		return x;
	}
	void insert(node *x){root=link(x,root);}
	node *pop(){
		node *tmp=root;
		root=combine(root->l);
		return tmp;
	}
	void decreasekey(node *x,int key){
		x->key=key;
		if (x!=root){
			x->r->pre=x->pre;
			if (x->pre->l!=x)x->pre->r=x->r;
				else x->pre->l=x->r;
			x->r=x->pre=Null;
			root=link(x,root);
		}
	}
	void insert(int key){node *x=Newnode(key);insert(x);}
	void del(node *x){decreasekey(x,-2147483647);pop();}
	void merge(Pairing_Heap *x){root=link(root,x->root);}
	int top(){return root->key;}
	bool empty(){return root==Null;}
	#undef N
};
Pairing_Heap a1;
struct Pairing_Heap1{
	#define N 1000005
	struct node{
		node *l,*r,*pre;
		int key;
	};
	node tree[N],*tmp[N],*Null;
	node *root;int len;
	void clear(){
		len=0;tmp[0]=root=Null=new node;
		Null->key=-(1<<30);Null->l=Null->r=Null->pre=Null;
	}
	Pairing_Heap1(){clear();}
	node *Newnode(int key){
		node *p=tree+(++len);
		p->key=key;p->l=p->r=p->pre=Null;
		return p;
	}
	node *link(node *a,node *b){
		if (a->key<b->key) {node *tmp=a;a=b;b=tmp;}
		if (b==Null)return a;
		b->r=a->l;a->l->pre=b;
		a->l=b;b->pre=a;
		return a;
	}
	node *combine(node *x){
		int total=0,i;node *y,*z;
		for (x->pre=Null;x!=Null;x=z){
			y=x->r,z=y->r;
			x->r=y->r=y->pre=z->pre=Null;
			tmp[++total]=link(x,y);
		}
		for (x=tmp[total],i=total-1;i>0;--i)x=link(x,tmp[i]);
		return x;
	}
	void insert(node *x){root=link(x,root);}
	node *pop(){
		node *tmp=root;
		root=combine(root->l);
		return tmp;
	}
	void decreasekey(node *x,int key){
		x->key=key;
		if (x!=root){
			x->r->pre=x->pre;
			if (x->pre->l!=x)x->pre->r=x->r;
				else x->pre->l=x->r;
			x->r=x->pre=Null;
			root=link(x,root);
		}
	}
	void insert(int key){node *x=Newnode(key);insert(x);}
	void del(node *x){decreasekey(x,-2147483647);pop();}
	void merge(Pairing_Heap1 *x){root=link(root,x->root);}
	int top(){return root->key;}
	bool empty(){return root==Null;}
	#undef N
};
Pairing_Heap1 a;
int main()
{
	long long n,A,b,c,key,ans=1;
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	a.insert(1);
	for (int i=2;i<=n;++i){
		key=(A*a.top()+b*i+c)%1000000007;
		if (i&1)a.insert(key);
			else a1.insert(key);
		while (a.top()>a1.top()){
			int tmp1=a.top(),tmp2=a1.top();
			a.pop();a1.pop();
			a.insert(tmp2);a1.insert(tmp1);
		}
		ans+=key;
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


