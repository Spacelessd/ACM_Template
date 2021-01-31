#include<stdio.h>
#include<map>
template <class Tkey,class Tvalue>
struct Map{
    struct node{
		Tkey key;Tvalue value;
		node *l,*r,*p;
    };
    node *null;
    void clear(){
        null=new node;null->l=null->r=null;
		null->key=-oo;
    }
    void zig(node *x){
        node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else if (z->r==y)z->r=x;
		x->p=z;y->p=x;
		y->l=x->r;x->r=y;
		y->l->p=y;
		y->update();
	}
    void zag(node *x){
        node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else if (z->r==y)z->r=x;
		x->p=z;y->p=x;
		y->r=x->l;x->l=y;
		y->r->p=y;
		y->update();
	}
	void splay(node *x)
	{
        node *y,*z;
        static node* stack[maxn];int top=0;
        if (x==null) return;
        for (node *q=x;;q=q->p){stack[++top]=q;if (isroot(q))break;}
        while (top)down(stack[top--]);
		while (!isroot(x)){
            y=x->p;z=y->p;
			if (isroot(y)) {if (x==y->l)zig(x);else zag(x);}
			else
				if (y==z->l)
					if (x==y->l){zig(y);zig(x);}
					else{zag(x);zig(x);}
				else 
					if (x==y->r){zag(y);zag(x);}
					else{zig(x);zag(x);}
		}
		x->update();
	}
};
Map<int,int> a;
int main(){
    
}


