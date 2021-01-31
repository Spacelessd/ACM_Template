#include<stdio.h> 
#define maxn 200017  
struct DynamicTree{    
    struct node{    
        int size;    
        node *l,*r,*p;  
    };    
    node *a,*null;    
    int isroot(node *p){return p->p->l!=p&&p->p->r!=p;}    
    void clear(){    
        null=new node;null->l=null->r=null;    
        null->size=0;    
    }    
    void ini_node(node *p){    
        p->l=p->r=null;p->size=1;  
    } 
    void set(int n){ 
        n+=5;a=new node[n];clear(); 
        for (int i=0;i<n;++i)ini_node(a+i); 
    } 
    void zig(node *x){ 
        node *y=x->p,*z=y->p; 
        if (z->l==y) z->l=x;else if (z->r==y)z->r=x;    
        x->p=z;y->p=x;    
        y->l=x->r;x->r=y;    
        y->l->p=y;    
        y->size=y->l->size+y->r->size+1;   
    }    
    void zag(node *x){    
        node *y=x->p,*z=y->p;    
        if (z->l==y) z->l=x;else if (z->r==y)z->r=x;    
        x->p=z;y->p=x;    
        y->r=x->l;x->l=y;    
        y->r->p=y;    
        y->size=y->l->size+y->r->size+1;   
    }
    void splay(node *x){
        while (!isroot(x))
            if (x==x->p->l)zig(x);else zag(x);
        x->size=x->l->size+x->r->size+1;
    }
    node *Expose(node *p){
        node *q=null;    
        for (;p!=null;p=p->p){    
            splay(p);p->r=q;p->size=p->l->size+q->size+1;q=p; 
        } 
        return q; 
    }  
    node *getnode(int x){return a+x;}    
    int getid(node *p){return p-a;}    
    int Depth(node *p){Expose(p);splay(p);return p->l->size;}  
    void Cut(node *p){    
        splay(p);p->l->p=p->p;p->l=null; 
        p->size=p->r->size+1; 
    }    
    void Changefa(node *x,node *y){Cut(x);x->p=y;} 
    void Changefa(int x,int y){Changefa(getnode(x),getnode(y));}    
};    
DynamicTree a;
inline void read(int &x){  
    char ch;x=0;  
    for (ch=getchar();!(ch>='0' && ch<='9');ch=getchar());  
    for (;ch>='0' && ch<='9';x=x*10+ch-'0',ch=getchar());  
}  
char buf[11],out[400007],*o=out;
inline void print(int x){ 
    char *b=buf;
    while(x){*b++=x%10+48;x/=10;}
    while(b--!=buf)*o++=*b;
    *o++='\n';
}
int n;
void init(){  
     int i,x;  
     read(n);a.set(n);  
     for (i=1;i<=n;++i){    
         read(x);
         int tmp=i+x>n?n+1:i+x;
         a.a[i].p=a.getnode(tmp);  
     }  
     a.a[n+1].p=a.null;
}    
int main() 
{ 
    //freopen("bounce.in","r",stdin);    
    //freopen("bounce.out","w",stdout);  
    int m,ch,i,tmp,x,y; 
    init(); 
    read(m);++m; 
    for (i=1;i<m;++i){ 
        read(ch);read(x);++x;
        if (ch==1){  
                   print(a.Depth(a.getnode(x)));  
                   } 
        else       { 
                   read(y);
                   tmp=x+y;if (tmp>n)tmp=n+1; 
                   a.Changefa(x,tmp); 
                   } 
        } 
    puts(out); 
    //for (;;); 
    return 0; 
}
