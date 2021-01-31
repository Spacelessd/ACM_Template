#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
int s1,s2,s3,s;
struct Splay{
	#define oo (1<<30)
	struct node{
		int key,size;
		node *l,*r,*p;
		void update(){++s;
			size=l->size+r->size+1;
		}
	};
	node a[N];
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
	node* newnode(int key){s+=10;
		node *p=a+(++len);
		p->l=p->r=p->p=null;
		p->size=1;p->key=key;
		return p;
	}
	void zig(node *x){s1+=10;
		node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else z->r=x;
		x->p=z;y->p=x;
		y->l=x->r;x->r=y;
		y->l->p=y;
		y->update();
	}
	void zag(node *x){s1+=10;
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
		while (x->p->size){s+=5;
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
		while (x->size){++s2;
			y=x;++x->size;
			if (z->key<x->key)x=x->l;
				else x=x->r;
		}
		z->p=y;s2+=2;
		if (z->key<y->key)y->l=z;
			else y->r=z;
		//splay(root,z);
	}
	node *findkth(node *&root,int k){
		node *x=root;
		while (k){++s3;
			if (k==x->l->size+1) break;
			if (k<=x->l->size) x=x->l;
				else {k-=x->l->size+1;x=x->r;}
		}
		splay(root,x);
		return x;
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
Splay a;
int main()
{
	int t1=clock();
	long long n,A,b,c,m,i,tmp,key,ans=1;
	freopen("statistics.in","r",stdin);
	//freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	//memset(a.a,0,sizeof(a.a));
	a.insert(a.root,1);
	for (i=2;i<=n;++i){s+=10;//continue;
		if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
		m=a.findkth(a.root,tmp)->key;
		key=(A*m+b*i+c)%1000000007;
		a.insert(a.root,(int)key);
		ans+=key;
		}
	printf("%I64d\n",ans);
	printf("rotate %d\n",s1);
	printf("find %d\n",s2);
	printf("findkth %d\n",s3);
	printf("else %d\n",s);
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
}




