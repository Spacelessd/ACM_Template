#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000010
struct Treap{
	struct node{
		int key,fix,size;
		node *l,*r;
		node(int _key,int _fix,node *_l,node *_r):
			key(_key),fix(_fix),l(_l),r(_r){}
		void update(){size=l->size+r->size+1;}
	};
	node *root;
	Treap():root(NULL){srand(time(0));}
	node *newnode(int key){
		return new node(key,rand(),NULL,NULL);
	}
	node *merge(node *x,node *y){
		return (!x||!y)?(x?x:y):
			(x->fix<y->fix?new node(x->key,x->fix,x->l,merge(x->r,y)):
				new node(y->key,y->fix,merge(y->l,x),y->r));
	}
	node *split_l(node *x,int key){
		return !x?NULL:(x->key<key?
			new node(x->key,x->fix,x->l,split_l(x->r,key)):
			split_l(x->l,key));
				
	}
	node *split_r(node *x,int key){
		return !x?NULL:(x->key>key?
			new node(x->key,x->fix,split_r(x->l,key),x->r):
			split_r(x->r,key));
				
	}
	node *del(node *x,int key){
		return merge(split_l(x,key),split_r(x,key));
	}
	node *insert(node *x,int key){
		return merge(merge(split_l(x,key),newnode(key)),split_r(x,key));
	}
	node* findkth(node *&root,int k){
        node *x=root;
        while (k){
              if (k==x->l->size+1) break;
		      if (k<=x->l->size) x=x->l;
			     else {k-=x->l->size+1;x=x->r;}			
        }
	    return x;
    }
	void print(node *x){
		if (x==NULL)return;
		print(x->l);
		printf("%d\n",x->key);
		print(x->r);
	}
};
Treap a;
#include<algorithm>
int T[N];
int main(){
	int n=100000;
	for (int i=1;i<=n;++i)T[i]=rand();
	for (int i=1;i<=n;++i)a.root=a.insert(a.root,T[i]);
	//a.print(a.root);
	//std::sort(T+1,T+1+n);
	//for (int i=1;i<=n;++i)printf("T %d\n",T[i]);
	system("pause");
}


