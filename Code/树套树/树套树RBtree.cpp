#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
#define M 1000005
#define N 10000005
#define black 0
#define red 1
struct node{
	node *l,*r,*p;
	int key,size,color;
	void update(){
		size=l->size+r->size+1;
	}
};
node a[N],*null;int len;
void clear(){
	len=0;null=new node;
	null->l=null->r=null->p=null;
	null->size=0;null->color=black;
}
struct RBtree{
	node *root;
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
		if (root==null){root=z;root->color=black;return;}
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
	int query(int key){
		int ans=0;
		for (node *x=root;x!=null;)
			if (x->key>=key)ans+=x->r->size+1,x=x->l;
			else x=x->r;
		return ans;
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
RBtree T[M];
struct Qnode{
	int key,p;
};
Qnode A[M];int A1=0,s=0;
bool cmp(const Qnode i,const Qnode j){return i.key<j.key;}
int x[M],y[M],n; char c[M];
void add(int x,int y){for (;x<=s;x+=x&-x) T[x].insert(T[x].root,y);}
int get(int x,int y){int res=0; for (;x;x-=x&-x)res+=T[x].query(y); return res;}
void read(int &x){
	char ch; x=0;
	for (ch=getchar();ch<'0' || ch>'9';ch=getchar());
	for (;ch>='0' && ch<='9';x=x*10+ch-48,ch=getchar());
}
int main()
{
	int t1=clock();
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	read(n);clear();
	for (int i=1;i<=n;++i){
		char ch=getchar(); while (ch!='+' && ch!='?') ch=getchar(); c[i]=ch;
		read(x[i]);read(y[i]);A[++A1].key=x[i];A[A1].p=i;
	}
	std::sort(A+1,A+1+A1,cmp);A[0].key=-1;
	for (int i=1;i<=A1;++i){
		if (A[i].key!=A[i-1].key)++s; x[A[i].p]=s;
	}
	for (int i=1;i<=s;++i)T[i].root=null;
	for (int i=1;i<=n;++i)
		if (c[i]=='+') add(x[i],y[i]);
		else printf("%d\n",get(x[i],y[i]));
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


