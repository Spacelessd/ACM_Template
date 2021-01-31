#include<stdio.h>
struct pairing{
    struct node{
        int l,r,child,key;
        };
    int top;
    pairing(){};
    
    node *newnode(int key)
    {
         node *p=&tree[++top];
         p->value=key,p->ch[0]=p->ch[1]=p->pre=Null;
         return p;
    }
    void insert(node *x)
    {
         
    }
    int min(){return root->key}
    void extractmin()
    {
         
    }
    void decrease()
    {
    }
    
    };
int main()
{
    scanf("%d",&n);
    for (i=1;i<=n;i++)
    {
    }
    system("pause");
}
