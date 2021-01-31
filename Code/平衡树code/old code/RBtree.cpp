#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

class RBtree{
public:
#define black 0
#define red 1
struct node{
	int l,r,key,size,color,p;
	};
	node a[1000010];
	int len,root;
	void clear()
	{
		len=0;root=0;
		a[0].l=a[0].r=a[0].p=a[0].key=a[0].size=0;
		a[0].color=black;
	}
	RBtree(){clear();}
	
	int newnode(int key)
	{
		int x=++len;
		a[x].l=a[x].r=a[x].p=0;
		a[x].size=1;a[x].color=red;
		a[x].key=key;
		return x;
	}
	
	void update(int x)
	{
		 a[x].size=a[a[x].l].size+a[a[x].r].size+1;
	}
	
	inline void zig(int x)
	{
		int y=a[x].p,z=a[y].p;
	   	if (a[z].l==y) a[z].l=x;else a[z].r=x;
		a[x].p=z;a[y].p=x;
		a[y].l=a[x].r;a[x].r=y;
		a[a[y].l].p=y;
		update(y);update(x);
	}
	inline void zag(int x)
	{
		int y=a[x].p,z=a[y].p;
		if (a[z].l==y) a[z].l=x;else a[z].r=x;
		a[x].p=z;a[y].p=x;
		a[y].r=a[x].l;a[x].l=y;
		a[a[y].r].p=y;
		update(y);update(x);
	}
	
	void insert(int &root,int key)
	{
	   int x=root,y=0,fa=a[root].p,z=newnode(key);
	   while (x){
			y=x;
			if (key<a[x].key)x=a[x].l;
				else x=a[x].r;
			}
	   a[z].p=y;
	   if (key<a[y].key)a[y].l=z;
		 else a[y].r=z;
	   x=z;
	   while (1){
		   y=a[x].p;
		   if (y==fa){root=x;a[x].color=black;return;}
		   if (a[y].color==black)return;
		   z=a[y].p;
		   if ((x==a[y].r)&&(y==a[z].l)){zag(x);zig(x);a[y].color=black;}
			 else if ((x==a[y].l)&&(y==a[z].r)){zig(x);zag(x);a[y].color=black;}
			   else if ((x==a[y].l)&&(y==a[z].l)){zig(y);a[x].color=black;x=y;}
				 else if ((x==a[y].r)&&(y==a[z].r)){zag(y);a[x].color=black;x=y;}
		   }
	}
	
	int find(int x,int key)
	{
		if (x==0)return 0;
		if (key==a[x].key)return x;
		if (key<a[x].key)return find(a[x].l,key);
		else return find(a[x].r,key);
	}
	
	int fmin(int x){while (a[x].l)x=a[x].l;return x;}
	int fmax(int x){while (a[x].r)x=a[x].r;return x;}
};
RBtree a;
#include"test.h"
int main()
{
	test1();
	test();
	test2();
}


