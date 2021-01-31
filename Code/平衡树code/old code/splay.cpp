#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

class Splay{
public:
struct node{
	int l,r,p,key,size;
    };
	node a[1000010];
	int len,root;
	void clear()
	{
    	len=0;root=0;
		a[0].l=a[0].r=a[0].key=a[0].size=0;
    }
	Splay(){clear();}
	
	int newnode(int key)
	{
        int x=++len;
        a[x].l=a[x].r=a[x].p=0;
        a[x].size=1;a[x].key=key;
        return x;
    }
    
	void update(int x)
	{
         a[x].size=a[a[x].l].size+a[a[x].r].size+1;
    }
	
	
	void zig(int x)  //ÓÒÐý
	{
	    int y=a[x].p,z=a[y].p;
		if (a[z].l==y) a[z].l=x;else a[z].r=x;
		a[x].p=z;a[y].p=x;
		a[y].l=a[x].r;a[x].r=y;
		a[a[y].l].p=y;
		update(y);
	}

	void zag(int x)  //×óÐý
	{
 	    int y=a[x].p,z=a[y].p;
		if (a[z].l==y) a[z].l=x;else a[z].r=x;
		a[x].p=z;a[y].p=x;
		a[y].r=a[x].l;a[x].l=y;
		a[a[y].r].p=y;
		update(y);
	}
	
	
	void splay(int &root,int x)  //ºËÐÄ²Ù×÷:Ë«Ðýsplay
	{
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
	
	void insert(int &root,int key)
	{
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
	

	int find(int &root,int x)
	{
        int tmp=root;
        while (tmp!=0){
          if (x==a[tmp].key) {splay(root,tmp);return tmp;}
              else if (x<a[tmp].key) tmp=a[tmp].l;
                else tmp=a[tmp].r;
          }
        splay(root,a[tmp].p);return 0;
	}
};
Splay a;

#include"test.h"
int main()
{
    test1();
    test();
}


