#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct AVL{
	struct node{
		int l,r,size,key,p,height;
	};
	node a[N];
	int root,len;
	void clear(){
		root=0;len=0;
		a[0].l=a[0].r=a[0].p=a[0].size=0;
		a[0].height=0;
	}
	AVL(){clear();}
	int newnode(int key){
		int x=++len;
		a[x].l=a[x].r=a[x].p=0;
		a[x].size=1;a[x].key=key;
		a[x].height=1;
		return x;
	}
	void renewh(int x){
		a[x].height=a[a[x].l].height>a[a[x].r].height
		?a[a[x].l].height+1:a[a[x].r].height+1;
	}
	void update(int x){
		a[x].size=a[a[x].l].size+a[a[x].r].size+1;
		renewh(x);
	}
	void zig(int x){
		int y=a[x].p,z=a[y].p;
		if (a[z].l==y) a[z].l=x;else a[z].r=x;
		a[x].p=z;a[y].p=x;
		a[y].l=a[x].r;a[x].r=y;
		a[a[y].l].p=y;
		update(y);update(x);
	}
	void zag(int x){
		int y=a[x].p,z=a[y].p;
		if (a[z].l==y) a[z].l=x;else a[z].r=x;
		a[x].p=z;a[y].p=x;
		a[y].r=a[x].l;a[x].l=y;
		a[a[y].r].p=y;
		update(y);update(x);
	}
	void insert(int &root,int key){
		int y;
		if (root==0){root=newnode(key);return;}
		if (key<a[root].key){
			insert(a[root].l,key);a[a[root].l].p=root;
			if (a[a[root].l].height-a[a[root].r].height>1){
				if (key<a[a[root].l].key){y=a[root].l;zig(y);root=y;}
					else {y=a[a[root].l].r;zag(y);zig(y);root=y;}
			}else update(root);
		}
		else {
			insert(a[root].r,key);a[a[root].r].p=root;
			if (a[a[root].r].height-a[a[root].l].height>1){
				if (key>=a[a[root].r].key){y=a[root].r;zag(y);root=y;}
					else {y=a[a[root].r].l;zig(y);zag(y);root=y;}
			}else update(root);
		}
	}
	void del(int &root,int key){
		if (root==0)return;
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
		if (!x)return;
		print(a[x].l);
		printf("nie %d\n",a[x].key);
		print(a[x].r);
	}
};
AVL a;
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
		//printf("%d %d %d\n",i,m,A*m+b*i+c);
		ans+=key;
		//print(a.root);
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


