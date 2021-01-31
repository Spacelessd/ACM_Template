#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct Splay{
#define oo (1<<30)
    struct node{
		int key,size;
		node *l,*r,*p;
		void update(){
             size=l->size+r->size+1;
		}
    };
    node a[200010];
	node *null,*root;
	int len;
	void clear(){
		null=new node;null->l=null->r=null;
		null->size=0;null->key=-oo;
		len=0;root=null;
    }
    Splay(int n=5){
        n+=5;clear();
	}
    node* newnode(int key){
        node *p=a+(++len);
		p->l=p->r=p->p=null;
        p->size=1;p->key=key;
        return p;
    }
	void zig(node *x){
        node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else z->r=x;
		x->p=z;y->p=x;
		y->l=x->r;x->r=y;
		y->l->p=y;
		y->update();
	}
    void zag(node *x){
        node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else z->r=x;
		x->p=z;y->p=x;
		y->r=x->l;x->l=y;
		y->r->p=y;
		y->update();
	}
	void splay(node *x){
        node *y,*z,*fa=root->p;
        if (x==null) return;
		while (x->p!=fa){
            y=x->p;z=y->p;
			if (z==fa) if (x==y->l)zig(x);else zag(x);
			else
				if (y==z->l)
					if (x==y->l)zig(y),zig(x);
					else zag(x),zig(x);
				else 
					if (x==y->r)zag(y),zag(x);
					else zig(x),zag(x);
		}
		x->update();root=x;
	}
	void insert(int key)
	{
       node *x=root,*y=null,*z=newnode(key);
       if (root==null){root=z;return;}
       while (x->size){
             ++(y=x)->size;
             if (z->key<x->key)x=x->l;
               else x=x->r;
             }
       z->p=y;
       if (z->key<y->key)y->l=z;
         else y->r=z;
       //splay(z);
	}
	node* findkth(int k){
        node *x=root;
        while (k){
              if (k==x->l->size+1) break;
		      if (k<=x->l->size) x=x->l;
			     else k-=x->l->size+1,x=x->r;
        }
	    //splay(x);
		return x;
    }
};
Splay a;
int main()
{
    long long n,A,b,c,m,i,tmp,key,ans=1;
    freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
    scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
    a.insert(1);
    for (i=2;i<=n;++i){
        if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
        m=a.findkth(tmp)->key;
        key=(A*m+b*i+c)%1000000007;
        a.insert((int)key);
        //printf("%d %d %d\n",i,m,A*m+b*i+c);
        ans+=key;
        //print(a.root);
        }
    printf("%I64d\n",ans);
    //system("pause");
}










