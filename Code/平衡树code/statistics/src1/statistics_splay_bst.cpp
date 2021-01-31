#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct Splay{
#define oo (1<<30)
	struct node{
		int key,size;
		node *l,*r,*p;
	};
	node a[200010];
	node *null,*root;
	int len;
	void clear(){
		null=new node;null->l=null->r=null;
		null->size=0;null->key=-oo;
		len=0;root=null;
	}
	Splay(int n=5){
		n+=5;clear();
	}
	node* newnode(int key){
		node *p=++len+a;
		p->l=p->r=p->p=null;
		p->size=1;p->key=key;
		return p;
	}
	void insert(int key)
	{
	   node *x=root,*y=null,*z=newnode(key);
	   while (x!=null){
			 ++(y=x)->size;
			 if (z->key<x->key)x=x->l;
			   else x=x->r;
			 }
	   z->p=y;
	   if (z->key<y->key)y->l=z;
		 else y->r=z;
	   //splay(z);
	}
	node* findkth(int k){
		node *x=root;
		while (k){
			  if (k<=x->l->size) x=x->l;
else if (k==x->l->size+1) break;
				 else k-=x->l->size+1,x=x->r;
		}
		return x;
	}
};
Splay a;
int main()
{
	long long n,A,b,c,m,i,tmp,key,ans=1;
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	a.root=a.newnode(1);
	for (i=2;i<=n;++i){
		if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
		m=a.findkth(tmp)->key;
		key=(A*m+b*i+c)%1000000007;
		a.insert((int)key);
		//printf("%d %d %d\n",i,m,A*m+b*i+c);
		ans+=key;
		//print(a.root);
		}
	printf("%I64d\n",ans);
	//system("pause");
}


