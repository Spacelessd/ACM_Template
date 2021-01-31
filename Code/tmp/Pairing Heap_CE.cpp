#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct pairing_heap{
#define maxn 10000010
struct node{
    node *l,*r,*pre;
    int key;
    };
static node tree[maxn];
static node *tmp[maxn];
static node *Null;
static int len;
    node *root;
    node *newnode(int key){
         node *p=&tree[++len];
         p->key=key;p->l=p->r=p->pre=Null;
         return p;
    }
    pairing_heap(){root=Null;}
    node *link(node *a,node *b){
         if (a->key>b->key) {node *tmp=a;a=b;b=tmp;}
         if (b==Null)return a;
         b->r=a->l;a->l->pre=b;
         a->l=b;b->pre=a;
         return a;
    }
    node *combine(node *x){
         int total=0,i;node *y,*z;
         x->pre=Null;
         for (;x!=Null;x=z)
         {
             y=x->r,z=y->r;
             x->r=y->r=y->pre=z->pre=Null;
             tmp[++total]=link(x,y);
         }
         for (x=tmp[total],i=total-1;i>0;--i)x=link(x,tmp[i]);
         return x;
    }
    void insert(node *x){
         root=link(x,root);
    }
    int min(){return root->key;}
    node *extractmin(){
         node *tmp=root;
         root=combine(root->l);
         return tmp;
    }
    void decreasekey(node *x,int key){
         x->key=key;
         if (x!=root){
            x->r->pre=x->pre;
            if (x->pre->l!=x)x->pre->r=x->r;
              else x->pre->l=x->r;
            x->r=x->pre=Null;
            root=link(x,root);
            }
    }
    void merge(pairing_heap *x){
         root=link(root,x->root);
    }
    void del(node *x){
         decreasekey(x,-2147483647);
         extractmin();
         }
};
pairing_heap::node tree[maxn];
pairing_heap::node *tmp[maxn];
pairing_heap::node *Null;
/*
void init()
{
     pairing_heap::tmp[0]=pairing_heap::Null=new pairing_heap::node;
     pairing_heap::Null->key=2147483647;pairing_heap::Null->l=pairing_heap::Null->r=pairing_heap::Null->pre=pairing_heap::Null;
}*/
pairing_heap a;
int n,i;
pairing_heap::node *x;
int main()
{
    /*init();
    scanf("%d",&n);
    int X=13251325;
    int t1=clock();
    for (i=1;i<=n;i++)
    {
        x=a.newnode(X&0x7fffffff);
        a.insert(x);
        X+=(X<<2)+1;
    }
    for (i=1;i<=n;i++)
    {
        x=a.extractmin();
        if (x!=Null)printf("%d\n",x->key);else printf("error!\n");
    }
    printf("time=%d\n",clock()-t1);*/
    system("pause");
}





/*int main()
{
    init();
    scanf("%d",&n);
    int t1=clock();
    a.resize(n);
    for (i=1;i<=n;i++)
    {
        x=a.newnode(i);
        a.insert(x);
    }
    for (i=1;i<=n;i++)
    {
        x=a.extractmin();
        //if (x!=Null)printf("%d\n",x->key);else printf("error!\n");
    }
    printf("time=%d\n",clock()-t1);
    system("pause");
}*/
