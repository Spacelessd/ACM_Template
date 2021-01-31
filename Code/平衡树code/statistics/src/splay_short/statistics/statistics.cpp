#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct Splay{
	#define oo (1<<30)
	struct node{
		node *ch[2],*p;int key,size;
		void setc(node *c,int d){ch[d]=c;c->p=this;}
		bool dir(){return this==p->ch[1];}
		void update(){size=ch[0]->size+ch[1]->size+1;}
	}*root;
	node a[N],*null;int len;
	void clear(){
		len=0;root=null=new node;null->ch[0]=null->ch[1]=null;
		null->size=0;null->key=-oo;
	}
	Splay(){clear();}
	node *Newnode(int key){
		node *p=a+(++len);p->ch[0]=p->ch[1]=p->p=null;
		p->size=1;p->key=key;
		return p;
	}
	void rot(node *x){
		node *p=x->p;bool d=x->dir();
		if (p->p!=null)p->p->setc(x,p->dir());else x->p=null;
		p->setc(x->ch[!d],d);x->setc(p,!d);p->update();
	}
	void splay(node *&root,node *x){
		if (x==null) return;
		while (x->p!=null)if (x->p->p==null)rot(x);
		else x->dir()==x->p->dir()?rot(x->p),rot(x):(rot(x),rot(x));
		x->update();root=x;
	}
	void insert(node *&root,int key){
		node *x=root,*y=null,*z=Newnode(key);
		if (root==null){root=z;return;}
		while (x!=null){
			y=x;
			if (z->key<x->key)x=x->ch[0];
				else x=x->ch[1];
		}
		if (z->key<y->key)y->setc(z,0);
			else y->setc(z,1);
		splay(root,z);
	}
	node *findkth(node *&root,int k){
		node *x=root;
		while (k){
			if (k==x->ch[0]->size+1) break;
			if (k<=x->ch[0]->size) x=x->ch[0];
				else {k-=x->ch[0]->size+1;x=x->ch[1];}
		}
		splay(root,x);return x;
	}
	node *fmin(node *x){while (x->ch[0]!=null)x=x->ch[0];return x;}
	node *fmax(node *x){while (x->ch[1]!=null)x=x->ch[1];return x;}
	void print(node *x){
		if (x==null)return;
		print(x->ch[0]);
		printf("nie %d\n",x->key);
		print(x->ch[1]);
	}
};
Splay a;
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


