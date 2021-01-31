#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
#define ll long long
int s;
struct treap{
	struct node{
		int l,r,key,size;
	};
	node a[N];
	int len,root,oo;
	void clear(){
		srand(time(0));
		oo=2147483647;
		len=0;root=0;
		a[0].l=a[0].r=a[0].key=a[0].size=0;
	}
	treap(){clear();}
	int newnode(int key){
		int x=++len;
		a[x].l=a[x].r=0;
		a[x].size=1;a[x].key=key;
		return x;
	}
	void update(int x){
		a[x].size=a[a[x].l].size+a[a[x].r].size+1;
	}
	void zig(int &x){++s;
		int y=a[x].l;
		a[x].l=a[y].r;a[y].r=x;
		update(x);update(y);
		x=y;
	}
	void zag(int &x){++s;
		int y=a[x].r;
		a[x].r=a[y].l;a[y].l=x;
		update(x);update(y);
		x=y;
	}
	void insert(int &x,int key){
		if (!x)x=newnode(key);
		else 
		if (key<=a[x].key){
			insert(a[x].l,key);++a[x].size;
			if ((ll)rand()*(ll)a[x].size<(ll)rand()*(ll)a[a[x].l].size)zig(x);
		}
		else if (key>a[x].key){
			insert(a[x].r,key);++a[x].size;
			if ((ll)rand()*(ll)a[x].size<(ll)rand()*(ll)a[a[x].r].size)zag(x);
		}
	}
	int find(int x,int key){
		if (x==0)return 0;
		if (key==a[x].key)return x;
		if (key<a[x].key)return find(a[x].l,key);
		else return find(a[x].r,key);
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
		if (x==0) return;
		print(a[x].l);
		printf("nie %d\n",a[x].key);
		print(a[x].r);
	}
};
treap a;
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
	printf("%d\n",s);
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


