#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct Binomial_Heap{
	#define N 1000005
	#define L 20
	struct node{node *l,*r;int key;}a[N];
	struct 
	node *root[L];
	Random_Heap(){for (int i=0;i<L;++i)root[i]=NULL;}
	void insert(int key){
		++len;nodes[len].key=key;nodes[len].l=nodes[len].r=NULL;
		root=M(root,nodes+len);
	}
	bool empty(){return len==0;}
	int top(){return root->key;}
	void pop(){root=M(root->l,root->r);}
	#undef N
};
Random_Heap a1;
struct Random_Heap1{
	#define N 1000005
	struct node{node *l,*r;int key;}nodes[N];
	int ran(){static int x=31253125;x+=(x<<4)+1;x&=(0x7fffffff);return x&(65536);}
	node *M(node *p,node *q){
		return (!p||!q)?(p?p:q):(p->key<q->key?M(q,p):
			((ran()?p->r=M(p->r,q):p->l=M(p->l,q)),p));
	}
	node *root;int len;
	Random_Heap1(){root=NULL;len=0;}
	void insert(int key){
		++len;nodes[len].key=key;nodes[len].l=nodes[len].r=NULL;
		root=M(root,nodes+len);
	}
	bool empty(){return len==0;}
	int top(){return root->key;}
	void pop(){root=M(root->l,root->r);}
	#undef N
};
Random_Heap1 a;
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


