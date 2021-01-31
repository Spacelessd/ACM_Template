#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct RBtree{
	#define black 0
	#define red 1
	struct node{
		node *l,*r,*p;
		int key,size,color;
		void update(){
			size=l->size+r->size+1;
		}
	};
	node a[N];
	int len;node *root,*null;
	void clear(){
		len=0;root=null=new node;
		null->l=null->r=null->p=null;
		null->size=0;null->color=black;
	}
	RBtree(){clear();}
	node *newnode(int key){
		node *x=a+(++len);
		x->l=x->r=x->p=null;
		x->size=1;x->color=red;
		x->key=key;return x;
	}
	void zig(node *x){
		node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else z->r=x;
		x->p=z;y->p=x;y->l=x->r;
		x->r=y;y->l->p=y;
		y->update();x->update();
	}
	void zag(node *x){
		node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else z->r=x;
		x->p=z;y->p=x;y->r=x->l;
		x->l=y;y->r->p=y;
		y->update();x->update();
	}
	void insert(node *&root,int key){
		node *x=root,*y=null,*fa=root->p,*z=newnode(key);
		while (x!=null){
			++(y=x)->size;
			if (key<x->key)x=x->l;
				else x=x->r;
		}
		z->p=y;
		if (key<y->key)y->l=z;
			else y->r=z;
		x=z;
		while (1){
			y=x->p;
			if (y==fa){root=x;x->color=black;return;}
			if (y->color==black)return;
			z=y->p;
			if (x==y->r&&y==z->l)zag(x),zig(x),y->color=black;
			else if (x==y->l&&y==z->r)zig(x),zag(x),y->color=black;
			else if (x==y->l&&y==z->l)zig(y),x->color=black,x=y;
			else if (x==y->r&&y==z->r)zag(y),x->color=black,x=y;
		}
	}
	void del(node *&root,int key){
		
	}
	node *find(node *x,int key){
		if (x==null)return null;
		if (key==x->key)return x;
		if (key<x->key)return find(x->l,key);
		else return find(x->r,key);
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
RBtree a;
int main()
{
	int t1=clock();
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
	//printf("%d\n",clock()-t1);
	//system("pause");for (;;);
	return 0;
}




