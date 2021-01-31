#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

class BST{
public:
	struct node{
		int l,r,key,size,p;
    };
	node a[1000010];
	int len,root;
	void clear()
	{
        srand(time(0));len=0;root=0;
		a[0].l=a[0].r=a[0].p=a[0].key=a[0].size=0;
    }
	BST(){clear();}
	
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
	
    void insert(int &root,int key)
	{
	   int x=root,y=0,z=newnode(key);
       if (root==0){root=z;return;}
       while (x){
             y=x;
             if (key<a[x].key)x=a[x].l;
               else x=a[x].r;
             }
       a[z].p=y;
       if (key<a[y].key)a[y].l=z;
         else a[y].r=z; 
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
    
    int delmax(int x)
    {
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
    
    int delmin(int x)
    {
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
    
    void del(int x)
    {
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
};
BST a;
#include"test.h"
int main()
{
    test1();
    test();
    test2();
}


