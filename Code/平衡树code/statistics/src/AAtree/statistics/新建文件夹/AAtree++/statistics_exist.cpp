#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct AAtree{
	struct node{
		node *l,*r; int key,level,size,exist;
		void update(){
			size=l->size+r->size+exist;
		}
	};
	node a[N],*root,*null;int len;
	void clear(){
		len=0;root=null=new node;
		null->l=null->r=null;null->level=0;null->size=0;
	}
	AAtree(){clear();}
	node *newnode(int key){
		node *x=a+(++len);x->l=x->r=null;
		x->size=1;x->key=key;x->level=1;x->exist=1;
		return x;
	}
	node *LeftRotate(node *x){
		node *y=x->l;x->l=y->r;y->r=x;
		x->update();return y;
	}
	node *RightRotate(node *x){
		node *y=x->r;x->r=y->l;y->l=x;
		x->update();return y;
	}
	void Skew(node *&x){if (x->l->level==x->level)x=LeftRotate(x);}
	void Split(node *&x){
		if (x->r->r->level==x->level)
			x=RightRotate(x),++x->level;
	}
	node *find(node *x,int key){
		while (x!=null)
			if (key<x->key)x=x->l;
				else if (key>x->key)x=x->r;
					else break;
		return x;
	}
	void insert(node *&x,int key){
		if (x==null){x=newnode(key);return;}
		if (key<x->key)insert(x->l,key);
			else insert(x->r,key);
		Skew(x);Split(x);x->update();
	}
	void del(node *&x,int key){
		if (x==null)return;
		if (x->key==key){x->size-=x->exist;x->exist=0;return;}
		if (key<x->key)del(x->l,key);
			else del(x->r,key); 
	}
	node *findkth(node *root,int k){
		node *x=root;
		while (k){
			if (x->exist&&k==x->l->size+x->exist) break;
			if (k<=x->l->size) x=x->l;
				else {k-=x->l->size+x->exist;x=x->r;}
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
AAtree a;
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
		key=(A*m+b*i+c)%1000000007;ans+=key;
		a.insert(a.root,(int)key);
		a.del(a.root,(int)key);
		a.insert(a.root,(int)key);
	}
	printf("%I64d\n",ans);
	//printf("%d\n",clock()-t1);
	//system("pause");for (;;);
	return 0;
}


