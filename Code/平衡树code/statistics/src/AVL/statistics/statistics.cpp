#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct AVL{
	struct node{
		int size,key,h;
		node *l,*r,*p;
		void renewh(){h=l->h>r->h?l->h+1:r->h+1;}
		void update(){
			renewh(); size=l->size+r->size+1;
		}
	};
	node a[N],*root,*null; int len;
	void clear(){
		len=0; root=null=new node;
		null->l=null->r=null->p=null;
		null->h=null->size=0;
	}
	AVL(){clear();}
	node *newnode(int key){
		node *x=a+(++len); x->l=x->r=x->p=null;
		x->size=1; x->key=key; x->h=1;
		return x;
	}
	void zig(node *x){
		node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else z->r=x;
		x->p=z;y->p=x;y->l=x->r;x->r=y;y->l->p=y;
		y->update();x->update();
	}
	void zag(node *x){
		node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else z->r=x;
		x->p=z;y->p=x;y->r=x->l;x->l=y;y->r->p=y;
		y->update();x->update();
	}
	void insert(node *&x,int key){
		node *y; if (x==null){x=newnode(key);return;}
		if (key<x->key){
			insert(x->l,key);x->l->p=x;
			if (x->l->h-x->r->h>1){
				if (key<x->l->key){y=x->l;zig(y);x=y;}
					else {y=x->l->r;zag(y);zig(y);x=y;}
			}else x->update();
		}
		else {
			insert(x->r,key);x->r->p=x;
			if (x->r->h-x->l->h>1){
				if (key>=x->r->key){y=x->r;zag(y);x=y;}
					else {y=x->r->l;zig(y);zag(y);x=y;}
			}else x->update();
		}
	}
	void del(node *&root,int key){
		if (root==null)return;
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
		printf("nie %d %d %d %d\n",x->key,x->l->key,x->r->key,x->p->key);
		print(x->r);
	}
};
AVL a;
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
		a.insert(a.root,(int)key); ans+=key;
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


