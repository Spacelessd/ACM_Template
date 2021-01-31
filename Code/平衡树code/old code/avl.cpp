#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

class AVL{
public:
struct node{
       int l,r,size,key,p,height;
    };
    node a[1000010];
    int root,len;
    void clear()
    {
        root=0;len=0;
	    a[0].l=a[0].r=a[0].p=a[0].size=0;
	    a[0].height=0;
    }
    AVL(){clear();}

	int newnode(int key)
	{
        int x=++len;
        a[x].l=a[x].r=a[x].p=0;
        a[x].size=1;a[x].key=key;
        a[x].height=1;
        return x;
    }
    
	void renewh(int x)
	{
         a[x].height=a[a[x].l].height>a[a[x].r].height?a[a[x].l].height+1:a[a[x].r].height+1;
    }
    
	void update(int x)
	{
         a[x].size=a[a[x].l].size+a[a[x].r].size+1;
         renewh(x);
    }
	
    void zig(int x)
    {
        int y=a[x].p,z=a[y].p;
       	if (a[z].l==y) a[z].l=x;else a[z].r=x;
	    a[x].p=z;a[y].p=x;
	    a[y].l=a[x].r;a[x].r=y;
	    a[a[y].l].p=y;
	    update(y);update(x);
    }
    
    void zag(int x)
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
    
    void del(int &root,int key)
	{
        if (root==0)return;
               
    }
};

AVL a;
#include"test.h"
int main()
{
    test1();
    test();
    test2();
}


