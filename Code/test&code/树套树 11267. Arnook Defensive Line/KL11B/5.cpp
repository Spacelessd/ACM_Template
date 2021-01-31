#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
#define M 1000005
#define N 10000005
#define oo (1<<30)
struct node{
	int key,size;
	node *l,*r,*p;
	void update(){
		size=l->size+r->size+1;
	}
};
node a[N],*null;int len;
void clear(){
	null=new node;null->l=null->r=null;
	null->size=0;null->key=-oo;len=0;
}
struct Splay{
	node *root;
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
	void splay(node *&root,node *x){
		node *y,*z,*fa=root->p;
		if (x==null) return;
		while (x->p->size){
			y=x->p;z=y->p;
			if (!z->size) if (x==y->l)zig(x);else zag(x);
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
	void insert(node *&root,int key){
		node *x=root,*y=null,*z=newnode(key);
		if (root==null){root=z;return;}
		while (x->size){
			y=x;
			if (z->key<x->key)x=x->l;
				else x=x->r;
		}
		z->p=y;
		if (z->key<y->key)y->l=z;
			else y->r=z;
		splay(root,z);
	}
	node *findkth(node *&root,int k){
		node *x=root;
		while (k){
			if (k==x->l->size+1) break;
			if (k<=x->l->size) x=x->l;
				else {k-=x->l->size+1;x=x->r;}
		}
		splay(root,x);return x;
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
		if (x==NULL)return;
		print(x->l);
		printf("nie %d\n",x->key);
		print(x->r);
	}
};
Splay T[M];
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
	freopen("1.in","r",stdin);
	freopen("5.out","w",stdout);
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
	//system("pause");
	return 0;
}


