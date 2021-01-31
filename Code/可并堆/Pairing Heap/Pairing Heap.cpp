#include <ctime>
#include <iostream>
using namespace std;
#define maxn 1000010
struct node{
       int value;
       node *ch[2],*pre;
       };
node tree[maxn],*tmp[maxn],*root,*Null;
int top=0;
node *newnode(int key)
{
     node *p=&tree[++top];
     p->value=key,p->ch[0]=p->ch[1]=p->pre=Null;
     return p;
}
node *link(node *a,node *b)
{
     if (a->value>b->value) {node *tmp=a;a=b;b=tmp;}
     if (b==Null)return a;
     b->ch[1]=a->ch[0];
     if (a->ch[0]!=Null) a->ch[0]->pre=b;
     a->ch[0]=b,b->pre=a;
     return a;
}

node *combine(node *x)
{
     int total=0,i;
     node *y,*z,*res;
     if (x==Null) return Null;
     for (;x!=Null;x=z)
     {
         y=x->ch[1],z=y->ch[1];
         x->ch[1]=y->ch[1]=y->pre=z->pre=Null;
         tmp[++total]=link(x,y);
     }
     for (res=tmp[total],i=total-1;i;i--)
       res=link(res, tmp[i]);
     return res;
}

int n,i;
int main()
{
     root=Null=newnode(1<<30);
     //freopen("a.in", "r", stdin);
     //freopen("a.out", "w", stdout);
     Null->ch[0]=Null->ch[1]=Null->pre=Null;
     srand(time(0));
     scanf("%d",&n);
     //for (i=1;i<=n;i++)
       //root=link(root,newnode((rand()<<16)+rand()));
     for (i=1;i<=n;i++)
       root=link(root,newnode(n-i+1));
     for (i=1;i<=n;i++)
       printf("%d\n",root->value),root=combine(root->ch[0]);
     system("pause");
     return 0;
}




