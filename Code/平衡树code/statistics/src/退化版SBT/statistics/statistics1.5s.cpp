#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct SBT{
	struct node{
		node *l,*r;
		int key,size;
		void update(){
			size=l->size+r->size+1;
		}
	};
	node a[N];
	int len;node *root,*null;
	void clear(){
		len=0;root=null=new node;
		null->l=null->r=null;
		null->key=null->size=0;
	}
	SBT(){clear();}
	node *newnode(int key){
		node *x=a+(++len);
		x->l=x->r=null;
		x->size=1;x->key=key;
		return x;
	}
	void left_rotate(node *&x){
		node *y=x->r;
		x->r=y->l;y->l=x;
		x->update();y->update();x=y;
	}
	void right_rotate(node *&x){
		node *y=x->l;
		x->l=y->r;y->r=x;
		x->update();y->update();x=y;
	}
	void insert(node *&x,int key){
		if (x==null)x=newnode(key);
		else {
			++x->size;
			if (key<x->key){
				insert(x->l,key);
				if (x->l->l>x->r)right_rotate(x);
			}
			else {
				insert(x->r,key);
				if (x->r->r>x->l)left_rotate(x);
			}
		}
	}
	int del(node *&x,int key){
		--x->size;
		if (key==x->key||key<x->key&&x->l==null
		||key>x->key&&x->r==null){
			int tmp=x->key;
			if (x->l==null)x=x->r;
				else if (x->r==null)x=x->l;
					else x->key=del(x->l,x->key+1);
			return tmp;
		}
		else
			if (key<x->key)return del(x->l,key);
			else return del(x->r,key);
	}
	node *findkth(node *&root,int k){
		node *x=root;
		while (k){
			if (k==x->l->size+1) break;
			if (k<=x->l->size) x=x->l;
				else {k-=x->l->size+1;x=x->r;}
		}
		return x;
	}
	node *fmin(node *x){while (x->l!=null)x=x->l;return x;}
	node *fmax(node *x){while (x->r!=null)x=x->r;return x;}
	void print(node *x){
		if (x==null)return;
		print(x->l);
		printf("nie %d\n",x->key);
		print(x->r);
	}
};
SBT a;
int main()
{
	long long n,A,b,c,m,i,tmp,key,ans=1;
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	a.insert(a.root,1);
	for (i=2;i<=n;++i){
		if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
		m=a.findkth(a.root,tmp)->key;
		key=(A*m+b*i+c)%1000000007;
		a.insert(a.root,(int)key);
		ans+=key;
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


