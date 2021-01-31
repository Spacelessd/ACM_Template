#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct Btree{
	#define L 2
	struct node{
		node *son[L*2+1];int key[L*2+1];
		int num,size;bool leaf;
		void update(){
			size=num;
			if (!leaf)
				for (int i=1;i<=num+1;++i)size+=son[i]->size;
		}
	};
	node a[N],*root;int len;
	void clear(){
		len=0;root=Newnode();root->size=0;root->leaf=1;
	}
	Btree(){clear();}
	node *Newnode(){
		node *x=a+(++len);x->num=0;
		return x;
	}
	void split_child(node *x,int k,node *y){
		node *z=Newnode();
		z->leaf=y->leaf;z->num=L-1;
		for (int i=1;i<L;++i)z->key[i]=y->key[L+i];
		if (!y->leaf)
			for (int i=1;i<=L;++i)z->son[i]=y->son[L+i];
		y->num=L-1;
		for (int i=x->num+1;i>k;--i)x->son[i+1]=x->son[i];
		x->son[k+1]=z;
		for (int i=x->num;i>=k;--i)x->key[i+1]=x->key[i];
		x->key[k]=y->key[L];++x->num;
		y->update();z->update();x->update();
	}
	void insert_nonfull(node *x,int key){
		if (x->leaf)
			for (int i=x->num+1;i;--i){
				if (i==1||x->key[i-1]<=key){
					x->key[i]=key;++x->num;++x->size;
					return;
				}
				x->key[i]=x->key[i-1];
			}
		else {
			int i;
			for (i=x->num;i;--i)
				if (x->key[i]<=key)break;
			++i;
			if (x->son[i]->num==L*2-1){
				split_child(x,i,x->son[i]);
				if (key>x->key[i])++i;
			}
			insert_nonfull(x->son[i],key);
		}
		x->update();
	}
	void insert(int key){
		if (root->num==L*2-1){
			node *x=Newnode();
			x->leaf=0;x->son[1]=root;
			split_child(x,1,root);root=x;
		}
		insert_nonfull(root,key);
	}
	int findkth(node *x,int k){
		if (x->leaf)return x->key[k];
		for (int i=1;i<=x->num+1;++i){
			if (x->son[i]->size>=k)return findkth(x->son[i],k);
			k-=x->son[i]->size+1;if (!k)return x->key[i];
		}
	}
	void print(node *x){
		for (int i=1;i<=x->num;++i){
			if (!x->leaf)print(x->son[i]);
			printf("%d ",x->key[i]);
		}
		if (!x->leaf)print(x->son[x->num+1]);
	}
};
Btree a;
int main()
{
	long long n,A,b,c,m,i,tmp,key,ans=1;
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	a.insert(1);
	for (i=2;i<=n;++i){
		if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
		m=a.findkth(a.root,tmp);
		key=(A*m+b*i+c)%1000000007;
		a.insert((int)key);
		ans+=key;
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}




