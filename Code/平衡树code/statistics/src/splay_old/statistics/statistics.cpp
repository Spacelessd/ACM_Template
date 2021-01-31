#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct Splay{
	struct node{
		int l,r,p,key,size;
	};
	node a[N];int len,root;
	void clear(){
		len=0;root=0;
		a[0].l=a[0].r=a[0].key=a[0].size=0;
	}
	Splay(){clear();}
	int newnode(int key){
		int x=++len;
		a[x].l=a[x].r=a[x].p=0;
		a[x].size=1;a[x].key=key;
		return x;
	}
	void update(int x){
		a[x].size=a[a[x].l].size+a[a[x].r].size+1;
	}
	void zig(int x){
		int y=a[x].p,z=a[y].p;
		if (a[z].l==y) a[z].l=x;else a[z].r=x;
		a[x].p=z;a[y].p=x;
		a[y].l=a[x].r;a[x].r=y;
		a[a[y].l].p=y;
		update(y);
	}
	void zag(int x){
		int y=a[x].p,z=a[y].p;
		if (a[z].l==y) a[z].l=x;else a[z].r=x;
		a[x].p=z;a[y].p=x;
		a[y].r=a[x].l;a[x].l=y;
		a[a[y].r].p=y;
		update(y);
	}
	void splay(int &root,int x){
		int y,z,fa=a[root].p;
		if (x==0) return;
		while (a[x].p!=fa){
			y=a[x].p;z=a[y].p;
			if (z==fa) {if (x==a[y].l)zig(x);else zag(x);}
			else
				if (y==a[z].l)
					if (x==a[y].l){zig(y);zig(x);}
					else{zag(x);zig(x);}
				else
					if (x==a[y].r){zag(y);zag(x);}
					else{zig(x);zag(x);}
		}
		update(x);root=x;
	}
	void insert(int &root,int key){
		int x=root,y=0,z=newnode(key);
		if (root==0){root=z;return;}
		while (x){
			y=x;
			if (a[z].key<a[x].key)x=a[x].l;
				else x=a[x].r;
		}
		a[z].p=y;
		if (a[z].key<a[y].key)a[y].l=z;
			else a[y].r=z;
		splay(root,z);
	}
	int find(int &root,int x){
		int tmp=root;
		while (tmp!=0){
			if (x==a[tmp].key) {splay(root,tmp);return tmp;}
				else if (x<a[tmp].key) tmp=a[tmp].l;
					else tmp=a[tmp].r;
		}
		splay(root,a[tmp].p);return 0;
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
		if (x==0)return;
		print(a[x].l);
		printf("nie %d\n",a[x].key);
		print(a[x].r);
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
		m=a.a[a.findkth(a.root,tmp)].key;
		key=(A*m+b*i+c)%1000000007;
		a.insert(a.root,(int)key);
		ans+=key;
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}





