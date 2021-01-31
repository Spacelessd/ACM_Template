#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
struct DynamicTree{
	public:
	struct node{
		int key,size,min;
		node *l,*r,*p;
	};
	node a[100010],*root,*null;
	int len;
	void clear()
	{
		null=new node;null->size=0;null->min=oo;
		len=0;root=null;
	}
	DynamicTree(){clear();}	
	node *newnode(int key)
	{
		node *x=&a[++len];
		x->l=x->r=x->p=null;
		x->size=1;x->key=key;
		return x;
	}
	void update(node *x)
	{
		x->size=x->l->size+x->r->size+1;
		x->min=x->key;
		if (x->l&&x->l->min<x->min)x->min=x->l->min;
		if (x->r&&x->r->min<x->min)x->min=x->r->min;
	}
	void zig(node *x)
	{
		node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else z->r=x;
		x->p=z;y->p=x;
		y->l=x->r;x->r=y;
		y->l->p=y;
		update(y);
	}
	void zag(node *x)
	{
		node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else z->r=x;
		x->p=z;y->p=x;
		y->r=x->l;x->l=y;
		y->r->p=y;
		update(y);
	}
	void splay(node *root,node *x)
	{
		node *y,*z,*fa=root->p;
		if (x==null) return;
		while (x->p!=fa){
			y=x->p;z=y->p;
			if (z==fa) {if (x==y->l)zig(x);else zag(x);}
			else
				if (y==z->l)
					if (x==y->l){zig(y);zig(x);}
					else{zag(x);zig(x);}
				else 
					if (x==y->r){zag(y);zag(x);}
					else{zig(x);zag(x);}
		}
		update(x);root=x;
	}
	int rank(node *x){
		splay(x);return x->l->size+1;
	}
	
};
DynamicTree a;
int n,i;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	
	system("pause");
	return 0;
}


