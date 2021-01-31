#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct BST{
	struct node{
		int l,r,key,size,p;
	};
	node a[N];
	int len,root;
	void clear(){
		srand(time(0));len=0;root=0;
		a[0].l=a[0].r=a[0].p=a[0].key=a[0].size=0;
	}
	BST(){clear();}
	int newnode(int key){
		int x=++len;
		a[x].l=a[x].r=a[x].p=0;
		a[x].size=1;a[x].key=key;
		return x;
	}
	void update(int x){
		a[x].size=a[a[x].l].size+a[a[x].r].size+1;
	}
	void insert(int &root,int key){
		int x=root,y=0,z=newnode(key);
		if (root==0){root=z;return;}
		while (x){
			++a[y=x].size;
			if (key<a[x].key)x=a[x].l;
				else x=a[x].r;
		}
		a[z].p=y;
		if (key<a[y].key)a[y].l=z;
			else a[y].r=z;
	}
	int find(int x,int key){
		if (x==0)return 0;
		if (key==a[x].key)return x;
		if (key<a[x].key)return find(a[x].l,key);
			else return find(a[x].r,key);
	}
	int delmax(int x){
		if (x==0)return 0;
		if (a[x].l==0){
			a[a[x].r].p=a[x].p;a[a[x].p].l=a[x].r;
			return x;
			}
		else {
			int tmp=delmax(a[x].l);
			update(x);return tmp;
		}
	}
	int delmin(int x){
		 if (x==0)return 0;
		 if (a[x].r==0){
			a[a[x].l].p=a[x].p;a[a[x].p].r=a[x].l;
			return x;
		}
		else {
			int tmp=delmin(a[x].r);
			update(x);return tmp;
		}
	}
	void del(int x){
		int tmp;
		if (rand()<16384){
			tmp=delmin(a[x].l);
			if (x==a[a[x].p].l)a[a[x].p].l=tmp;
				else a[a[x].p].r=tmp;
			a[tmp].p=a[x].p;update(tmp);
		}
		else {
			tmp=delmax(a[x].r);
			if (x==a[a[x].p].l)a[a[x].p].l=tmp;
				else a[a[x].p].r=tmp;
			a[tmp].p=a[x].p;update(tmp);
		}
		for (x=a[x].p;x;x=a[x].p) update(x);
	}
	int findkth(int &root,int k){
		int x=root;
		while (k){
			if (k==a[a[x].l].size+1) break;
			if (k<=a[a[x].l].size) x=a[x].l;
				else {k-=a[a[x].l].size+1;x=a[x].r;}
		}
		return x;
	}
	int fmin(int x){while (a[x].l)x=a[x].l;return x;}
	int fmax(int x){while (a[x].r)x=a[x].r;return x;}
	void print(int x){
		if (x==NULL)return;
		print(a[x].l);
		printf("nie %d\n",a[x].key);
		print(a[x].r);
	}
};
BST a;
int main()
{
	long long n,A,b,c,m,i,tmp,key,ans=1;
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	a.insert(a.root,1);
	for (i=2;i<=n;++i){
		if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
		m=a.a[a.findkth(a.root,tmp)].key;
		key=(A*m+b*i+c)%1000000007;
		a.insert(a.root,(int)key);
		ans+=key;
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


