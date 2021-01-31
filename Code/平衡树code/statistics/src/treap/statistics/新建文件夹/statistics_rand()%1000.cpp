#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct treap{
	#define oo (1<<30)
	struct node{
		node *l,*r;int key,fix,size;
		void update(){
			size=l->size+r->size+1;
		}
	};
	node a[N],*root,*null;int len;
	void clear(){
		srand(time(0));len=0;root=null=new node;
		null->l=null->r=null;null->size=0;null->fix=oo;
	}
	treap(){clear();}
	node *newnode(int key){
		node *x=a+(++len);x->l=x->r=null;
		x->size=1;x->key=key;x->fix=rand()%1000;
		return x;
	}
	void zig(node *&x){
		node *y=x->l;x->l=y->r;y->r=x;
		x->update();y->update();x=y;
	}
	void zag(node *&x){
		node *y=x->r;x->r=y->l;y->l=x;
		x->update();y->update();x=y;
	}
	void insert(node *&x,int key){
		if (x==null)x=newnode(key);
		else
		if (key<=x->key){
			insert(x->l,key);++x->size;
			if (x->l->fix<x->fix)zig(x);
		}
		else if (key>x->key){
			insert(x->r,key);++x->size;
			if (x->r->fix<x->fix)zag(x);
		}
	}
	node *find(node *x,int key){
		if (x==null)return null;
		if (key==x->key)return x;
		if (key<x->key)return find(x->l,key);
		else return find(x->r,key);
	}
	void del(node *&x,int key){
		if (x==null)return;
		if (x->key==key)
			if (x->l==null||x->r==null)
				if (x->l==null)x=x->l;
					else x=x->r;
			else if (x->l->fix<x->r->fix)
				zig(x),del(x->r,key),x->update();
				else zag(x),del(x->l,key),x->update();
		else if (key<x->key)del(x->l,key);
			else del(x->r,key);
	}
	node *findkth(node *root,int k){
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
		if (x==null) return;
		print(x->l);
		printf("nie %d\n",x->key);
		print(x->r);
	}
};
treap a;
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
	system("pause");
	return 0;
}


