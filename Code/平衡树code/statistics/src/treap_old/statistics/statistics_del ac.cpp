#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct treap{
	struct node{
		int l,r,key,fix,size;
	};
	node a[N];
	int len,root,oo;
	void clear(){
		srand(time(0));
		oo=2147483647;
		len=0;root=0;
		a[0].l=a[0].r=a[0].size=0;
		a[0].fix=oo;
	}
	treap(){clear();}
	int newnode(int key){
		int x=++len;
		a[x].l=a[x].r=0;
		a[x].size=1;a[x].key=key;
		a[x].fix=rand()*32768+rand();
		return x;
	}
	void update(int x){
		a[x].size=a[a[x].l].size+a[a[x].r].size+1;
	}
	void zig(int &x){
		int y=a[x].l;a[x].l=a[y].r;a[y].r=x;
		update(x);update(y);x=y;
	}
	void zag(int &x){
		int y=a[x].r;a[x].r=a[y].l;a[y].l=x;
		update(x);update(y);x=y;
	}
	void insert(int &x,int key){
		if (!x)x=newnode(key);
		else
		if (key<=a[x].key){
			insert(a[x].l,key);++a[x].size;
			if (a[a[x].l].fix<a[x].fix)zig(x);
		}
		else if (key>a[x].key){
			insert(a[x].r,key);++a[x].size;
			if (a[a[x].r].fix<a[x].fix)zag(x);
		}
	}
	int find(int x,int key){
		if (x==0)return 0;
		if (key==a[x].key)return x;
		if (key<a[x].key)return find(a[x].l,key);
		else return find(a[x].r,key);
	}
	void del(int &x,int key){
		if (x==0)return;
		if (a[x].key==key){
			if (!a[x].l||!a[x].r){
				if (a[x].l)x=a[x].l;
					else x=a[x].r;
			}
			else {
				if (a[a[x].l].fix<a[a[x].r].fix){
					zig(x);del(a[x].r,key);update(x);
				}
				else{
					zag(x);del(a[x].l,key);update(x);
				}
			}
		}
		else if (key<a[x].key)del(a[x].l,key),update(x);
			else del(a[x].r,key),update(x);
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
		if (!x) return;
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
		a.del(a.root,(int)key);
		a.insert(a.root,(int)key);
		ans+=key;
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


