#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct SkewHeap{
	#define N 1000005
	struct node{node *l,*r;int key;}nodes[N];
	node *Merge(node *p,node *q){
		static node *t,*tmp;
		if (!p||!q)return p?p:q;
		if (p->key>q->key)t=p,p=q,q=t;
		tmp=Merge(p->r,q);p->r=p->l;p->l=tmp;
		return p;
	}
	node *root;int len;
	SkewHeap(){root=NULL;len=0;}
	void insert(int key){
		++len;nodes[len].key=key;nodes[len].l=nodes[len].r=NULL;
		root=Merge(root,nodes+len);
	}
	bool empty(){return len==0;}
	int top(){return root->key;}
	void pop(){root=Merge(root->l,root->r);}
};
SkewHeap a1;
struct SkewHeap1{
	#define N 1000005
	struct node{node *l,*r;int key;}nodes[N];
	node *Merge(node *p,node *q){
		static node *t,*tmp;
		if (!p||!q)return p?p:q;
		if (p->key<q->key)t=p,p=q,q=t;
		tmp=Merge(p->r,q);p->r=p->l;p->l=tmp;
		return p;
	}
	node *root;int len;
	SkewHeap1(){root=NULL;len=0;}
	void insert(int key){
		++len;nodes[len].key=key;nodes[len].l=nodes[len].r=NULL;
		root=Merge(root,nodes+len);
	}
	bool empty(){return len==0;}
	int top(){return root->key;}
	void pop(){root=Merge(root->l,root->r);}
};
SkewHeap1 a;
int main()
{
	long long n,A,b,c,key,ans=1;
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	a.insert(1);
	for (int i=2;i<=n;++i){
		key=(A*a.top()+b*i+c)%1000000007;
		if (i&1)a.insert(key);
			else a1.insert(key);
		while (a.top()>a1.top()){
			int tmp1=a.top(),tmp2=a1.top();
			a.pop();a1.pop();
			a.insert(tmp2);a1.insert(tmp1);
		}
		ans+=key;
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


