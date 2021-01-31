#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 12000010
struct node{
		int key,fix,size;
		node *l,*r;
		node(int _key,int _fix,node *_l,node *_r):
			key(_key),fix(_fix),l(_l),r(_r){update();}
		node(){}
		void update(){
			size=1;
			if (l)size+=l->size;
			if (r)size+=r->size;
		}
	};
node A[N];int a1;
node *New(int _key,int _fix,node *_l,node *_r){
		++a1;A[a1].key=_key;A[a1].fix=_fix;A[a1].l=_l;A[a1].r=_r;
		(A+a1)->update();return A+a1;
	}
struct Treap{
	node *root;
	Treap():root(NULL){srand(time(0));a1=0;}
	node *newnode(int key){
		return New(key,rand(),NULL,NULL);
	}
	node *merge(node *x,node *y){
		return (!x||!y)?(x?x:y):
			(x->fix<y->fix?New(x->key,x->fix,x->l,merge(x->r,y)):
				New(y->key,y->fix,merge(x,y->l),y->r));
	}
	node *split_l(node *x,int key){
		return !x?NULL:(x->key<=key?
			New(x->key,x->fix,x->l,split_l(x->r,key)):
			split_l(x->l,key));
	}
	node *split_r(node *x,int key){
		return !x?NULL:(x->key>key?
			New(x->key,x->fix,split_r(x->l,key),x->r):
			split_r(x->r,key));
	}
	node *del(node *x,int key){
		node *L=split_l(x,key),*tmp=merge(L?L->l:NULL,split_r(x,key));
		if (tmp) tmp->update();
		return tmp;
	}
	node *remove(node *x,int key){
		return merge(split_l(x,key-1),split_r(x,key));
	}
	node *insert(node *x,int key){
		return merge(merge(split_l(x,key),newnode(key)),split_r(x,key));
	}
	node* findkth(node *root,int k){
        node *x=root;int S;
        while (k){
			S=x->l?x->l->size:0;
            if (k==S+1) break;
		    if (k<=S) x=x->l;
				else k-=S+1,x=x->r;			
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
	long long n,A,b,c,m,tmp,key,ans=1;
    freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
    scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
    a.root=a.insert(a.root,1);
    for (int i=2;i<=n;++i){
        if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
        m=a.findkth(a.root,tmp)->key;
        key=(A*m+b*i+c)%1000000007;
        a.root=a.insert(a.root,(int)key);
        ans+=key;
        }
    printf("%I64d\n",ans);
    //system("pause");for (;;);
}
