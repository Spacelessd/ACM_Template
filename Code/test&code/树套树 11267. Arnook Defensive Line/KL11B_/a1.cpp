#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
#define M 1000005
#define N 10000005
#define oo (1<<30)
struct node{
	node *l,*r;int key,fix,size;
	void update(){
		size=l->size+r->size+1;
	}
};
node a[N],*null;int len;
void clear(){
	srand(time(0));null=new node;
	null->l=null->r=null;null->size=0;null->fix=oo;
}
struct treap{
	node *root;
	node *newnode(int key){
		node *x=a+(++len);x->l=x->r=null;
		x->size=1;x->key=key;x->fix=rand()*32768+rand();
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
	int findkth(node *root,int k){
		node *x=root;
		while (k){
			if (k==x->l->size+1) break;
			if (k<=x->l->size) x=x->l;
				else {k-=x->l->size+1;x=x->r;}
		}
		return x->key;
	}
	int query(int key){
		int ans=0;
		for (node *x=root;x!=null;)
			if (x->key>=key)ans+=x->r->size+1,x=x->l;
			else x=x->r;
		return ans;
	}
	node *fmin(node *x){while (x->l)x=x->l;return x;}
	node *fmax(node *x){while (x->r)x=x->r;return x;}
	void print(node *x){
		if (x==null) return;
		print(x->l);
		printf("nie %d\n",x->key);
		print(x->r);
	}
};
treap T[M];
struct Qnode{
	int key,p;
};
Qnode A[M];int A1=0,s=0;
bool cmp(const Qnode i,const Qnode j){return i.key<j.key;}
int x[M],y[M],n; char c[M];
void add(int x,int y){for (;x<=s;x+=x&(-x)) T[x].insert(T[x].root,y);}
int get(int x,int y){int res=0; for (;x;x-=x&(-x))res+=T[x].query(y); return res;}
void read(int &x){
	char ch; x=0;
	for (ch=getchar();ch<'0' || ch>'9';ch=getchar());
	for (;ch>='0' && ch<='9';x=x*10+ch-48,ch=getchar());
}
int main()
{
	int t1=clock();
	freopen("1.in","r",stdin);
	freopen("3.out","w",stdout);
	read(n);clear();
	for (int i=1;i<=n;++i){
		char ch=getchar(); while (ch!='+' && ch!='?') ch=getchar(); c[i]=ch;
		read(x[i]);read(y[i]);A[++A1].key=x[i];A[A1].p=i;
	}
	std::sort(A+1,A+1+A1,cmp);A[0].key=-1;
	for (int i=1;i<=A1;++i){
		if (A[i].key!=A[i-1].key)++s;x[A[i].p]=s;
	}
	for (int i=1;i<=s;++i)T[i].root=null;
	printf("time1=%d\n",clock()-t1);
	for (int i=1;i<=n;++i)
		if (c[i]=='+') add(x[i],y[i]);
		else printf("%d\n",get(x[i],y[i]));
	printf("time=%d\n",clock()-t1);
	//system("pause");
	return 0;
}


