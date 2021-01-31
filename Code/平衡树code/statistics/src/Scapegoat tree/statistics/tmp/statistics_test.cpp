#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
#define oo (1<<30)
struct Scapegoat_tree{
	struct node{
		int key,size;
		node *l,*r;
		void update(){
			size=l->size+r->size+1;
		}
	};
	node a[N],*stack[N],*null,*root;int len,s1;
	void clear(){
		null=new node;null->l=null->r=null;
		null->size=0;null->key=-oo;
		len=0;root=null;
	}
	Scapegoat_tree(){clear();}
	node* newnode(int key){
		node *p=a+(++len);
		p->l=p->r=null;
		p->size=1;p->key=key;
		return p;
	}
	void build(int l,int r){
		int mid=(l+r)>>1,tmp;
		if (l<mid){
			build(l,mid-1);tmp=(l+mid-1)>>1;
			stack[mid]->l=stack[tmp];
		}else stack[mid]->l=null;
		if (r>mid){
			build(mid+1,r);tmp=(mid+1+r)>>1;
			stack[mid]->r=stack[tmp];
		}else stack[mid]->r=null;
		stack[mid]->update();
	}
	void dfs(node *x){
		if (x->l!=null)dfs(x->l);
		stack[++s1]=x;
		if (x->r!=null)dfs(x->r);
	}
	void insert(node *&x,int key){
		if (x==null){x=newnode(key);return;}
		if (key<x->key){
			insert(x->l,key);
			if (x->r->size*2<x->l->size){
				s1=0;dfs(x);build(1,s1);
				x=stack[(1+s1)>>1];
			}
			else ++x->size;
		}
		else {
			insert(x->r,key);
			if (x->l->size*2<x->r->size){
				s1=0;dfs(x);build(1,s1);
				x=stack[(1+s1)>>1];
			}
			else ++x->size;
		}
	}
	node* findkth(node *root,int k){
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
		if (x==null)return;
		print(x->l);
		printf("nie %d\n",x->key);
		print(x->r);
	}
};
Scapegoat_tree a;
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
	//system("pause");for (;;);
	return 0;
}


